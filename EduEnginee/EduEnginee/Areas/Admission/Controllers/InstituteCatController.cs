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
    public class InstituteCatController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/InstituteCat/

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
        // GET: /Admission/InstituteCat/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.InstituteCataries.Count().ToString());
            ObjectQuery<InstituteCatary> institutecataries = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<InstituteCatary>();
            institutecataries = institutecataries.Include(i => i.InstituteType);
            institutecataries = institutecataries.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(institutecataries.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Find(id);
            return PartialView("GridData", new InstituteCatary[] { institutecatary });
        }

        //
        // GET: /Admission/InstituteCat/Create

        public ActionResult Create()
        {
            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "CreatedBy");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/InstituteCat/Create

        [HttpPost]
        public ActionResult Create(InstituteCatary institutecatary)
        {
            if (ModelState.IsValid)
            {
                db.InstituteCataries.Add(institutecatary);
                db.SaveChanges();
                return PartialView("GridData", new InstituteCatary[] { institutecatary });
            }

            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "CreatedBy", institutecatary.InstituteTypeId);
            return PartialView("Edit", institutecatary);
        }

        //
        // GET: /Admission/InstituteCat/Edit/5

        public ActionResult Edit(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Find(id);
            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "CreatedBy", institutecatary.InstituteTypeId);
            return PartialView(institutecatary);
        }

        //
        // POST: /Admission/InstituteCat/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteCatary institutecatary)
        {
            if (ModelState.IsValid)
            {
                db.Entry(institutecatary).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new InstituteCatary[] { institutecatary });
            }

            ViewBag.InstituteTypeId = new SelectList(db.InstituteTypes, "Id", "CreatedBy", institutecatary.InstituteTypeId);
            return PartialView(institutecatary);
        }

        //
        // POST: /Admission/InstituteCat/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            InstituteCatary institutecatary = db.InstituteCataries.Find(id);
            db.InstituteCataries.Remove(institutecatary);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
