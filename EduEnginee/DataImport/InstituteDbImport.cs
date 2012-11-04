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


        public class institute
        {
            public int Id;
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
        
        string output = "";
        
        public String tempQry = @"UPDATE Institutes
SET       Title ='#Title', HeadName ='#HeadName', Phone ='#Phone', EmailAddress ='#EmailAddress', WebSite ='#WebSite', EstablishDate =#EstablishDate, NoOfMaleStd =#NoOfMaleStd, NoOfFemaleStd =#NoOfFemaleStd, NoOfTeacher =#NoOfTeacher, NoOfMaleHostelSit =#NoOfMaleHostelSit, NoOfFemaleHostelSit =#NoOfFemaleHostelSit, Location ='#Location'
where Id=#Id;\n";

        int startId = 0;
        int endId = 0;
        private void SubmitTb_Click(object sender, EventArgs e)
        {
            insList.Clear();
            startId = Convert.ToInt32(StartIdTb.Text);
            endId = Convert.ToInt32(EndIdTb.Text);
            string totalHtml = "";
            string tempUrl = "http://www.eduicon.com/Institute/?Institute_Basic_ID=";
            institute tempInstitute = new institute();
            
            string finalQry = "";
            //for Title <font style="font-size: 20px;">Ad-din Womens Medical College</font>
            	//<title>Bangladesh University of Engineering and Technology (BUET)</title>
            
            


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



            //for email
            //    <a href="mailto:vcoffice@vc.buet.ac.bd" target="_blank" class="email" title="vcoffice@vc.buet.ac.bd">Email</a>
            //    <a href="mailto:duet@duet.ac.bd" target="_blank" class="email" title="duet@duet.ac.bd">Email</a>
							
			
            
            //for Web
            //                                    <a href="http://www.duet.ac.bd" target="_blank" class="web" title="http://www.duet.ac.bd">Website</a>
            //                                    <a href="http://www.buet.ac.bd" target="_blank" class="web" title="http://www.buet.ac.bd">Website</a>
            
            //,


            //for headname
            //    <p class="head" style="margin-left: 18px;">Prof Dr SM Nazrul Islam</p>
            //    <p class="head" style="margin-left: 18px;">Professor Dr.Mohammed Alauddin</p>
            
        //for maile student

        //                    <td width="38%">Male Student</td>
        //                    <td width="5%">:</td>
        //                    <td align="right" width="7%">5876</td>


            //No of female student
            //    <td>Female Student</td>
            //                <td>:</td>
            //                <td align="right">1269</td>


            //total teacher
            //    <td>Total Teacher</td>
            //                <td>:</td>
            //                <td align="right">496</td>


            //<td>Male Hostel Seat</td>
            //                <td>:</td>
            //                <td align="right">2482</td>
						
            for (int i = startId; i <= endId; i++)
            {

                
                totalHtml = WebFetch.GetHtml(tempUrl+i);
                tempInstitute.Id = i;
                
                tempInstitute.Title = MyString.tokenString(totalHtml, "<title>", "</title>");
                tempInstitute.Location = MyString.tokenString(totalHtml,"</title>", "</font><br>", "<br>");
                tempInstitute.EstablishDate = MyString.tokenString(totalHtml, "Established in ", "</font>");
                tempInstitute.Location= tempInstitute.Location.Replace("\t","");
                tempInstitute.Phone = MyString.tokenString(totalHtml, "Phone: ", "<br>");
                tempInstitute.EmailAddress = MyString.tokenString(totalHtml, "mailto:", "\"");
                tempInstitute.WebSite = MyString.tokenString(totalHtml, "class=\"web\" title=\"", "\">Website");
                tempInstitute.HeadName = MyString.tokenString(totalHtml, "<p class=\"head\" style=\"margin-left: 18px;\">", "</p>");
                tempInstitute.NoOfMaleStd = MyString.tokenString(totalHtml, "Male Student", "align=\"right\">", "</td>");
                tempInstitute.NoOfFemaleStd = MyString.tokenString(totalHtml, "Female Student","<td align=\"right\">", "</td>");
                tempInstitute.NoOfTeacher = MyString.tokenString(totalHtml, "Total Teacher", "<td align=\"right\">", "</td>");
                tempInstitute.NoOfMaleHostelSit = MyString.tokenString(totalHtml, "Male Hostel Seat",  "<td align=\"right\">","</td>");
                tempInstitute.NoOfFemaleHostelSit = MyString.tokenString(totalHtml, "Female Hostel Seat", "<td align=\"right\">", "</td>");



                insList.Add(tempInstitute);
                finalQry = CreateSql(finalQry, tempInstitute);

            }
            
//                    public String tempQry = @"UPDATE Institutes
//SET       Title ='#Title', HeadName ='#HeadName', Phone ='#Phone', EmailAddress ='#EmailAddress', WebSite ='#WebSite', EstablishDate =#EstablishDate, NoOfMaleStd =#NoOfMaleStd, NoOfFemaleStd =#NoOfFemaleStd, NoOfTeacher =#NoOfTeacher, NoOfMaleHostelSit =#NoOfMaleHostelSit, NoOfFemaleHostelSit =#NoOfFemaleHostelSit, Location ='#Location
//where Id='#Id";

            for (int i = 0; i < insList.Count; i++)
            {

                finalQry = CreateSql(finalQry, insList[i]);

                

            }

            
        }

        private string CreateSql(string finalQry, institute ins)
        {
            finalQry = tempQry;


            finalQry = finalQry.Replace("#Title", ins.Title);
            finalQry = finalQry.Replace("#HeadName", ins.HeadName);
            finalQry = finalQry.Replace("#Phone", ins.Phone);
            finalQry = finalQry.Replace("#EmailAddress", ins.EmailAddress);
            finalQry = finalQry.Replace("#WebSite", ins.WebSite);
            finalQry = finalQry.Replace("#EstablishDate", ins.EstablishDate);
            finalQry = finalQry.Replace("#NoOfMaleStd", ins.NoOfMaleStd);
            finalQry = finalQry.Replace("#NoOfFemaleStd", ins.NoOfFemaleStd);
            finalQry = finalQry.Replace("#NoOfTeacher", ins.NoOfTeacher);
            finalQry = finalQry.Replace("#NoOfMaleHostelSit", ins.NoOfMaleHostelSit);
            finalQry = finalQry.Replace("#NoOfFemaleHostelSit", ins.NoOfFemaleHostelSit);
            finalQry = finalQry.Replace("#Location", ins.Location);
            finalQry = finalQry.Replace("#Id", "" + ins.Id);

            finalQry = finalQry.Replace("N/A", "0");

            OutputTb.Text += finalQry;
            return finalQry;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            startId += 50;
            endId += 50;
            StartIdTb.Text =""+ startId;
            EndIdTb.Text = "" + endId;
        }

        private void minusBtn_Click(object sender, EventArgs e)
        {
            startId-= 50;
            endId -= 50;
            StartIdTb.Text = "" + startId;
            EndIdTb.Text = "" + endId;
        }
    }
}
