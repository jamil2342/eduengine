using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Visa.Models;

namespace EduEnginee.Areas.Visa.Controllers
{
    public class VisaProcedureController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/VisaProcedure/

        public ActionResult Index()
        {
            var visaprocedureset = db.VisaProcedureSet.Include(v => v.CountrySet).Include(v => v.VisaTypeSet);
            return View(visaprocedureset.ToList());
        }


        public ActionResult _ContinentTab()
        {

            return PartialView(db.ContinentSet.ToList());
        }

        public ActionResult _CountryList(int? continentId)
        {

            var qry = from q in db.CountrySet
                      where q.ContinentId==continentId
                      orderby q.Title
                      select q;
            return PartialView(qry.ToList());
        }

        public ActionResult _List(int? countryId)
        {
            var visaprocedureset = from q in db.VisaProcedureSet
                                   where q.Country_Id == countryId
                                   select q;
            return View(visaprocedureset.ToList());
        }
        //
        // GET: /Visa/VisaProcedure/Details/5

        public ActionResult Details(int id = 0)
        {
            VisaProcedureSet visaprocedureset = db.VisaProcedureSet.Find(id);
            if (visaprocedureset == null)
            {
                return HttpNotFound();
            }
            return View(visaprocedureset);
        }

        //
        // GET: /Visa/VisaProcedure/Create

        public ActionResult Create()
        {
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title");
            ViewBag.VisaTypeId = new SelectList(db.VisaTypeSet, "Id", "Title");
            return View();
        }

        //
        // POST: /Visa/VisaProcedure/Create

        [HttpPost]
        public ActionResult Create(VisaProcedureSet visaprocedureset)
        {
            if (ModelState.IsValid)
            {
                db.VisaProcedureSet.Add(visaprocedureset);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", visaprocedureset.Country_Id);
            ViewBag.VisaTypeId = new SelectList(db.VisaTypeSet, "Id", "Title", visaprocedureset.VisaTypeId);
            return View(visaprocedureset);
        }

        //
        // GET: /Visa/VisaProcedure/Edit/5

        public ActionResult Edit(int id = 0)
        {
            VisaProcedureSet visaprocedureset = db.VisaProcedureSet.Find(id);
            if (visaprocedureset == null)
            {
                return HttpNotFound();
            }
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", visaprocedureset.Country_Id);
            ViewBag.VisaTypeId = new SelectList(db.VisaTypeSet, "Id", "Title", visaprocedureset.VisaTypeId);
            return View(visaprocedureset);
        }

        //
        // POST: /Visa/VisaProcedure/Edit/5

        [HttpPost]
        public ActionResult Edit(VisaProcedureSet visaprocedureset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(visaprocedureset).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", visaprocedureset.Country_Id);
            ViewBag.VisaTypeId = new SelectList(db.VisaTypeSet, "Id", "Title", visaprocedureset.VisaTypeId);
            return View(visaprocedureset);
        }

        //
        // GET: /Visa/VisaProcedure/Delete/5

        public ActionResult Delete(int id = 0)
        {
            VisaProcedureSet visaprocedureset = db.VisaProcedureSet.Find(id);
            if (visaprocedureset == null)
            {
                return HttpNotFound();
            }
            return View(visaprocedureset);
        }

        //
        // POST: /Visa/VisaProcedure/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            VisaProcedureSet visaprocedureset = db.VisaProcedureSet.Find(id);
            db.VisaProcedureSet.Remove(visaprocedureset);
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