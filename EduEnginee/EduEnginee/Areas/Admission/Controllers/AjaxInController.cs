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
    public class AjaxInController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/AjaxIn/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.Institutes.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/AjaxIn/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.Institutes.Count().ToString());
            ObjectQuery<Institute> institutes = db.Institutes.Include("Country").Include("InstituteSubcatary");
            institutes = institutes.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutes.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            return PartialView("GridData", new Institute[] { institute });
        }

        //
        // GET: /Admission/AjaxIn/Create

        public ActionResult Create()
        {
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name");
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/AjaxIn/Create

        [HttpPost]
        public ActionResult Create(Institute institute)
        {
            if (ModelState.IsValid)
            {
                db.Institutes.AddObject(institute);
                db.SaveChanges();
                return PartialView("GridData", new Institute[] { institute });
            }

            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return PartialView("Edit", institute);
        }

        //
        // GET: /Admission/AjaxIn/Edit/5

        public ActionResult Edit(int id)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return PartialView(institute);
        }

        //
        // POST: /Admission/AjaxIn/Edit/5

        [HttpPost]
        public ActionResult Edit(Institute institute)
        {
            if (ModelState.IsValid)
            {
                db.Institutes.Attach(institute);
                db.ObjectStateManager.ChangeObjectState(institute, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new Institute[] { institute });
            }

            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return PartialView(institute);
        }

        //
        // POST: /Admission/AjaxIn/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            db.Institutes.DeleteObject(institute);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
