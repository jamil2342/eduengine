using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace FASTMONEY
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
                String ews = "FastMoney";
                if (!EventLog.SourceExists("FastMoneyClient"))
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
        public CookieAuthenticator(string url)
        {
            Uri uri = new Uri(url);
            this.Url = new UriBuilder(uri.Scheme, uri.Host, uri.Port).ToString();
            //this.UserAgent = userAgent;
            //this.Credential = credentials;
            //this.Repository = repo;
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
            // HttpWebRequest request = (HttpWebRequest)WebRequest.Create(this.Url);
            this.Url = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";
            HttpWebRequest request = WebRequest.Create(new Uri(this.Url)) as HttpWebRequest;
            request.CookieContainer = new CookieContainer();
             request.UserAgent = this.UserAgent;
            Trace.WriteLine("Connect() Url = " + this.Url.ToString());
            Trace.WriteLine("Connect() UserAgent = " + this.UserAgent);
            //Do a GET on the First Money URL
            // Set type to POST
            request.Method = "POST";

            // Create the data we want to send
            /*
            StringBuilder data = new StringBuilder();
            byte[] byteData = Encoding.UTF8.GetBytes(data.ToString());      // Create a byte array of the data we want to send
            request.ContentLength = byteData.Length;                        // Set the content length in the request headers

            // Write data to request
            using (Stream postStream = request.GetRequestStream())
            {
                postStream.Write(byteData, 0, byteData.Length);
            }
            */
            try
            {

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
            catch (Exception)
            {
            }

            /*
            HttpWebRequest request = WebRequest.Create(new Uri(this.Url)) as HttpWebRequest;

            // Set type to POST
            request.Method = "POST";

            // Create the data we want to send
            StringBuilder data = new StringBuilder();
            byte[] byteData = Encoding.UTF8.GetBytes(data.ToString());      // Create a byte array of the data we want to send
            request.ContentLength = byteData.Length;                        // Set the content length in the request headers

            // Write data to request
            using (Stream postStream = request.GetRequestStream())
            {
                postStream.Write(byteData, 0, byteData.Length);
            }

            // Get response and return it
            XmlDocument xmlResult = new XmlDocument();
            try
            {
                using (HttpWebResponse response = request.GetResponse() as HttpWebResponse)
                {
                    StreamReader reader = new StreamReader(response.GetResponseStream());
                   // result = reader.ReadToEnd();
                    reader.Close();
                }
               // xmlResult.LoadXml(result);
            }
            catch (Exception e)
            {
                xmlResult = new XmlDocument();
            }
             * */

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

        public CookieCollection Authenticate()
        {
            this.Connect();
            this.ValidateCredentials();
            return this.Cookies;
        }
    }
    public class FastMoneyClient
    {
        private CookieCollection cookies;

        private CookieAuthenticator m_authenticator;
        public CookieAuthenticator Authenticator
        {
            get { return m_authenticator; }
            set { m_authenticator = value; }
        }
        string Url
        {
            get;
            set;
        }

        public DataTable GetFastMoney()
        {
            string result = "";

            this.Url = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";


            // Create the web request
            HttpWebRequest request = WebRequest.Create(new Uri(this.Url)) as HttpWebRequest;

            // Set type to POST
            request.Method = "POST";

            // Create the data we want to send
            StringBuilder data = new StringBuilder();
            byte[] byteData = Encoding.UTF8.GetBytes(data.ToString());      // Create a byte array of the data we want to send
            request.ContentLength = byteData.Length;                        // Set the content length in the request headers

            // Write data to request
            using (Stream postStream = request.GetRequestStream())
            {
                postStream.Write(byteData, 0, byteData.Length);
            }

            // Get response and return it
            XmlDocument xmlResult = new XmlDocument();
            try
            {
                using (HttpWebResponse response = request.GetResponse() as HttpWebResponse)
                {
                    StreamReader reader = new StreamReader(response.GetResponseStream());
                    result = reader.ReadToEnd();
                    reader.Close();
                }
                xmlResult.LoadXml(result);
            }
            catch (Exception e)
            {
                xmlResult = new XmlDocument();
            }

            XmlReader xmlReader = new XmlNodeReader(xmlResult);

            var xmlTag = xmlResult.GetElementsByTagName("item");

            DataTable dtFM = ConvertXmlNodeListToDataTable(xmlTag);
            return dtFM;
        }
        public DataTable ConvertXmlNodeListToDataTable(XmlNodeList xmlTag)
        {
            DataTable dt = new DataTable();
            int TempColumn = 0;

            foreach (XmlNode node in xmlTag.Item(0).ChildNodes)
            {
                TempColumn++;
                DataColumn dc = new DataColumn(node.Name, System.Type.GetType("System.String"));
                if (dt.Columns.Contains(node.Name))
                {
                    dt.Columns.Add(dc.ColumnName = dc.ColumnName + TempColumn.ToString());
                }
                else
                {
                    dt.Columns.Add(dc);
                }
            }

            int ColumnsCount = dt.Columns.Count;
            for (int i = 0; i < xmlTag.Count; i++)
            {
                DataRow dr = dt.NewRow();
                for (int j = 0; j < ColumnsCount; j++)
                {
                    dr[j] = xmlTag.Item(i).ChildNodes[j].InnerText;
                }
                dt.Rows.Add(dr);
            }
            return dt;
        }
       
        public Item[] GetFastMoney(String Url)
        {

           // string Url = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";


            HttpClient client = new HttpClient();
            HttpResponseMessage response = client.GetAsync(Url).Result;
            string str = response.Content.ReadAsStringAsync().Result;
            XmlSerializer serializer = new XmlSerializer(typeof(Rss));
            StringReader rdr = new StringReader(str);
            Rss resultingMessage = (Rss)serializer.Deserialize(rdr);
            return resultingMessage.Channel.Item.ToArray();


        }
       
    }
}
