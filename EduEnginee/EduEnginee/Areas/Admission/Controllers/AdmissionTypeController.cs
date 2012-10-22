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
    public class AdmissionTypeController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/AdmissionType/

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
        // GET: /Admission/AdmissionType/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.AdmissionTypes.Count().ToString());
            ObjectQuery<AdmissionType> admissiontypes = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<AdmissionType>();
            admissiontypes = admissiontypes.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(admissiontypes.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Find(id);
            return PartialView("GridData", new AdmissionType[] { admissiontype });
        }

        //
        // GET: /Admission/AdmissionType/Create

        public ActionResult Create()
        {
            return PartialView("Edit");
        }

        //
        // POST: /Admission/AdmissionType/Create

        [HttpPost]
        public ActionResult Create(AdmissionType admissiontype)
        {
            if (ModelState.IsValid)
            {
                db.AdmissionTypes.Add(admissiontype);
                db.SaveChanges();
                return PartialView("GridData", new AdmissionType[] { admissiontype });
            }

            return PartialView("Edit", admissiontype);
        }

        //
        // GET: /Admission/AdmissionType/Edit/5

        public ActionResult Edit(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Find(id);
            return PartialView(admissiontype);
        }

        //
        // POST: /Admission/AdmissionType/Edit/5

        [HttpPost]
        public ActionResult Edit(AdmissionType admissiontype)
        {
            if (ModelState.IsValid)
            {
                db.Entry(admissiontype).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new AdmissionType[] { admissiontype });
            }

            return PartialView(admissiontype);
        }

        //
        // POST: /Admission/AdmissionType/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            AdmissionType admissiontype = db.AdmissionTypes.Find(id);
            db.AdmissionTypes.Remove(admissiontype);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
