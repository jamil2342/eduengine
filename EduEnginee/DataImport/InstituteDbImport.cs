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
    public partial class InstituteDbImport : Form
    {
        public InstituteDbImport()
        {
            InitializeComponent();
        }
        public String tempQry = @"UPDATE Institutes
SET       Title =#Title, HeadName =#, Phone =#, EmailAddress =#, WebSite =#, EstablishDate =#, NoOfMaleStd =#, NoOfFemaleStd =#, NoOfTeacher =#, NoOfMaleHostelSit =#, NoOfFemaleHostelSit =#, Location =#";

        public class institute
        {
            public  string Title; 
            public string  HeadName ; 
            public string  Phone ; 
            public string  EmailAddress ;
            public string  WebSite ; 
            public string  EstablishDate ;
            public string  NoOfMaleStd ;
            public string  NoOfFemaleStd ;
            public string  NoOfTeacher ; 
            public string  NoOfMaleHostelSit ;
            public string  NoOfFemaleHostelSit ; 
            public string  Location ;

        }

        List<institute> insList = new List<institute>();
        private void SubmitTb_Click(object sender, EventArgs e)
        {
            int startId = Convert.ToInt32(StartIdTb.Text);
            int endId = Convert.ToInt32(EndIdTb.Text);
            string totalHtml = "";
            string tempUrl = "http://www.eduicon.com/Institute/?Institute_Basic_ID=";
            institute tempInstitute = new institute();
            
            
            //for Title <font style="font-size: 20px;">Ad-din Womens Medical College</font>
            
            


            /*
             
             for location
             * 
             * (BUET)</font><br>
							Dhaka-1000<br>
							Phone
             */



            /*
             for phone
             * 
							Phone: 02-9665650-80, 8616833-38, 8614640-44, 8618344-49 , Fax: 02-8613046<br>
             
             */
            for (int i = startId; i <= endId; i++)
            {
                
                totalHtml = WebFetch.GetHtml(tempUrl+i);
                tempInstitute.Title=MyString.tokenString(totalHtml,"<font style=\"font-size: 20px;\">","</font>");
                tempInstitute.Location = MyString.tokenString(totalHtml, "</font><br>", "<br>");
                tempInstitute.Phone = MyString.tokenString(totalHtml, "Phone: ", "<br>");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");
                tempInstitute.Location = MyString.tokenString(totalHtml, "", "");

            }
        }
    }
}
