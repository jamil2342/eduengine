using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataImport
{
    class MyString
    {
        public MyString()
        { 
        
        }

        public static string tokenString(string mainStr,string startStr,string endStr)
        {
            string temp = "";
            int startIndex = mainStr.IndexOf(startStr);
            int endIndex = mainStr.IndexOf(endStr);
            int len=endIndex-startIndex-startStr.Length;
            if (len>0)
            {
                temp = mainStr.Substring(startIndex + startStr.Length, len); 
            }
            return temp;

        
        }
    }
}
