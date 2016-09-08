using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.SharePoint.Client;
using Microsoft.SharePoint.Client.WebParts;
using System.Security.Cryptography;
using System.Security.Cryptography.X509Certificates;
using System.Net;
using System.Net.Security;
using System.Reflection;
using System.Data;
using System.IO;
using System.Xml.Linq;
using System.Threading;
using System.Text.RegularExpressions;
using System.Web;
using System.Security;
using System.Diagnostics;
using Microsoft.Win32;

namespace SharePointClient
{

    public static class Trace
    {
        private static Mutex mut = new Mutex();
        public static bool bDebug
        {
            get;
            set;
        }
        public static void Write(string line, object b)
        {
            mut.WaitOne();
            if (bDebug)
            {
                string m_fileName = Assembly.GetExecutingAssembly().Location.Replace("dll", "log");
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(m_fileName, true))
                {
                    file.Write(string.Format(line, b));
                }
            }
            System.Diagnostics.Trace.Write(string.Format(line, b));
            mut.ReleaseMutex();
        }
        public static void WriteLine()
        {
            WriteLine("");
        }

        public static void WriteLine(string line, object b)
        {
            line = line + "\r\n";
            Write(line, b);
        }

        public static void WriteLine(string line, bool bevtlog = false)
        {
            mut.WaitOne();
            if (bDebug)
            {
                string m_fileName = Assembly.GetExecutingAssembly().Location.Replace("dll", "log");
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(m_fileName, true))
                {
                    file.WriteLine(line);
                }
            }
            if (bevtlog)
            {
	            String ews = "SharePointClient";
	            if (!EventLog.SourceExists("SharePointClient"))
	            {
		            EventLog.CreateEventSource(ews, "Application");
	            }
	            EventLog myLog = new EventLog();
	            myLog.Source = ews;
                myLog.WriteEntry(line, EventLogEntryType.Error);
            }
            System.Diagnostics.Trace.WriteLine(line);
            mut.ReleaseMutex();
        }
    }

    public class CookieAuthenticator
    {
        public CookieAuthenticator(string url, string userAgent, NetworkCredential credentials, string repo)
        {
            Uri uri = new Uri(url);
            this.Url = new UriBuilder(uri.Scheme, uri.Host, uri.Port).ToString();
            this.UserAgent = userAgent;
            this.Credential = credentials;
            this.Repository = repo;
        }
        NetworkCredential Credential
        {
            get;
            set;
        }
        string Url
        {
            get;
            set;
        }
        string ProxyUrl
        {
            get;
            set;
        }
        string UserAgent
        {
            set;
            get;
        }
        private CookieCollection Cookies
        {
            get;
            set;
        }
        private string[] Queries
        {
            get;
            set;
        }
        private string ValidationUrl
        {
            get;
            set;
        }
        private string Repository
        {
            get;
            set;
        }
        private void Connect()
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(this.Url);
            request.CookieContainer = new CookieContainer();
            request.UserAgent = this.UserAgent;
            Trace.WriteLine("Connect() Url = " + this.Url.ToString());
            Trace.WriteLine("Connect() UserAgent = " + this.UserAgent);
            //Do a GET on the SharePoint URL
            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            {
                //Get the UAG generated cookies from the response
                this.Cookies = response.Cookies;
                Trace.WriteLine("Connect() cookies " + this.Cookies.Count.ToString());
                //Get the query strings to construct login page URL
                if (!string.IsNullOrEmpty(response.ResponseUri.Query))
                {
                    this.Queries = response.ResponseUri.Query.Substring(1).Split(new string[] { "&" }, StringSplitOptions.RemoveEmptyEntries);
                    this.ValidationUrl = this.Url;
                    //Construct the login page URL
                    for (int i = 0; i < response.ResponseUri.Segments.Length - 1; i++)
                    {
                        this.ValidationUrl += response.ResponseUri.Segments[i];
                    }
                    this.ValidationUrl += "Validate.asp";
                    Trace.WriteLine("Connect() " + this.ValidationUrl);
                }
            }
        }

        public void Disconnect()
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(this.Url + "/InternalSite/LogoffMsg.asp");
            request.CookieContainer = new CookieContainer();
            request.UserAgent = this.UserAgent;
            //Do a GET on the SharePoint URL
            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse()) 
            {
                Trace.WriteLine("Disconnect() " + response.ResponseUri.ToString());
            };
        }

        private void ValidateCredentials()
        {
            Trace.WriteLine("ValidateCredentials()");

            //Construct the POST HTTP Request Data
            ASCIIEncoding encoding = new ASCIIEncoding();
            string postData = string.Empty;
            postData += string.Format("user_name={0}", this.Credential.UserName);
            postData += string.Format("&password={0}", this.Credential.Password);
            postData += string.Format("&repository={0}", this.Repository);
            foreach (var query in this.Queries)
            {
                if (query.Contains("site_name=")
                    || query.Contains("resource_id=")
                    || query.Contains("secure=")
                    || query.Contains("login_type="))
                    postData += "&" + query;
            }

//user_name=blahuser&password=blahpassword&repository=Extranet+Partners&site_name=eteams&secure=1&resource_id=A6F90491E9E44F57BDF64DF92F40038A&login_type=2

            byte[] data = encoding.GetBytes(postData);
            //Do a POST on the Login Page URL
            HttpWebRequest postRequest = (HttpWebRequest)WebRequest.Create(this.ValidationUrl);
            postRequest.ContentType = "application/x-www-form-urlencoded";
            postRequest.ContentLength = data.Length;
            postRequest.CookieContainer = new CookieContainer();
            foreach (Cookie cookie in this.Cookies)
            {
                postRequest.CookieContainer.Add(cookie);
            }

            postRequest.Method = "POST";
            postRequest.AllowAutoRedirect = true;
            using (Stream newStream = postRequest.GetRequestStream())
            {
                newStream.Write(data, 0, data.Length);
            }
            //get back the cookies
            using (HttpWebResponse response = (HttpWebResponse)postRequest.GetResponse())
            {
                Trace.WriteLine("ValidateCredentials() " + response.ResponseUri.ToString());
                if (response.ResponseUri.ToString().Contains("error_code"))
                {
                    Trace.WriteLine("ValidateCredentials() Invalid credentials");
                    throw new Exception("Invalid credentials");
                }

                this.Cookies = response.Cookies;
            }
        }

        public bool GetFile(string libraryname, string destinationfolder)
        {
            if (string.IsNullOrEmpty(destinationfolder))
            {
                Trace.WriteLine("GetFile() Destination folder not specifed. Skipping content download");
                return false;
            }
            Trace.WriteLine("GetFile() Destination folder " + destinationfolder);
            string filename = Path.GetFileName(libraryname);
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(this.Url + libraryname);
            request.Accept = "text/html, application/xhtml+xml, */*";
            request.Headers.Add(HttpRequestHeader.AcceptEncoding, "gzip,deflate");

            request.CookieContainer = new CookieContainer();
            request.UserAgent = this.UserAgent;

            if (this.Cookies != null)
            {
                foreach (Cookie cookie in this.Cookies)
                {
                    request.CookieContainer.Add(cookie);
                }
            }
            Trace.WriteLine("GetFile() request " + this.Url + libraryname);
            try
            {

                //Do a GET on the SharePoint URL
                using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                {
                    Stream responseStream = responseStream = response.GetResponseStream();
                    //if (response.ContentEncoding.ToLower().Contains("gzip"))
                    //responseStream = new GZipStream(responseStream, CompressionMode.Decompress);
                    //if (response.ContentEncoding.ToLower().Contains("deflate"))
                    //responseStream = new DeflateStream(responseStream, CompressionMode.Decompress);

                    StreamReader Reader = new StreamReader(responseStream, Encoding.Default);
                    //var stream = oFileInfo.Stream;
                    IList<byte> content = new List<byte>();
                    int b;
                    while ((b = responseStream.ReadByte()) != -1)
                    {
                        content.Add((byte)b);
                    }
                    var downloadFileName = Path.Combine(destinationfolder, Uri.UnescapeDataString(filename));
                    try
                    {
                        System.IO.File.WriteAllBytes(downloadFileName, content.ToArray());
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("GetFile() " + downloadFileName + ",error " + ex.Message);
                    }

                    Reader.Close();
                    response.Close();
                }
                //Trace.WriteLine("GetFile()" + this.ValidationUrl);
            }
            catch (Exception ex)
            {
                Trace.WriteLine("GetFile() " + ex.Message);
                return false;
            }
            return true;
        }

        public CookieCollection Authenticate()
        {
            this.Connect();
            this.ValidateCredentials();
            return this.Cookies;
        }
    }

    public class CSharePointClient
    {
        private CookieCollection cookies;
        private string m_serviceUrl;
        public string ServiceUrl
        {
            get { return m_serviceUrl; }
            set { m_serviceUrl = value; }
        }
        private string m_proxyUrl;
        public string ProxyUrl
        {
            get { return m_proxyUrl; }
            set { m_proxyUrl = value; }
        }
        private string m_proxyUser;
        public string ProxyUser
        {
            get { return m_proxyUser; }
            set { m_proxyUser = value; }
        }
        private string m_proxyPassword;
        public string ProxyPassword
        {
            get { return m_proxyPassword; }
            set { m_proxyPassword = value; }
        }

        private string m_proxyDomain;
        public string ProxyDomain
        {
            get { return m_proxyDomain; }
            set { m_proxyDomain = value; }
        }
        private bool m_bUseProxy;
        public bool UseProxy
        {
            get { return m_bUseProxy; }
            set { m_bUseProxy = value; }
        }

        private bool m_bBypassProxy;
        public bool BypassProxy
        {
            get { return m_bBypassProxy; }
            set { m_bBypassProxy = value; }
        }

        private string m_bypasslist;
        public string BypassList
        {
            get { return m_bypasslist; }
            set { m_bypasslist = value; }
        }

        private string m_proxyauthtype;
        public string ProxyAuthType
        {
            get { return m_proxyauthtype; }
            set { m_proxyauthtype = value; }
        }

        private string m_usr;
        public string User
        {
            get { return m_usr; }
            set
            {
                m_usr = value;
                if (m_usr.Contains('\\'))
                {
                    string[] parts = m_usr.Split('\\');
                    m_usr = parts[0];
                    if (parts.Length > 1)
                        m_domain = parts[1];
                }
            }
        }
        private string m_pwd;
        public string Password
        {
            get { return m_pwd; }
            set { m_pwd = value; }
        }
        private string m_domain;
        public string Domain
        {
            get { return m_domain; }
            set { m_domain = value; }
        }
        private string m_certfile;
        public string CertFile
        {
            get { return m_certfile; }
            set 
            {
                m_certfile = value;
                if (!string.IsNullOrEmpty(m_certfile))
                {
                    m_cert = X509Certificate.CreateFromCertFile(m_certfile);
                    Trace.WriteLine("CertFile() Loading cert file " + m_certfile);
                }

            }
        }
        private bool m_bNTLM;
        public bool NTLM
        {
            get { return m_bNTLM; }
            set { m_bNTLM = value; }
        }
        private ClientAuthenticationMode m_authmode;
        public int AuthMode
        {
            get { return (int)m_authmode; }
            set { m_authmode = (ClientAuthenticationMode)value; }
        }
        private string m_viewtitle;
        public string ViewTitle
        {
            get { return m_viewtitle; }
            set { m_viewtitle = value; }
        }

        private bool bInitialLoad;
        public bool InitialLoad
        {
            get { return bInitialLoad; }
            set { bInitialLoad = value; }
        }


        private CookieAuthenticator m_authenticator;
        public CookieAuthenticator Authenticator
        {
            get { return m_authenticator; }
            set { m_authenticator = value; }
        }
        private string m_userAgent;
        public string UserAgent
        {
            get { return m_userAgent; }
            set { m_userAgent = value; }
        }
        private string m_fuagAuth;
        public string FuagAuth
        {
            get { return m_fuagAuth; }
            set { m_fuagAuth = value.Replace(" ", "+").Trim(); }
        }

        private string m_LastError;
        public string LastError
        {
            get { return m_LastError; }
            set { m_LastError = value; }
        }
        private string m_contentfolder;
        public string ContentFolder
        {
            get { return m_contentfolder; }
            set 
            {
                if (value.EndsWith("\\"))
                    m_contentfolder = value;
                else
                    m_contentfolder = value + "\\";
            }
        }
        private X509Certificate m_cert;

        private bool m_exitnow;
        public bool ExitNow
        {
            get { return m_exitnow; }
            set { m_exitnow = value; }
        }

        private string m_authtype;
        public string AuthType
        {
            get { return m_authtype; }
            set { m_authtype = value; }
        }

        public void SetDebug(bool bDebug)
        {
            Trace.bDebug = bDebug;
        }

        private string m_exts;
        public string Extentions
        {
            get { return m_exts; }
            set { m_exts = value; }
        }

        private int m_updateinterval;
        public int UpdateInterval
        {
            get { return m_updateinterval; }
            set { m_updateinterval = value; }
        }
        private int m_updatetimeout;
        public int UpdateTimeout
        {
            get { return m_updatetimeout; }
            set { m_updatetimeout = value; }
        }
        public CSharePointClient()
        {
            m_context = null;
            m_dt = null;
            m_InProgress = false;
            m_exitnow = false;
            m_updateinterval = 60;
            bInitialLoad = true;
            m_userAgent = "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.1; WOW64; Trident/6.0)";
            using (Stream CertStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(GetType(), @"sharepointclient.cer"))
            {
                byte[] RawBytes = new byte[CertStream.Length];
                for (int Index = 0; Index < CertStream.Length; Index++)
                {
                    RawBytes[Index] = (byte)CertStream.ReadByte();
                }
                m_cert = new X509Certificate();
                m_cert.Import(RawBytes);
            }
            RegistryKey myreg = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Symon Communications\Symon Portal\System\Collectors\ShareView");
            m_exts = (string)myreg.GetValue("AllowedGraphicExts", ".jpg.png.gif.bmp.wdp.jpeg.xaml.xca.hdp");
        }

        ~CSharePointClient()
        {
        }

        void context_ExecutingWebRequest(object sender, WebRequestEventArgs e)
        {
            //Trace.WriteLine("ExecutingWebRequest() WebRequest received - " + e.WebRequestExecutor.WebRequest.RequestUri.ToString());
            HttpWebRequest webReq = e.WebRequestExecutor.WebRequest;
            webReq.UserAgent = m_userAgent;
            webReq.ClientCertificates.Add(m_cert);
            if (m_authtype.CompareTo("NTLM") == 0 || m_authtype.CompareTo("Negotiate") == 0)
            {
                try
                {
                    e.WebRequestExecutor.RequestHeaders.Add("X-FORMS_BASED_AUTH_ACCEPTED", "f");
                    //Trace.WriteLine("ExecutingWebRequest() Added header 'X-FORMS_BASED_AUTH_ACCEPTED','f'");
                }
                catch (Exception ex)
                {
                    Trace.WriteLine("ExecutingWebRequest() Error adding header 'X-FORMS_BASED_AUTH_ACCEPTED','f':" + ex.Message);
                }
            }
            if (this.cookies != null )
            {
                e.WebRequestExecutor.WebRequest.CookieContainer = new CookieContainer();
                foreach (Cookie cookie in this.cookies)
                {
                    //Trace.WriteLine("ExecutingWebRequest() Added cookie " + cookie.ToString());
                    e.WebRequestExecutor.WebRequest.CookieContainer.Add(cookie);
                }
            }
            else if (this.cookies == null && m_authtype.CompareTo("Claims-Based") == 0 )
            {
                string claimurl = m_serviceUrl + "/_windows/default.aspx?ReturnUrl=%2f_layouts%2fAuthenticate.aspx%3fSource%3d%252FDefault%252Easpx&Source=%2FDefault.aspx";
                //Trace.WriteLine("ExecutingWebRequest() Claim-based authentication:" + claimurl);
                CookieContainer Cookies = new CookieContainer();
                HttpWebRequest request = WebRequest.Create(claimurl) as HttpWebRequest;
                if (string.IsNullOrEmpty(m_usr) || string.IsNullOrEmpty(m_pwd))
                    request.Credentials = CredentialCache.DefaultNetworkCredentials;
                else
                    request.Credentials = new NetworkCredential(m_usr, m_pwd, m_domain);
                request.Method = "GET";
                request.CookieContainer = Cookies;
                request.AllowAutoRedirect = false;
                try
                { 
                    HttpWebResponse response = request.GetResponse() as HttpWebResponse;
                    if (null != response)
                    {
                        this.cookies = response.Cookies;
                    }
                    foreach (Cookie cookie in this.cookies)
                    {
                        //Trace.WriteLine("ExecutingWebRequest() Added cookie " + cookie.ToString());
                    }
                    e.WebRequestExecutor.WebRequest.CookieContainer = Cookies;
                }
                catch (Exception ex)
                {
                    Trace.WriteLine("ExecutingWebRequest() Claims based authetication error:" + ex.Message);
                }
            }
            if (m_bUseProxy && !String.IsNullOrEmpty(m_proxyUrl) && !String.IsNullOrEmpty(m_proxyUser) && !String.IsNullOrEmpty(m_proxyPassword))
            {
                Trace.WriteLine("ExecutingWebRequest() Using Proxy Url " + m_proxyUrl.ToString());
                webReq.Headers.Add("Proxy-Authorization", "Basic " + Convert.ToBase64String(ASCIIEncoding.ASCII.GetBytes(m_proxyUser + ":" + m_proxyPassword)));
            }
        }

        public int RowLimit { get; set; }
        public string OrderColumn { get; set; }
        public bool Ascending { get; set; }
        public string ThumbnailGroup { get; set; }
        ListItemCollectionPosition m_itemPosition = null;
        public bool MoreData
        {
            get { return m_itemPosition != null; }
        }

        private bool LoginToSharePoint(ClientContext context)
        {
            ServicePointManager.ServerCertificateValidationCallback = delegate(object sender, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors)
            {
                return true;
            };
            ServicePointManager.SecurityProtocol = System.Net.SecurityProtocolType.Tls;
            ServicePointManager.Expect100Continue = false;
            m_LastError = String.Empty;
            context.ExecutingWebRequest += new EventHandler<WebRequestEventArgs>(context_ExecutingWebRequest);
            Web web = context.Web;
            context.AuthenticationMode = m_authmode;
            if (Trace.bDebug)
            {
                Trace.WriteLine("LoginToSharePoint() AuthMode = " + m_authmode.ToString());
                Trace.WriteLine("LoginToSharePoint() AuthType = " + m_authtype.ToString());
            }
            if (m_bUseProxy)
            {
                System.Net.WebProxy pry = new System.Net.WebProxy();
                if (!String.IsNullOrEmpty(m_proxyUrl))
                {
                    pry.Address = new UriBuilder(m_proxyUrl).Uri;
                    Trace.WriteLine("LoginToSharePoint() Using proxy = " + pry.Address.ToString());
                }
                else
                {
                    try
                    {
                        pry.Address = WebRequest.DefaultWebProxy.GetProxy(new Uri(context.Url));
                        Trace.WriteLine("LoginToSharePoint() Getting proxy = " + pry.Address.ToString());
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("LoginToSharePoint() Exception '" + ex.Message + "' trying to get DefaultWebProxy");
                    }
                    finally
                    {
                        m_proxyUrl = pry.Address.ToString();
                    }
                }
                Trace.WriteLine("LoginToSharePoint() Proxy Url = " + m_proxyUrl);
                if (!String.IsNullOrEmpty(m_proxyUser) && !String.IsNullOrEmpty(m_proxyPassword))
                {
                    pry.UseDefaultCredentials = false;
                    Trace.WriteLine("LoginToSharePoint() Proxy User = " + m_proxyUser);
                    Trace.WriteLine("LoginToSharePoint() Proxy Pswd = " + new String('*', m_proxyPassword.Length));
                    pry.Credentials = new NetworkCredential(m_proxyUser, m_proxyPassword);
                }
                else
                {
                    pry.Credentials = CredentialCache.DefaultCredentials;
                    pry.UseDefaultCredentials = true;
                    if (Trace.bDebug)
                    {
                        Trace.WriteLine("LoginToSharePoint() Using DefaultCredentials");
                    }
                }

                pry.BypassProxyOnLocal = m_bBypassProxy;

                if (!String.IsNullOrEmpty(m_bypasslist))
                {
                    string[] bypasslist = m_bypasslist.Split(';');
                    if (bypasslist.Count() > 0)
                    {
                        pry.BypassList = bypasslist;
                    }
                }
                WebRequest.DefaultWebProxy = pry;
            }
            else
            {
                m_proxyUrl = null;
                WebRequest.DefaultWebProxy = null;
            }
            cookies = null;
            if (m_authmode == ClientAuthenticationMode.Default)
            {
                NetworkCredential nc = new NetworkCredential(m_usr, m_pwd, m_domain);
                if (!string.IsNullOrEmpty(m_usr) && Trace.bDebug)
                {
                    Trace.WriteLine("LoginToSharePoint() Usr = " + m_usr);
                    Trace.WriteLine("LoginToSharePoint() Pswd = " + new String('*', m_pwd.Length));
                    Trace.WriteLine("LoginToSharePoint() Domain = " + m_domain);
                }
                if (!string.IsNullOrEmpty(m_authtype))
                {
                    CredentialCache cc = new CredentialCache();
                    if (string.IsNullOrEmpty(m_usr) || string.IsNullOrEmpty(m_pwd))
                    {
                        cc.Add(new Uri(m_serviceUrl), m_authtype, CredentialCache.DefaultNetworkCredentials);
                        if ( Trace.bDebug )
                            Trace.WriteLine("LoginToSharePoint() Adding " + m_authtype + " with DefaultNetworkCredentials");
                    }
                    else
                    {
                        cc.Add(new Uri(m_serviceUrl), m_authtype, nc);
                        if (Trace.bDebug)
                            Trace.WriteLine("LoginToSharePoint() Adding " + m_authtype + " with '" + m_domain + "\\" + m_usr + "'");
                    }
                    context.Credentials = cc;
                  
                }
                if (!string.IsNullOrEmpty(m_fuagAuth) && !string.IsNullOrEmpty(m_usr))
                {
                    if (Trace.bDebug)
                        Trace.WriteLine("LoginToSharePoint() FuagAuth = '" + m_fuagAuth + "'");
                    m_authenticator = new CookieAuthenticator(m_serviceUrl, m_userAgent, (NetworkCredential)nc, m_fuagAuth);
                    try
                    {
                        if (!string.IsNullOrEmpty(m_fuagAuth))
                        {
                            this.cookies = m_authenticator.Authenticate();
                        }
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("LoginToSharePoint() failed." + ex.Message);
                        m_LastError = ex.Message;
                        return false;
                    }
                }
            }
            else if (m_authmode == ClientAuthenticationMode.FormsAuthentication)
            {
                FormsAuthenticationLoginInfo formsAuthInfo = new FormsAuthenticationLoginInfo(m_usr, m_pwd);
                context.FormsAuthenticationLoginInfo = formsAuthInfo;
            }
            return true;
        }
 
        public List<string> RetrieveLists()
        {
            Trace.WriteLine("RetrieveLists()" + m_serviceUrl);
            bInitialLoad = true;
            lastProcessedToken = null;
            m_LastError = String.Empty;
            List<string> retList = new List<string>();
            using (ClientContext context = new ClientContext(m_serviceUrl))
            {
                if (!LoginToSharePoint(context))
                {
                    context.Dispose();
                    return retList;
                }

                ListCollection collList = context.Web.Lists;
                BasePermissions permissions = new BasePermissions();
                permissions.Set(PermissionKind.ViewListItems);
                ConditionalScope scope = new ConditionalScope(context,
                    () => collList.ServerObjectIsNull.Value != true && context.Web.DoesUserHavePermissions(permissions).Value == true);
                using (scope.StartScope())
                {
                    context.Load(collList, w => w.Include(l => l.Title).Where(l => l.Title != null));
                }
                try
                {
                    //Trace.WriteLine("RetrieveLists() ExecuteQuery");
                    context.ExecuteQuery();
                    //Trace.WriteLine("RetrieveLists() ExecuteQuery succeeded");
                    if (scope.TestResult.HasValue && scope.TestResult.Value)
                    {
                        foreach (List oList in collList)
                            retList.Add(oList.Title);
                    }
                }
                catch (Exception ex)
                {
                    Trace.WriteLine("RetrieveLists():" + ex.Message + ":" + m_serviceUrl, true);
                    m_LastError = ex.Message;
                    context.Dispose();
                }
                if (!string.IsNullOrEmpty(m_fuagAuth))
                    m_authenticator.Disconnect();
            }
            return retList;
        }

        public List<string> RetrieveViews(string listName)
        {
            List<string> retViews = new List<string>();
            m_LastError = String.Empty;
            using (ClientContext context = new ClientContext(m_serviceUrl))
            {
                if (!LoginToSharePoint(context))
                {
                    context.Dispose();
                    return retViews;
                }

                var list = context.Web.Lists.GetByTitle(listName);
                var views = list.Views;
                if (list != null)
                {
                    context.Load(views);
                    try
                    {
                        context.ExecuteQuery();
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("RetrieveViews():" + ex.Message + ":" + m_serviceUrl, true);
                        context.Dispose();
                        m_LastError = ex.Message;
                        return retViews;
                    }
                    foreach (var v in views)
                    {
                        if ( v.Title.Length > 0 )
                            retViews.Add(v.Title);
                    }
                }
                if (!string.IsNullOrEmpty(m_fuagAuth))
                    m_authenticator.Disconnect();
            }
            return retViews;
        }

        public Dictionary<string, string> RetrieveFields(string listName)
        {
            m_LastError = String.Empty;
            Dictionary<string, string> retList = new Dictionary<string, string>();
            using (ClientContext context = new ClientContext(m_serviceUrl))
            {
                if (!LoginToSharePoint(context))
                {
                    context.Dispose();
                    return null;
                }

                var list = context.Web.Lists.GetByTitle(listName);
                var views = list.Views;
                if (list != null)
                {
                    context.Load(list, l => l.Title,
                        l => l.ItemCount,
                        l => l.Fields.Include(
                            f => f.Title,
                            f => f.Description,
                            f => f.TypeAsString,
                            f => f.InternalName).Where(f => f.Hidden == false));
                    context.Load(views);
                    try
                    {
                        context.ExecuteQuery();
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("RetrieveFields():" + ex.Message + ":" + m_serviceUrl, true);
                        context.Dispose();
                        m_LastError = ex.Message;
                        return null;
                    }
                    FieldCollection collField = list.Fields;

                    CamlQuery query = new CamlQuery();
                    Trace.WriteLine("RetrieveFields() for view '" + m_viewtitle + "'");
                    if (!string.IsNullOrEmpty(m_viewtitle))
                    {
                        Trace.WriteLine("RetrieveFields() Views count " + views.Count.ToString());
                        if (views != null)
                        {
                            foreach (var v in views)
                            {
                                if (v.Title == m_viewtitle)
                                {
                                    XDocument viewXml = XDocument.Parse(v.HtmlSchemaXml);
                                    query.ViewXml = viewXml.Element("View").ToString();
                                    break;
                                }
                            }
                        }
                    }
                    else
                        query.ViewXml = @"<View/>";
                    Trace.WriteLine("RetrieveFields() " + query.ViewXml);
                    ListItemCollection items = list.GetItems(query);

                    try
                    {
                        context.Load(items);
                        context.ExecuteQuery();
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("RetrieveFields() error " + ex.Message,  true);
                        context.Dispose();
                        m_LastError = ex.Message;
                        return null;
                    }
                    if (items.Count == 0)
                    {
                        foreach (var col in collField)
                        {
                            Trace.WriteLine("RetrieveFields() " + col.InternalName + "," + col.TypeAsString);
                            retList.Add(col.InternalName, col.TypeAsString);
                        }
                        retList.Add("images", "Text");
                    }
                    else
                    {
                        foreach (var col in collField)
                        {
                            foreach (var itemcol in items[0].FieldValues)
                            {
                                if (itemcol.Key.ToString() == col.InternalName)
                                {
                                    Trace.WriteLine("RetrieveFields() " +col.InternalName + "," + col.TypeAsString);
                                    retList.Add(col.InternalName, col.TypeAsString);
                                }
                            }
                        }
                        retList.Add("images", "Text");
                    }
                }

                if (!string.IsNullOrEmpty(m_fuagAuth))
                    m_authenticator.Disconnect();
            }
            return retList;
        }

        delegate void AsynchronousDelegate(string listname);
        public volatile bool m_InProgress = false;
        volatile DataTable m_dt = null;
        volatile ClientContext m_context = null;
        DateTime m_lastupdate;
        public DataTable RetrieveListItems(string listName)
        {
            TimeSpan ts;
            if (m_dt != null && !m_InProgress )
            {
                Trace.WriteLine(DateTime.Now.ToString("T") + " RetrieveListItems() - Data available.");
                DataTable dt = m_dt;
                m_dt = null;
                return dt;
            }
            if (m_context == null && !m_InProgress && m_dt == null)
            {
                m_exitnow = false;
                ts = DateTime.Now - m_lastupdate;
                if ((m_itemPosition == null && ts.TotalSeconds > m_updateinterval) || m_itemPosition != null)
                {
                    if (m_itemPosition != null)
                        Trace.WriteLine(DateTime.Now.ToString("T") + " RetrieveListItems() - start asynch bindGrid(). bMoreData");
                    else
                        Trace.WriteLine(DateTime.Now.ToString("T") + " RetrieveListItems() - start asynch bindGrid().");

                    m_InProgress = true;
                    AsynchronousDelegate eAsynch = new AsynchronousDelegate(bindGrid);
                    eAsynch.BeginInvoke(listName, null, null);
                    m_lastupdate = DateTime.Now;
                }
                return null;
            }
            ts = DateTime.Now - m_lastupdate;
            Trace.WriteLine(DateTime.Now.ToString("T") + " RetrieveListItems() - Data not retreived yet. Seconds since last update = " + ts.TotalSeconds.ToString());
            if (ts.TotalSeconds > m_updatetimeout)
            {
                Trace.WriteLine(DateTime.Now.ToString("T") + " RetrieveListItems() - timeout. Timeout = " + m_updatetimeout.ToString());
                m_LastError = "Timeout retrieving data";
                m_InProgress = false;
                if ( m_context != null)
                  m_context.Dispose();
                m_context = null;
                m_dt = null;
            }
            return null;
        }

        public bool IsImage(string url)
        {
            UriBuilder uri = new UriBuilder(url);
            string filename = Path.GetFileName(uri.Path);
            if (string.IsNullOrEmpty(m_contentfolder))
            {
                Trace.WriteLine("IsImage() Destination folder not specifed. Skipping content download. return FALSE.");
                return false;
            }
            else if (string.IsNullOrEmpty(filename))
            {
                Trace.WriteLine("IsImage() no filename");
                return false;
            }
            else if (!m_exts.Contains(Path.GetExtension(uri.Path).ToLower()))
            {
                Trace.WriteLine("IsImage() not an image. Ext = " + Path.GetExtension(uri.Path));
                return false;
            }
            else if (string.IsNullOrEmpty(Path.GetExtension(uri.Path)))
            {
                Trace.WriteLine("IsImage() not an image. Ext is blank");
                return false;
            }
            return true;
        }
        public bool CheckForExistence(string url, string listname, string scope)
        {
            UriBuilder uri = new UriBuilder(url);
            String relpath;
            if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(scope + "/"))
                relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(scope + "/", "");
            else
            {
                relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                relpath = relpath.Replace("//", "/");
            }
            var downloadFileName = Path.Combine(m_contentfolder, Uri.UnescapeDataString(relpath));
            if (System.IO.File.Exists(downloadFileName))
            {
                Trace.WriteLine("CheckForExistence(" + url + ")\n\t" + downloadFileName + " exists.");
                return true;
            }
            return false;
        }
        public bool DownLoadUrl(string url, string listname, string scope)
        {
            UriBuilder uri = new UriBuilder(url);
            string filename = Path.GetFileName(uri.Path);
            if ( IsImage(url) )
            {
                if (!string.IsNullOrEmpty(m_fuagAuth) && m_authenticator != null)
                {
                    if (m_authenticator.GetFile(uri.Path, m_contentfolder))
                    {
                        Trace.WriteLine("DownLoadUrl() return TRUE.");
                        return true;
                    }
                }
                else
                {
                    FileInformation oFileInfo = null;
                    try
                    {
                        Trace.WriteLine("DownLoadUrl(" + url + ") m_context.Url = " + m_context.Url.ToString());
                        Trace.WriteLine("DownLoadUrl(" + url + ") uri.Path = " + uri.Path);
                        Trace.WriteLine("DownLoadUrl(" + url + ") listname = " + listname);
                        Trace.WriteLine("DownLoadUrl(" + url + ") scope = " + scope);
                        Trace.WriteLine("DownLoadUrl(" + url + ") m_contentfolder = " + m_contentfolder);
                        String relpath;
                        if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(scope + "/"))
                            relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(scope + "/", "");
                        else
                        {
                            relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                            relpath = relpath.Replace("//", "/");
                        }
                        Trace.WriteLine("DownLoadUrl(" + url + ") relativepath = " + relpath);
                        oFileInfo = Microsoft.SharePoint.Client.File.OpenBinaryDirect(m_context, uri.Path);
                        var downloadFileName = Path.Combine(m_contentfolder, Uri.UnescapeDataString(relpath));
                        String folder = Path.GetDirectoryName(downloadFileName);
                        if (!Directory.Exists(folder))
                        {
                            Directory.CreateDirectory(folder);
                            Trace.WriteLine("DownLoadUrl(" + url + ") Created:" + folder);
                        }
                        using (Stream destFile = System.IO.File.OpenWrite(downloadFileName))
                        {
                            byte[] buffer = new byte[8 * 1024];
                            int len;
                            while ((len = oFileInfo.Stream.Read(buffer, 0, buffer.Length)) > 0)
                            {
                                destFile.Write(buffer, 0, len);
                            }
                        }
                        Trace.WriteLine("DownLoadUrl(" + url + ") Downloaded:" + downloadFileName);
                        Trace.WriteLine("DownLoadUrl(" + url + ") return TRUE.");
                        return true;
                    }
                    catch (TimeoutException ex)
                    {
                        Trace.WriteLine("DownLoadUrl(" + m_context.Url.ToString() + ") " + ex.Message);
                        return false;
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("DownLoadUrl(" + url + ") Exception:" + ex.Message + ". Attempting HttpWebRequest");
                        HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
                        request.Accept = "text/html, application/xhtml+xml, */*";
                        request.Headers.Add(HttpRequestHeader.AcceptEncoding, "gzip,deflate");
                        request.CookieContainer = new CookieContainer();
                        request.UserAgent = this.UserAgent;
                        try
                        {
                            if (!string.IsNullOrEmpty(m_authtype))
                            {
                                CredentialCache cc = new CredentialCache();
                                UriBuilder uriprefix = new UriBuilder(url);
                                string prefix = uriprefix.Scheme + "://" + uriprefix.Host + ":" + uriprefix.Port;
                                if (string.IsNullOrEmpty(m_usr) || string.IsNullOrEmpty(m_pwd))
                                {
                                    cc.Add(new Uri(prefix), m_authtype, CredentialCache.DefaultNetworkCredentials);
                                    Trace.WriteLine("DownLoadUrl(" + url + ") Adding " + m_authtype + " with DefaultNetworkCredentials");
                                }
                                else
                                {
                                    cc.Add(new Uri(prefix), m_authtype, new NetworkCredential(m_usr, m_pwd, m_domain));
                                    Trace.WriteLine("DownLoadUrl(" + url + ") Adding " + m_authtype + " with '" + m_domain + "\\" + m_usr + "'");
                                }
                                request.Credentials = cc;
                            }
                            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                            {
                                String relpath;
                                if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(scope + "/"))
                                    relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(scope + "/", "");
                                else
                                {
                                    relpath = listname + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                                    relpath = relpath.Replace("//", "/");
                                }
                                Trace.WriteLine("DownLoadUrl(" + url + ") relativepath = " + relpath);
                                var downloadFileName = Path.Combine(m_contentfolder, Uri.UnescapeDataString(relpath));
                                String folder = Path.GetDirectoryName(downloadFileName);
                                Stream responseStream = responseStream = response.GetResponseStream();
                                if (!Directory.Exists(folder))
                                {
                                    Directory.CreateDirectory(folder);
                                    Trace.WriteLine("DownLoadUrl(" + url + ") Created:" + folder);
                                }
                                using (Stream destFile = System.IO.File.OpenWrite(downloadFileName))
                                {
                                    byte[] buffer = new byte[8 * 1024];
                                    int len;
                                    while ((len = responseStream.Read(buffer, 0, buffer.Length)) > 0)
                                    {
                                        destFile.Write(buffer, 0, len);
                                    }
                                }
                                response.Close();
                                Trace.WriteLine("DownLoadUrl(" + url + ") Downloaded:" + downloadFileName);
                                return true;
                            }
                        }
                        catch (Exception ex1)
                        {
                            Trace.WriteLine("DownLoadUrl(" + url + ") " + ex1.Message, true);
                            return false;
                        }
                    }
                }
            }
            Trace.WriteLine("DownLoadUrl(" + url + ") return FALSE.");
            return false;
        }

        ChangeToken lastProcessedToken = null;
        ChangeCollection changes;
        public void bindGrid(string listName)
        {
            m_LastError = String.Empty;
            m_dt = new DataTable();
            using (m_context = new ClientContext(m_serviceUrl))
            {
                if (!LoginToSharePoint(m_context))
                {
                    m_context.Dispose();
                    m_context = null;
                    m_InProgress = false;
                    return;
                }
                Trace.WriteLine("bindGrid(" + m_context.Url + ") begin");

                var list = m_context.Web.Lists.GetByTitle(listName);
                var views = list.Views;
                //m_context.Load(list, l => l.RootFolder);
                //m_context.Load(list, l => l.RootFolder.Folders);
                if (list != null)
                {
                    m_context.Load(list, l => l.Title,
                       l => l.Id,
                       l => l.ItemCount,
                       l => l.Fields.Include(
                           f => f.Title,
                           f => f.Description,
                           f => f.TypeAsString,
                           f => f.Scope,
                           f => f.StaticName,
                           f => f.SchemaXml,
                           f => f.InternalName).Where(f => f.Hidden == false));
                    //m_context.Load(list.RootFolder.Folders);
                    m_context.Load(views);

                    try
                    {
                        //Trace.WriteLine("bindGrid() ExecuteQuery " + listName);
                        m_context.ExecuteQuery();
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("bindGrid(" + m_context.Url + ") error " + ex.Message, true);
                        m_LastError = ex.Message;
                        m_context.Dispose();
                        m_context = null;
                        m_InProgress = false;
                        return;
                    }
                    FieldCollection collField = list.Fields;
                    CamlQuery query = new CamlQuery();
                    //Trace.WriteLine("RetrieveFields() for view '" + m_viewtitle + "'");
                    if (!string.IsNullOrEmpty(m_viewtitle))
                    {
                        //Trace.WriteLine("RetrieveFields() Views count " + views.Count.ToString());
                        if (views != null)
                        {
                            foreach (var v in views)
                            {
                                //Trace.WriteLine("bindGrid() - View '" + v.Title + "'");
                                if (v.Title == m_viewtitle)
                                {
                                    XDocument viewXml = XDocument.Parse(v.HtmlSchemaXml);
                                    viewXml.Element("View").Add(new XAttribute("Scope", "RecursiveAll"));
                                    query.ViewXml = viewXml.Element("View").ToString();
                                    break;
                                }
                            }
                            if (string.IsNullOrEmpty(query.ViewXml))
                            {
                                //Trace.WriteLine("bindGrid() - View '" + m_viewtitle + "' not found",  true);
                                m_context.Dispose();
                                m_context = null;
                                m_InProgress = false;
                                return;

                            }
                        }
                    }
                    else
                        query.ViewXml = @"<View Scope='RecursiveAll'></View>";

                    query.ListItemCollectionPosition = m_itemPosition;
                    if (m_itemPosition != null)
                        Trace.WriteLine("bindGrid(" + m_context.Url + ") - continue data, m_itemPosition not null.");
                    else
                    {
                        ChangeQuery listChanges = new ChangeQuery(false, false);
                        listChanges.ChangeTokenStart = lastProcessedToken;
                        listChanges.Item = true;
                        listChanges.Add = true;
                        listChanges.DeleteObject = true;
                        listChanges.Update = true;
                        changes = list.GetChanges(listChanges);
                        try
                        {
                            m_context.Load(changes);
                            m_context.ExecuteQuery();
                            Trace.WriteLine("bindGrid(" + m_context.Url + ") - m_itemPosition is null. CHANGE COUNT = " + changes.Count.ToString());
                            foreach (Change change in changes)
                            {
                                if (change is Microsoft.SharePoint.Client.ChangeItem)
                                {
                                    ChangeItem ci = change as ChangeItem;
                                    Trace.WriteLine("bindGrid(" + m_context.Url + ") " + ci.ItemId.ToString() + ":" + ci.ChangeType.ToString());
                                    lastProcessedToken = ci.ChangeToken;
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            Trace.WriteLine("bindGrid(" + m_context.Url + ") changes(1):" + ex.Message, true);
                        }
                    }

                    ListItemCollection items = list.GetItems(query);
                    //Trace.WriteLine("bindGrid() - ExecuteQuery() " + query.ViewXml.ToString());
                    try
                    {
                        m_context.Load(items);
                        m_context.ExecuteQuery();
                        //Trace.WriteLine("bindGrid() - ExecuteQuery succeeded");
                        m_itemPosition = items.ListItemCollectionPosition;
                        if ( m_itemPosition != null )
                            Trace.WriteLine("bindGrid(" + m_context.Url + ") - all data not received. More data expected.");
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine("bindGrid(" + m_context.Url + ") - " + ex.Message, true);
                        m_LastError = ex.Message;
                        m_context.Dispose();
                        m_context = null;
                        m_InProgress = false;
                        return;
                    }
                    //Trace.WriteLine();
                    if (items.Count == 0)
                    {
                        foreach (var col in collField)
                        {
                            //Trace.WriteLine("");
                            //Trace.WriteLine("Title\t\t\t" + col.Title);
                            //Trace.WriteLine("Type\t\t\t" + col.TypeAsString);
                            //Trace.WriteLine("InternalName\t" + col.InternalName);
                            //Trace.WriteLine("Scope\t\t\t" + col.Scope);
                            //Trace.WriteLine("StaticName\t\t" + col.StaticName);
                            //Trace.WriteLine("SchemaXml\t\t" + col.SchemaXml);

                            m_dt.Columns.Add(col.InternalName);
                        }
                        m_dt.Columns.Add("images");
                    }
                    else
                    {
                        foreach (var fld in collField)
                        {
                            foreach (var itemcol in items[0].FieldValues)
                            {
                                if (itemcol.Key.ToString() == fld.InternalName)
                                {
                                    //Trace.WriteLine("");
                                    //Trace.WriteLine("Title\t\t\t" + fld.Title);
                                    //Trace.WriteLine("Type\t\t\t" + fld.TypeAsString);
                                    //Trace.WriteLine("InternalName\t" + fld.InternalName);
                                    //Trace.WriteLine("Scope\t\t\t" + fld.Scope);
                                    //Trace.WriteLine("StaticName\t\t" + fld.StaticName);
                                    //Trace.WriteLine("SchemaXml\t\t" + fld.SchemaXml);
                                    m_dt.Columns.Add(fld.InternalName);
                                }
                            }
                        }
                        m_dt.Columns.Add("images");
                    }

                    Trace.WriteLine("bindGrid(" + m_context.Url + ") - DT columns " + m_dt.Columns.Count.ToString() + ",Rows " + items.Count.ToString());
                    Trace.WriteLine("bindGrid(" + m_context.Url + ") - bInitialLoad = " + bInitialLoad.ToString());
                    foreach (var item in items)
                    {
                        
                        //Trace.WriteLine("ROW:" + item.Id.ToString());
                        if (ExitNow)
                            break;
                        bool updated = false;
                        if (bInitialLoad)
                        {
                            updated = true; // done for each row so images are re-downloaded
                        }
                        else
                        {
                            try
                            {
                                foreach (Change change in changes)
                                {
                                    if (change is Microsoft.SharePoint.Client.ChangeItem)
                                    {
                                        ChangeItem ci = change as ChangeItem;
                                        if (ci.ItemId == item.Id)
                                        {
                                            // only update row image if change for this item was detected.
                                            Trace.WriteLine("bindGrid(" + m_context.Url + ") - item " + item.Id.ToString() + " is in Change list. image will be re-downloaded");
                                            updated = true;
                                        }
                                    }
                                }
                            }
                            catch (Exception ex)
                            {
                                Trace.WriteLine("bindGrid(" + m_context.Url + ") changes(2):" + ex.Message, false);
                            }
                        }
                        //Trace.WriteLine("updated = "+ updated.ToString());
                
                        DataRow Row = m_dt.NewRow();
                        string images = string.Empty;
                        foreach (DataColumn col in m_dt.Columns)
                        {
                            if (ExitNow)
                                break;
                            //Trace.WriteLine("------------------------------------------------------------------");
                            //Trace.WriteLine("COLUMN:" + col.ToString());
                            if (col.ToString().CompareTo("images") == 0)
                            {
                                continue;
                            }
                            else if (item[col.ToString()] != null)
                            {
                                string fldtype = string.Empty;
                                string fldscope = string.Empty;
                                foreach (var fld in collField)
                                {
                                    if (fld.InternalName == col.ToString())
                                    {
                                        fldtype = fld.TypeAsString;
                                        fldscope = fld.Scope;
                                        break;
                                    }
                                }
                                //Trace.WriteLine("Type:"+item[col.ToString()].GetType().ToString());
                                //Trace.WriteLine("fldscope:" + fldscope);
                                if (item[col.ToString()].GetType() == typeof(Microsoft.SharePoint.Client.FieldUrlValue))
                                {
                                    string path = string.Empty;
                                    string url = ((Microsoft.SharePoint.Client.FieldUrlValue)(item[col.ToString()])).Url;
                                    if (!string.IsNullOrEmpty(url))
                                    {
                                        //Trace.WriteLine(url);
                                        try
                                        {
                                            bool gotimage = true;
                                            if (updated || !CheckForExistence(url, listName, fldscope))
                                                gotimage = DownLoadUrl(url, listName, fldscope);

                                            if (IsImage(url) && gotimage)
                                            {
                                                String subfile;
                                                if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(fldscope + "/"))
                                                    subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(fldscope + "/", "");
                                                else
                                                {
                                                    subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                                                    subfile = subfile.Replace("//", "/");
                                                }
                                                if (!String.IsNullOrEmpty(images))
                                                    images += "," + subfile;
                                                else
                                                    images = subfile;
                                                //Trace.WriteLine("images = " + images);
                                            }

                                        }
                                        catch (Exception ex)
                                        {
                                            Trace.WriteLine("bindGrid(" + m_context.Url + ") Column: " + col.ToString() + ", Error " + ex.Message, true);
                                        }
                                    }
                                    Row[col] = url;
                                }
                                else
                                {
                                    string value;
                                    if (item[col.ToString()].GetType() == typeof(Microsoft.SharePoint.Client.FieldUserValue))
                                    {
                                        value = ((Microsoft.SharePoint.Client.FieldUserValue)item[col.ToString()]).LookupValue;
                                        //Trace.WriteLine("bindGrid() - FieldUserValue:LookupValue for '" + col.ToString() + "' = " + value);
                                    }
                                    else if (item[col.ToString()].GetType() == typeof(Microsoft.SharePoint.Client.FieldUserValue[]))
                                    {
                                        FieldUserValue[] fuv = ((Microsoft.SharePoint.Client.FieldUserValue[])(item[col.ToString()]));
                                        string values = string.Empty;
                                        foreach (FieldUserValue uservalue in fuv)
                                            if (string.IsNullOrEmpty(values))
                                                values = uservalue.LookupValue;
                                            else
                                                values += ";" + uservalue.LookupValue;
                                        value = values;
                                        //Trace.WriteLine("bindGrid() - FieldUserValue[]:LookupValue for '" + col.ToString() + "' = " + value);
                                    }
                                    else if (item[col.ToString()].GetType() == typeof(String[]))
                                    {
                                        String[] sta = ((String[])(item[col.ToString()]));
                                        string values = string.Empty;
                                        foreach (String strvalue in sta)
                                            if (string.IsNullOrEmpty(values))
                                                values = strvalue;
                                            else
                                                values += ";" + strvalue;
                                        value = values;
                                        //Trace.WriteLine("bindGrid() - String[]: '" + col.ToString() + "' = " + value);
                                    }
                                    else if (item[col.ToString()].GetType() == typeof(Microsoft.SharePoint.Client.FieldLookupValue))
                                    {
                                        value = ((Microsoft.SharePoint.Client.FieldLookupValue)item[col.ToString()]).LookupValue;
                                        //Trace.WriteLine("bindGrid() - FieldLookupValue:LookupValue for '" + col.ToString() + "' = " + value);
                                    }
                                    else
                                    {
                                        value = item[col.ToString()].ToString();
                                    }
                                    if ( string.IsNullOrEmpty(value))
                                    {
                                        Row[col] = string.Empty;
                                        continue;
                                    }
                                    Match match = Regex.Match(value, @"<[^>]*");
                                    if (match.Success)
                                    {
                                        List<string> retImages = new List<String>();
                                        retImages = ExtractImages(item[col.ToString()].ToString());
                                        //Trace.WriteLine("Found " + retImages.Count.ToString() + " images.");
                                        foreach (string url in retImages)
                                        {
                                            //Trace.WriteLine(url);
                                            if (!string.IsNullOrEmpty(url))
                                            {
                                                try
                                                {
                                                    bool gotimage = true;
                                                    if (updated || !CheckForExistence(url, listName, fldscope))
                                                        gotimage = DownLoadUrl(url, listName, fldscope);

                                                    if (IsImage(url) && gotimage)
                                                    {
                                                        String subfile;
                                                        if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(fldscope + "/"))
                                                            subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(fldscope + "/", "");
                                                        else
                                                        {
                                                            subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                                                            subfile = subfile.Replace("//", "/");
                                                        }
                                                        if (!string.IsNullOrEmpty(images))
                                                            images += "," + subfile;
                                                        else
                                                            images = subfile;
                                                        //Trace.WriteLine("images = " + images);
                                                    }
                                                }
                                                catch (Exception ex)
                                                {
                                                    Trace.WriteLine("Column: " + col.ToString() + ", Error " + ex.Message);
                                                }
                                            }
                                        }
                                        //Trace.WriteLine("Stripping HTML on " + col.ToString());
										//Trace.WriteLine("value:" + value);
										string htmldecode = HttpUtility.HtmlDecode(value);
										//Trace.WriteLine("HtmlDecode():" + htmldecode);
										string stripped = StripHTML(htmldecode);
										//Trace.WriteLine("StripHTML():" + stripped);
                                        Row[col] = stripped;
                                    }
                                    else if (col.ToString().CompareTo("FieldLeafRef") == 0 || col.ToString().CompareTo("FileLeafRef") == 0)
                                    {
                                        UriBuilder uri = new UriBuilder();
                                        uri.Path = item["FileRef"].ToString();
                                        string url = uri.ToString();
                                        //Trace.WriteLine("Url using " + col.ToString() + ":" + url);
                                        try
                                        {
                                            if (item.FileSystemObjectType == FileSystemObjectType.Folder)
                                            {
                                                var foldername = Path.Combine(m_contentfolder, Uri.UnescapeDataString(Path.GetFileName(uri.Path)));
                                            }
                                            else
                                            {
                                                bool gotimage = true;
                                                if (updated || !CheckForExistence(url, listName, fldscope))
                                                    gotimage = DownLoadUrl(url, listName, fldscope);

                                                if (IsImage(url) && gotimage)
                                                {
                                                    String subfile;
                                                    if (Uri.UnescapeDataString(new UriBuilder(url).Path).Contains(fldscope + "/"))
                                                        subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path).Replace(fldscope + "/", "");
                                                    else
                                                    {
                                                        subfile = listName + "/" + Uri.UnescapeDataString(new UriBuilder(url).Path);
                                                        subfile = subfile.Replace("//", "/");
                                                    }
                                                    if (!string.IsNullOrEmpty(images))
                                                        images += "," + subfile;
                                                    else
                                                        images = subfile;
                                                    //Trace.WriteLine("images = " + images);
                                                }
                                            }

                                            Row[col] = value;
                                        }
                                        catch (Exception ex)
                                        {
                                            Trace.WriteLine("bindGrid(" + m_context.Url + ") Column: " + col.ToString() + ", Error " + ex.Message, true);
                                        }
                                    }
                                    else if (item[col.ToString()].GetType() == typeof(System.Int32) ||
                                             item[col.ToString()].GetType() == typeof(System.Int64))
                                    {
                                        //Trace.WriteLine("Integer");
                                        Row[col] = value;
                                    }
                                    else
                                    {
                                        //Trace.WriteLine("HtmlDecode");
                                        Row[col] = HttpUtility.HtmlDecode(value);
                                    }
                                }
                            }
                            //else
                            //    Trace.WriteLine("bindGrid(" + m_context.Url + ") - item for col " + col.ToString() + " is empty");
                        }
                        Row["images"]= images;
                        //Trace.WriteLine("Row['images'] = " + images);
                        m_dt.Rows.Add(Row);
                        m_lastupdate = DateTime.Now;
                    }
                }
                if (!string.IsNullOrEmpty(m_fuagAuth))
                    m_authenticator.Disconnect();
                Trace.WriteLine("bindGrid(" + m_context.Url + ") done");
            }
            m_context = null;
            m_InProgress = false;
            bInitialLoad = false;
        }

        public void killBindGrid()
        {
            if (m_context != null)
                m_context.Dispose();
            m_context = null;
            m_InProgress = false;
            bInitialLoad = true;
        }

        public string StripHTML(string source)
        {
            try
            {
                string result;

                // Remove HTML Development formatting
                // Replace line breaks with space
                // because browsers inserts space
                result = source.Replace("\r", " ");
                // Replace line breaks with space
                // because browsers inserts space
                result = result.Replace("\n", " ");
                // Remove step-formatting
                result = result.Replace("\t", string.Empty);
                // Remove repeating spaces because browsers ignore them
                result = System.Text.RegularExpressions.Regex.Replace(result,
                                                                      @"( )+", " ");

                // Remove the header (prepare first by clearing attributes)
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*head([^>])*>", "<head>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"(<( )*(/)( )*head( )*>)", "</head>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(<head>).*(</head>)", string.Empty,
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // remove all scripts (prepare first by clearing attributes)
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*script([^>])*>", "<script>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"(<( )*(/)( )*script( )*>)", "</script>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                //result = System.Text.RegularExpressions.Regex.Replace(result,
                //         @"(<script>)([^(<script>\.</script>)])*(</script>)",
                //         string.Empty,
                //         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"(<script>).*(</script>)", string.Empty,
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // remove all styles (prepare first by clearing attributes)
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*style([^>])*>", "<style>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"(<( )*(/)( )*style( )*>)", "</style>",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(<style>).*(</style>)", string.Empty,
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // insert tabs in spaces of <td> tags
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*td([^>])*>", "\t",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // insert line breaks in places of <BR> and <LI> tags
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*br( )*>", "\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*li( )*>", "\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // insert line paragraphs (double line breaks) in place
                // if <P>, <DIV> and <TR> tags
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*div([^>])*>", "\r\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*tr([^>])*>", "\r\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<( )*p([^>])*>", "\r\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // Remove remaining tags like <a>, links, images,
                // comments etc - anything that's enclosed inside < >
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"<[^>]*>", string.Empty,
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // replace special characters:
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @" ", " ",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&bull;", " * ",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&lsaquo;", "<",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&rsaquo;", ">",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&trade;", "(tm)",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&frasl;", "/",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&lt;", "<",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&gt;", ">",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&copy;", "(c)",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&reg;", "(r)",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                // Remove all others. More can be added, see
                // http://hotwired.lycos.com/webmonkey/reference/special_characters/
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         @"&(.{2,6});", string.Empty,
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // for testing
                //System.Text.RegularExpressions.Regex.Replace(result,
                //       this.txtRegex.Text,string.Empty,
                //       System.Text.RegularExpressions.RegexOptions.IgnoreCase);

                // make line breaking consistent
                result = result.Replace("\n", "\r");

                // Remove extra line breaks and tabs:
                // replace over 2 breaks with 2 and over 4 tabs with 4.
                // Prepare first to remove any whitespaces in between
                // the escaped characters and remove redundant tabs in between line breaks
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\r)( )+(\r)", "\r\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\t)( )+(\t)", "\t\t",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\t)( )+(\r)", "\t\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\r)( )+(\t)", "\r\t",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                // Remove redundant tabs
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\r)(\t)+(\r)", "\r\r",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                // Remove multiple tabs following a line break with just one tab
                result = System.Text.RegularExpressions.Regex.Replace(result,
                         "(\r)(\t)+", "\r\t",
                         System.Text.RegularExpressions.RegexOptions.IgnoreCase);
                // Initial replacement target string for line breaks
                string breaks = "\r\r\r";
                // Initial replacement target string for tabs
                string tabs = "\t\t\t\t\t";
                for (int index = 0; index < result.Length; index++)
                {
                    result = result.Replace(breaks, "\r\r");
                    result = result.Replace(tabs, "\t\t\t\t");
                    breaks = breaks + "\r";
                    tabs = tabs + "\t";
                }
                // That's it.
                return result;
            }
            catch
            {
                return source;
            }
        }

        private void ShowTable(DataTable table)
        {
            foreach (DataColumn col in table.Columns)
            {
                Trace.Write("{0,-14}", col.ColumnName);
            }
            Trace.WriteLine();

            foreach (DataRow row in table.Rows)
            {
                foreach (DataColumn col in table.Columns)
                {
                    if (col.DataType.Equals(typeof(DateTime)))
                        Trace.Write("{0,-14:d}", row[col]);
                    else if (col.DataType.Equals(typeof(Decimal)))
                        Trace.Write("{0,-14:C}", row[col]);
                    else
                        Trace.Write("{0,-14}", row[col]);
                }
                Trace.WriteLine();
            }
            Trace.WriteLine();
        }

        public List<string> ExtractImages(string source)
        {
            List<string> retImages = new List<string>();
            // insert tabs in spaces of <td> tags
            int pos, pos1;
            string image;
            foreach (Match m in Regex.Matches
                (source, "<img[^>]* src=\"([^\"]*)\"[^>]*>", System.Text.RegularExpressions.RegexOptions.IgnoreCase))
            {
                pos = m.Value.IndexOf("src=");
                pos1 = m.Value.IndexOf('"', pos+5);
                image = m.Value.Substring(pos+5, pos1 - (pos + 5));
                if ( !retImages.Contains(image) )                    
                 retImages.Add(image);
            }
            return retImages;
        }

        static void Main(string[] args)
        {
            CSharePointClient spc = new CSharePointClient();
            spc.ServiceUrl = "http://www.xsolive.com/";
            spc.AuthMode = 0;
            //spc.AuthMode = ClientAuthenticationMode.Anonymous;
            //spc.AuthMode = ClientAuthenticationMode.FormsAuthentication;
            spc.m_usr = "test@xsolive.com";
            spc.m_pwd = "Xsolive2010";
            spc.CertFile = @"E:\dev\Symon2010\sources\12.0\InternalTools\FirstClientApiApplication\test.cer";
            List<string> rlist = spc.RetrieveLists();
            Dictionary<string,string> flist = spc.RetrieveFields(rlist[0]);
            //spc.RetrieveListItems(rlist[0]);
        }
   
    }

}
