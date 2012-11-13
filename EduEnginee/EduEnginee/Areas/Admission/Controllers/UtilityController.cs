using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace EduEnginee.Areas.Admission.Controllers
{
    public class UtilityController : Controller
    {
        //
        // GET: /Admission/Utility/

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult NoRecord()
        {
            return PartialView();
        }

    }
}
