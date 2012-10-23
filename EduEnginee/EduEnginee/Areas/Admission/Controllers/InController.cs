using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Admission.Models;

namespace EduEnginee.Areas.Admission.Controllers
{
    public class InController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/In/

        public ActionResult Index()
        {
            var institutes = db.Institutes.Include("Country").Include("InstituteSubcatary");
            return View(institutes.ToList());
        }

        //
        // GET: /Admission/In/Details/5

        public ActionResult Details(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            return View(institute);
        }

        //
        // GET: /Admission/In/Create

        public ActionResult Create()
        {
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name");
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title");
            return View();
        }

        //
        // POST: /Admission/In/Create

        [HttpPost]
        public ActionResult Create(Institute institute)
        {
            if (ModelState.IsValid)
            {
                db.Institutes.AddObject(institute);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return View(institute);
        }

        //
        // GET: /Admission/In/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return View(institute);
        }

        //
        // POST: /Admission/In/Edit/5

        [HttpPost]
        public ActionResult Edit(Institute institute)
        {
            if (ModelState.IsValid)
            {
                db.Institutes.Attach(institute);
                db.ObjectStateManager.ChangeObjectState(institute, EntityState.Modified);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return View(institute);
        }

        //
        // GET: /Admission/In/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            return View(institute);
        }

        //
        // POST: /Admission/In/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            db.Institutes.DeleteObject(institute);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}