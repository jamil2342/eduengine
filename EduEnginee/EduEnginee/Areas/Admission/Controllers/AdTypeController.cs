using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Objects;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Admission.Models;

namespace EduEnginee.Areas.Admission.Controllers
{
    public class AdTypeController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/AdType/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.AdmissionTypes.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/AdType/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.AdmissionTypes.Count().ToString());
            ObjectQuery<AdmissionType> admissiontypes = db.AdmissionTypes;
            admissiontypes = admissiontypes.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(admissiontypes.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Single(a => a.Id == id);
            return PartialView("GridData", new AdmissionType[] { admissiontype });
        }

        //
        // GET: /Admission/AdType/Create

        public ActionResult Create()
        {
            return PartialView("Edit");
        }

        //
        // POST: /Admission/AdType/Create

        [HttpPost]
        public ActionResult Create(AdmissionType admissiontype)
        {
            if (ModelState.IsValid)
            {
                db.AdmissionTypes.AddObject(admissiontype);
                db.SaveChanges();
                return PartialView("GridData", new AdmissionType[] { admissiontype });
            }

            return PartialView("Edit", admissiontype);
        }

        //
        // GET: /Admission/AdType/Edit/5

        public ActionResult Edit(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Single(a => a.Id == id);
            return PartialView(admissiontype);
        }

        //
        // POST: /Admission/AdType/Edit/5

        [HttpPost]
        public ActionResult Edit(AdmissionType admissiontype)
        {
            if (ModelState.IsValid)
            {
                db.AdmissionTypes.Attach(admissiontype);
                db.ObjectStateManager.ChangeObjectState(admissiontype, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new AdmissionType[] { admissiontype });
            }

            return PartialView(admissiontype);
        }

        //
        // POST: /Admission/AdType/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Single(a => a.Id == id);
            db.AdmissionTypes.DeleteObject(admissiontype);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
