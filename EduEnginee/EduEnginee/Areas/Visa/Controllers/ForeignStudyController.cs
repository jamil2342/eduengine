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
    public class ForeignStudyController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/ForeignStudy/

        public ActionResult Index()
        {
            var foreignstudyset = db.ForeignStudySet.Include(f => f.CountrySet);
            return View(foreignstudyset.ToList());
        }

        public ActionResult _ContinentTab()
        {

            return PartialView(db.ContinentSet.ToList());
        }

        public ActionResult _CountryList(int? continentId)
        {

            var qry = from q in db.CountrySet
                      where q.ContinentId == continentId
                      orderby q.Title
                      select q;
            return PartialView(qry.ToList());
        }

        public ActionResult _List(int? countryId)
        {
            var foreignStudy = from q in db.ForeignStudySet
                                   where q.Country_Id == countryId
                                   select q;
            return View(foreignStudy.ToList());
        }

        //
        // GET: /Visa/ForeignStudy/Details/5

        public ActionResult Details(int id = 0)
        {
            ForeignStudySet foreignstudyset = db.ForeignStudySet.Find(id);
            if (foreignstudyset == null)
            {
                return HttpNotFound();
            }
            return View(foreignstudyset);
        }

        //
        // GET: /Visa/ForeignStudy/Create

        public ActionResult Create()
        {
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title");
            return View();
        }

        //
        // POST: /Visa/ForeignStudy/Create

        [HttpPost]
        public ActionResult Create(ForeignStudySet foreignstudyset)
        {
            if (ModelState.IsValid)
            {
                db.ForeignStudySet.Add(foreignstudyset);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", foreignstudyset.Country_Id);
            return View(foreignstudyset);
        }

        //
        // GET: /Visa/ForeignStudy/Edit/5

        public ActionResult Edit(int id = 0)
        {
            ForeignStudySet foreignstudyset = db.ForeignStudySet.Find(id);
            if (foreignstudyset == null)
            {
                return HttpNotFound();
            }
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", foreignstudyset.Country_Id);
            return View(foreignstudyset);
        }

        //
        // POST: /Visa/ForeignStudy/Edit/5

        [HttpPost]
        public ActionResult Edit(ForeignStudySet foreignstudyset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(foreignstudyset).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.Country_Id = new SelectList(db.CountrySet, "Id", "Title", foreignstudyset.Country_Id);
            return View(foreignstudyset);
        }

        //
        // GET: /Visa/ForeignStudy/Delete/5

        public ActionResult Delete(int id = 0)
        {
            ForeignStudySet foreignstudyset = db.ForeignStudySet.Find(id);
            if (foreignstudyset == null)
            {
                return HttpNotFound();
            }
            return View(foreignstudyset);
        }

        //
        // POST: /Visa/ForeignStudy/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            ForeignStudySet foreignstudyset = db.ForeignStudySet.Find(id);
            db.ForeignStudySet.Remove(foreignstudyset);
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