using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Net;
using System.Net.Http;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace Sample
{

    [XmlRoot(ElementName="item")]
	public class Item {
		[XmlElement(ElementName="title")]
		public string Title { get; set; }
		[XmlElement(ElementName="pubDate")]
		public string PubDate { get; set; }
		[XmlElement(ElementName="author")]
		public List<string> Author { get; set; }
		[XmlElement(ElementName="link")]
		public string Link { get; set; }
		[XmlElement(ElementName="description")]
		public string Description { get; set; }
        //[XmlElement(ElementName="category", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public Category Category { get; set; }
        //[XmlElement(ElementName="source")]
        //public Source Source { get; set; }
        //[XmlElement(ElementName="subtitle", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Subtitle { get; set; }
        //[XmlElement(ElementName="duration", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Duration { get; set; }
        //[XmlElement(ElementName="summary", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Summary { get; set; }
        //[XmlElement(ElementName="explicit", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Explicit { get; set; }
        //[XmlElement(ElementName="block", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Block { get; set; }
        //[XmlElement(ElementName="keywords", Namespace="http://www.itunes.com/dtds/podcast-1.0.dtd")]
        //public string Keywords { get; set; }
        //[XmlElement(ElementName="guid")]
        //public string Guid { get; set; }
        //[XmlElement(ElementName="enclosure")]
        //public Enclosure Enclosure { get; set; }
	}
    //public class item
    //{
    //    public string title ;
    //    public string  pubDate;
    //    public string  ;
    //    public string  ;
    //    public string  ;
        
    //    //public int id;
    //    //public int name;
    //    //public item()
    //    //{
    //    //    id = 10;
    //    //    name = 100;
    //    //}
    //}
    
    
    
    public class Worker
    {
        /// <summary>
        /// Callback method signature to send array of values.
        /// </summary>
        /// <param name="values">The values.</param>
        public delegate void FloatValuesReady(float[] values);

        /// <summary>
        /// Occurs when [float values are ready].
        /// </summary>
        public event FloatValuesReady ReadFloatValues;

        /// <summary>
        /// Sums the specified i.
        /// </summary>
        /// <param name="i">The i.</param>
        /// <param name="j">The j.</param>
        /// <returns></returns>
        public int Sum(int i, int j)
        {
            //HttpClient client
            return i + j + 1;
        }
        public Item[] callWebService1()
        {

            string page = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";


            HttpClient client = new HttpClient();
            HttpResponseMessage response = client.GetAsync(page).Result;
            string str = response.Content.ReadAsStringAsync().Result;
            
            Item[] i = new Item[2];
            i[0] = new Item();
            i[1] = new Item();
            //i[0].id = 10;
            //i[0].name = 100;
            //i[0].id = 10;
            //i[0].name = 100;

            //String URLString = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";
            //XmlTextReader reader = new XmlTextReader(URLString);

            //while (reader.Read())
            //{
            //    switch (reader.NodeType)
            //    {
            //        case XmlNodeType.Element: // The node is an element.
            //            Console.Write("<" + reader.Name);

            //            while (reader.MoveToNextAttribute()) // Read the attributes.
            //                Console.Write(" " + reader.Name + "='" + reader.Value + "'");
            //            Console.Write(">");
            //            Console.WriteLine(">");
            //            break;
            //        case XmlNodeType.Text: //Display the text in each element.
            //            Console.WriteLine(reader.Value);
            //            break;
            //        case XmlNodeType.EndElement: //Display the end of the element.
            //            Console.Write("</" + reader.Name);
            //            Console.WriteLine(">");
            //            break;
            //    }
            //}
            int firstIndex = str.IndexOf("<language>en</language>")+23;
            int lastIndex = str.IndexOf("</channel>");
            int len = lastIndex - firstIndex;
            str = str.Substring(firstIndex, len);
            XmlSerializer serializer = new XmlSerializer(typeof(Item));
            StringReader rdr = new StringReader(str);
            Item resultingMessage = (Item)serializer.Deserialize(rdr);
            return i;

        }

        public string callWebService()
        {

            string page = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";


            HttpClient client = new HttpClient();
            HttpResponseMessage response = client.GetAsync(page).Result;
            string str = response.Content.ReadAsStringAsync().Result;
            return str;
            //item[] i = new item[2];

            //return i;

        }

        /// <summary>
        /// Gets the Student object.
        /// </summary>
        /// <returns></returns>
        public ManagedStudent GetStudent()
        {
            Console.WriteLine("Enter a Name:");
            string text = Console.ReadLine();
            if (text != string.Empty)
            {
                return new ManagedStudent { Name = text };
            }
            return new ManagedStudent { Name = "NoName" };
        }

        /// <summary>
        /// Read some float values from Console and give it back to the caller using ReadFloatValues callback.
        /// So Caller should add event handler to ReadFloatValues event.
        /// </summary>
        public void GetSomeFloatValues()
        {
            List<float> values = new List<float>();
            Console.WriteLine("Enter 4 valid float values for the Native App");
            while (values.Count < 4)
            {
                string valueText = Console.ReadLine();
                float value;
                if (float.TryParse(valueText, out value))
                {
                    values.Add(value);
                }
            }
            if (this.ReadFloatValues != null)
            {
                this.ReadFloatValues(values.ToArray());
            }
        }
    }

    /// <summary>
    /// A Managed Class
    /// </summary>
    public class ManagedStudent
    {
        public int sum()
        {
            return 100;
        }
        public string Name { get; set; }
    }
}
