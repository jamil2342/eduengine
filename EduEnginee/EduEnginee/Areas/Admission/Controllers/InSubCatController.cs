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
    public class InSubCatController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/InSubCat/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.InstituteSubcataries.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/InSubCat/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.InstituteSubcataries.Count().ToString());
            ObjectQuery<InstituteSubcatary> institutesubcataries = db.InstituteSubcataries.Include("InstituteCatary");
            institutesubcataries = institutesubcataries.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutesubcataries.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Single(i => i.Id == id);
            return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
        }

        //
        // GET: /Admission/InSubCat/Create

        public ActionResult Create()
        {
            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/InSubCat/Create

        [HttpPost]
        public ActionResult Create(InstituteSubcatary institutesubcatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteSubcataries.AddObject(institutesubcatary);
                db.SaveChanges();
                return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
            }

            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "Title", institutesubcatary.InstituteCataryId);
            return PartialView("Edit", institutesubcatary);
        }

        //
        // GET: /Admission/InSubCat/Edit/5

        public ActionResult Edit(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Single(i => i.Id == id);
            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "Title", institutesubcatary.InstituteCataryId);
            return PartialView(institutesubcatary);
        }

        //
        // POST: /Admission/InSubCat/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteSubcatary institutesubcatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteSubcataries.Attach(institutesubcatary);
                db.ObjectStateManager.ChangeObjectState(institutesubcatary, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
            }

            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "Title", institutesubcatary.InstituteCataryId);
            return PartialView(institutesubcatary);
        }

        //
        // POST: /Admission/InSubCat/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Single(i => i.Id == id);
            db.InstituteSubcataries.DeleteObject(institutesubcatary);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
