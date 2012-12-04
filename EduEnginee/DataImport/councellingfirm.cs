using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace DataImport
{
    public partial class CouncellingFirm : Form
    {
        public CouncellingFirm()
        {
            InitializeComponent();
        }


        public class institute
        {
            public int Id ;
            public string Mobile;//
            public string Phone;//{ get; set; }
            public string Fax;// { get; set; }
            public string Email;//{ get; set; }
            public string Web;//{ get; set; }

            public string Description;// { get; set; }
            public string DirectorName;//{ get; set; }

            public string Address;// { get; set; }
            public string Title;// { get; set; }

        }

        List<institute> insList = new List<institute>();

        string output = "";

        public String tempQry = "\n" + @"UPDATE  CouncellingFirmSet
SET        Title = N'#Title', Mobile = N'#Mobile', Phone = N'#Phone', Email =N'#Email', Web =N'#Web', Description =N'#Description', DirectorName =N'#DirectorName', Address =N'#Address'
where id=#ID";

        int startId = 0;
        int endId = 0;
        private void SubmitTb_Click(object sender, EventArgs e)
        {
            insList.Clear();
            startId = Convert.ToInt32(StartIdTb.Text);
            endId = Convert.ToInt32(EndIdTb.Text);
            string totalHtml = "";

            string tempUrl = "http://www.eduicon.com/Counseling_Firm/Details/?Counselling_Basic_ID=#ID&type=general";
            institute tempInstitute = new institute();

            string finalQry = "";
           
            for (int i = startId; i <= endId; i++)
            {


                totalHtml = WebFetch.GetHtml(tempUrl.Replace("#ID",""+i));
                //totalHtml = Char.GetUnicodeCategory(totalHtml, 0).ToString();
                tempInstitute.Id = i;

                tempInstitute.Title = MyString.tokenString(totalHtml, "<title>", "</title>");
                tempInstitute.Phone = MyString.tokenString(totalHtml, "<b>Phone: </b>", "<br>", 100);
                tempInstitute.Mobile = MyString.tokenString(totalHtml, "<b>Mobile: </b>", "<br>", 400);
                tempInstitute.Email = MyString.tokenString(totalHtml, "<b>Email: </b>", "<br>", 400);
                tempInstitute.Web = MyString.tokenString(totalHtml, "<b>Web: </b><a href=\"", "\"", 400);
                tempInstitute.Fax = MyString.tokenString(totalHtml, "<b>Fax: </b>", "<br>", 400);
                tempInstitute.Address = MyString.tokenString(totalHtml, "<b>Address: </b>", "<br>", 500);
                tempInstitute.DirectorName = MyString.tokenString(totalHtml, "<b>Director Name: </b>", "<br>", 500);
                tempInstitute.Description = MyString.tokenString(totalHtml, "<td colspan=\"2\">", "</td>");

                insList.Add(tempInstitute);
                finalQry = CreateSql(finalQry, tempInstitute);
                Debug.WriteLine(finalQry);
            }




        }

        private string CreateSql(string finalQry, institute ins)
        {
            finalQry = tempQry;


            finalQry = finalQry.Replace("#Title", ins.Title);
            finalQry = finalQry.Replace("#Mobile", ins.Mobile);
            finalQry = finalQry.Replace("#Phone", ins.Phone);
            finalQry = finalQry.Replace("#Email", ins.Email);
            finalQry = finalQry.Replace("#Web", ins.Web);
            //finalQry = finalQry.Replace("#Description", ins.Description);
            finalQry = finalQry.Replace("#DirectorName", ins.DirectorName);
            finalQry = finalQry.Replace("#Address", ins.Address);
            finalQry = finalQry.Replace("#Fax", ins.Fax);
            finalQry = finalQry.Replace("#ID", "" + ins.Id);



            output += finalQry;
            //label1.Text = finalQry;
            if (ins.Id % 100 == 0)
            {
                OutputTb.Text += output;
                output = "";
            }

            return finalQry;
        }
    }
}
