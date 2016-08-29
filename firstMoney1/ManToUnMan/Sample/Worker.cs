using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Net;
using System.Net.Http;


namespace Sample
{
    public class item
    {
        public int id;
        public int name;
        public item()
        {
            id = 10;
            name = 100;
        }
    }
    
    
    
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


        public item[] callWebService()
        {

            string page = "http://podcast.cnbc.com/mmpodcast/fastmoney.xml";


            HttpClient client = new HttpClient();
            HttpResponseMessage response = client.GetAsync(page).Result;
            string str = response.Content.ReadAsStringAsync().Result;
            item[] i = new item[2];

            return i;

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
