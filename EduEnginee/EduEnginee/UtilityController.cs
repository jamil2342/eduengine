using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace EduEnginee
{
    public class UtilityController
    {
        //
        // GET: /Admission/Utility/


        public static string NoOfRecord(int? x)
        {
            if (x==0)
            {
                return "N/A";
            }
            else if (x==null)
            {
                return "N/A";
            }
            else
            {
                return "" + x;
            }
        }

    }
}
