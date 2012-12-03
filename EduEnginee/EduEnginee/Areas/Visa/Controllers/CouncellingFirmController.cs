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
    public class CouncellingFirmController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/CouncellingFirm/

        public ActionResult Index()
        {
            return View(db.CouncellingFirmSet.ToList());
        }

        public ActionResult _ContinentTab()
        {

            return PartialView(db.ContinentSet.ToList());
        }

        public ActionResult _List(int? continentId)
        {

            var qry= from q in db.CouncellingFirmSet
                     where q.CountrySet.Any(c=>c.ContinentId==continentId)
                         select q;
            return PartialView(qry.ToList());
        }


        //
        // GET: /Visa/CouncellingFirm/Details/5

        public ActionResult Details(int id = 0)
        {
            CouncellingFirmSet councellingfirmset = db.CouncellingFirmSet.Find(id);
            if (councellingfirmset == null)
            {
                return HttpNotFound();
            }
            return View(councellingfirmset);
        }

        //
        // GET: /Visa/CouncellingFirm/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Visa/CouncellingFirm/Create

        [HttpPost]
        public ActionResult Create(CouncellingFirmSet councellingfirmset)
        {
            if (ModelState.IsValid)
            {
                db.CouncellingFirmSet.Add(councellingfirmset);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(councellingfirmset);
        }

        //
        // GET: /Visa/CouncellingFirm/Edit/5

        public ActionResult Edit(int id = 0)
        {
            CouncellingFirmSet councellingfirmset = db.CouncellingFirmSet.Find(id);
            if (councellingfirmset == null)
            {
                return HttpNotFound();
            }
            return View(councellingfirmset);
        }

        //
        // POST: /Visa/CouncellingFirm/Edit/5

        [HttpPost]
        public ActionResult Edit(CouncellingFirmSet councellingfirmset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(councellingfirmset).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(councellingfirmset);
        }

        //
        // GET: /Visa/CouncellingFirm/Delete/5

        public ActionResult Delete(int id = 0)
        {
            CouncellingFirmSet councellingfirmset = db.CouncellingFirmSet.Find(id);
            if (councellingfirmset == null)
            {
                return HttpNotFound();
            }
            return View(councellingfirmset);
        }

        //
        // POST: /Visa/CouncellingFirm/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            CouncellingFirmSet councellingfirmset = db.CouncellingFirmSet.Find(id);
            db.CouncellingFirmSet.Remove(councellingfirmset);
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