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


            int startIndex = mainStr.IndexOf(startStr);
            string temp = mainStr.Substring(startIndex+startStr.Length);

            int len = temp.IndexOf(endStr);
            //len = len - endStr.Length;
            temp = temp.Remove(len);
            temp=temp.Replace("\n","");
            temp=temp.Replace("\r","");
            return temp;

            //string temp = mainStr.Substring(startIndex+startStr.Length, endIndex-endStr.Length+1);
            //temp = temp.Remove(endIndex);
            //return temp;

            //string temp = "";
            //int startIndex = mainStr.IndexOf(startStr);
            
            //int endIndex = mainStr.Substring(startIndex).IndexOf(endStr);
            
            
            //{
            //    temp = mainStr.Substring(startIndex + startStr.Length, endIndex); 
            //}
            //temp = temp.Replace(endStr, "");
            //return temp;

        
        }

        public static string tokenString(string mainStr,string firstStart, string startStr, string endStr)
        {
            string delemetedString = "";
            int temp=mainStr.IndexOf(firstStart);
            delemetedString=mainStr.Remove(0, temp);


            
            
            
            
            return tokenString(delemetedString, startStr, endStr);



        }


    }
}
