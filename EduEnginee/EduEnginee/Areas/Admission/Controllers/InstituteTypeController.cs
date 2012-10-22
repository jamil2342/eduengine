using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Data.Objects;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Admission.Models;

namespace EduEnginee.Areas.Admission.Controllers
{
    public class InstituteTypeController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/InstituteType/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.InstituteTypes.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/InstituteType/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.InstituteTypes.Count().ToString());
            ObjectQuery<InstituteType> institutetypes = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<InstituteType>();
            institutetypes = institutetypes.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutetypes.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            InstituteType institutetype = db.InstituteTypes.Find(id);
            return PartialView("GridData", new InstituteType[] { institutetype });
        }

        //
        // GET: /Admission/InstituteType/Create

        public ActionResult Create()
        {
            return PartialView("Edit");
        }

        //
        // POST: /Admission/InstituteType/Create

        [HttpPost]
        public ActionResult Create(InstituteType institutetype)
        {
            institutetype.CreatedBy = User.Identity.ToString();
            institutetype.UpdatedBy = User.Identity.ToString();
            institutetype.CreatedDate = System.DateTime.Now;
            institutetype.UpdatedDate = System.DateTime.Now;

            if (ModelState.IsValid)
            {
                db.InstituteTypes.Add(institutetype);
                db.SaveChanges();
                return PartialView("GridData", new InstituteType[] { institutetype });
            }

            return PartialView("Edit", institutetype);
        }

        //
        // GET: /Admission/InstituteType/Edit/5

        public ActionResult Edit(int id)
        {
            InstituteType institutetype = db.InstituteTypes.Find(id);
            return PartialView(institutetype);
        }

        //
        // POST: /Admission/InstituteType/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteType institutetype)
        {

            institutetype.UpdatedBy = User.Identity.ToString();
            institutetype.UpdatedDate = System.DateTime.Now;


            if (ModelState.IsValid)
            {
                db.Entry(institutetype).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new InstituteType[] { institutetype });
            }

            return PartialView(institutetype);
        }

        //
        // POST: /Admission/InstituteType/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            InstituteType institutetype = db.InstituteTypes.Find(id);
            db.InstituteTypes.Remove(institutetype);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
