using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace DataImport
{
    public partial class Form1 : Form
    {
        string input = "";
        string output = "";
        public Form1()
        {
            InitializeComponent();
        }
        string temp = "";
        int currentPos = 0;
        int nextPos = 0;
        List<string> inCat = new List<string>();
        
        
        private void submitBtn_Click(object sender, EventArgs e)
        {
            input = inputTb.Text;
            while (input.Length>0)
	        {
                string temp = "";
                currentPos = input.IndexOf("<h2");
                nextPos = input.IndexOf('\n', currentPos);
                temp = input.Substring(currentPos, nextPos - currentPos);
                inCat.Add(temp);
                input = input.Replace(temp, "");

	        }
            //for (int i = 0; i < input.Length; i++)
            //{

            //    if (input[i]=='\"'&& input[i+1]=='>')
            //    {
            //        string temp = "";
            //        for (int j = i+2; ; j++)
            //        {
            //            temp+=input[j];
            //            if (input[j] == '<' && input[j + 1] == '/')
            //            {
                            
            //            }
            //        }                    
            //    }
                
            //}
               
             
        }
    }
}
