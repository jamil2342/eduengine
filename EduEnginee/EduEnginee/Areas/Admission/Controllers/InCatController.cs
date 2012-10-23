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
    public class InCatController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/InCat/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.InstituteCataries.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/InCat/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.InstituteCataries.Count().ToString());
            ObjectQuery<InstituteCatary> institutecataries = db.InstituteCataries.Include("InstituteType");
            institutecataries = institutecataries.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutecataries.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Single(i => i.Id == id);
            return PartialView("GridData", new InstituteCatary[] { institutecatary });
        }

        //
        // GET: /Admission/InCat/Create

        public ActionResult Create()
        {
            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/InCat/Create

        [HttpPost]
        public ActionResult Create(InstituteCatary institutecatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteCataries.AddObject(institutecatary);
                db.SaveChanges();
                return PartialView("GridData", new InstituteCatary[] { institutecatary });
            }

            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "Title", institutecatary.InstituteTypeId);
            return PartialView("Edit", institutecatary);
        }

        //
        // GET: /Admission/InCat/Edit/5

        public ActionResult Edit(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Single(i => i.Id == id);
            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "Title", institutecatary.InstituteTypeId);
            return PartialView(institutecatary);
        }

        //
        // POST: /Admission/InCat/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteCatary institutecatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteCataries.Attach(institutecatary);
                db.ObjectStateManager.ChangeObjectState(institutecatary, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new InstituteCatary[] { institutecatary });
            }

            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "Title", institutecatary.InstituteTypeId);
            return PartialView(institutecatary);
        }

        //
        // POST: /Admission/InCat/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Single(i => i.Id == id);
            db.InstituteCataries.DeleteObject(institutecatary);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
