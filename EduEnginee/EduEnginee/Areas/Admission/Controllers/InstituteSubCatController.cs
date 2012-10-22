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
    public class InstituteSubCatController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/InstituteSubCat/

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
        // GET: /Admission/InstituteSubCat/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.InstituteSubcataries.Count().ToString());
            ObjectQuery<InstituteSubcatary> institutesubcataries = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<InstituteSubcatary>();
            //institutesubcataries = institutesubcataries.Include(i => i.InstituteCatary);
            institutesubcataries = institutesubcataries.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutesubcataries.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Find(id);
            return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
        }

        //
        // GET: /Admission/InstituteSubCat/Create

        public ActionResult Create()
        {
            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "CreatedBy");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/InstituteSubCat/Create

        [HttpPost]
        public ActionResult Create(InstituteSubcatary institutesubcatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteSubcataries.Add(institutesubcatary);
                db.SaveChanges();
                return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
            }

            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "CreatedBy", institutesubcatary.InstituteCataryId);
            return PartialView("Edit", institutesubcatary);
        }

        //
        // GET: /Admission/InstituteSubCat/Edit/5

        public ActionResult Edit(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Find(id);
            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "CreatedBy", institutesubcatary.InstituteCataryId);
            return PartialView(institutesubcatary);
        }

        //
        // POST: /Admission/InstituteSubCat/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteSubcatary institutesubcatary)
        {
            if (ModelState.IsValid)
            {
                db.Entry(institutesubcatary).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new InstituteSubcatary[] { institutesubcatary });
            }

            ViewBag.InstituteCataryId = new SelectList(db.InstituteCataries, "Id", "CreatedBy", institutesubcatary.InstituteCataryId);
            return PartialView(institutesubcatary);
        }

        //
        // POST: /Admission/InstituteSubCat/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            InstituteSubcatary institutesubcatary = db.InstituteSubcataries.Find(id);
            db.InstituteSubcataries.Remove(institutesubcatary);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
