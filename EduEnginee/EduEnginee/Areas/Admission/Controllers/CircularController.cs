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
    public class CircularController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/Circular/

        public ActionResult Index()
        {
            var circulars = db.Circulars.Include("AdmissionType").Include("Institute");
            return View(circulars.ToList());
        }


        public ActionResult ViewerCirIndex(int? insCat)
        {
            var qry = from q in db.Institutes  
                      where !String.IsNullOrEmpty(q.Title) && q.Circulars.Count>0
                      select q;

            if (insCat!=null)
            {
                qry = from q in qry
                      where q.InstituteSubcatary.InstituteCataryId == insCat
                      select q;
            }
            return View(qry.ToList());
        }


        public ActionResult _InsCatList()
        {
            var qry = from q in db.InstituteCataries
                      select q;
            return PartialView(qry.ToList());
        }

        public ActionResult _CirList(int ? instituteId)
        {
            var qry = from q in db.Circulars
                      where q.InstituteId == instituteId
                      select q;
            return PartialView(qry.ToList());
        }

        //
        // GET: /Admission/Circular/Details/5

        public ActionResult Details(int id = 0)
        {
            Circular circular = db.Circulars.Single(c => c.Id == id);
            if (circular == null)
            {
                return HttpNotFound();
            }
            return View(circular);
        }

        //
        // GET: /Admission/Circular/Create

        public ActionResult Create()
        {
            ViewBag.AdmissionTypeId = new SelectList(db.AdmissionTypes, "Id", "Title");
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title");
            return View();
        }

        //
        // POST: /Admission/Circular/Create

        [HttpPost]
        public ActionResult Create(Circular circular)
        {
            if (ModelState.IsValid)
            {
                db.Circulars.AddObject(circular);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.AdmissionTypeId = new SelectList(db.AdmissionTypes, "Id", "Title", circular.AdmissionTypeId);
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", circular.InstituteId);
            return View(circular);
        }

        //
        // GET: /Admission/Circular/Edit/5

        public ActionResult Edit(int id = 0)
        {
            Circular circular = db.Circulars.Single(c => c.Id == id);
            if (circular == null)
            {
                return HttpNotFound();
            }
            ViewBag.AdmissionTypeId = new SelectList(db.AdmissionTypes, "Id", "Title", circular.AdmissionTypeId);
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", circular.InstituteId);
            return View(circular);
        }

        //
        // POST: /Admission/Circular/Edit/5

        [HttpPost]
        public ActionResult Edit(Circular circular)
        {
            if (ModelState.IsValid)
            {
                db.Circulars.Attach(circular);
                db.ObjectStateManager.ChangeObjectState(circular, EntityState.Modified);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.AdmissionTypeId = new SelectList(db.AdmissionTypes, "Id", "Title", circular.AdmissionTypeId);
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", circular.InstituteId);
            return View(circular);
        }

        //
        // GET: /Admission/Circular/Delete/5

        public ActionResult Delete(int id = 0)
        {
            Circular circular = db.Circulars.Single(c => c.Id == id);
            if (circular == null)
            {
                return HttpNotFound();
            }
            return View(circular);
        }





        [AcceptVerbs(HttpVerbs.Delete)]
        [ActionName("Delete")]
        public ActionResult AjaxDelete(int id)
        {
            Circular circular = db.Circulars.Single(c => c.Id == id);
            db.Circulars.DeleteObject(circular);
            db.SaveChanges();


            return PartialView("_Accordin", db.Circulars.ToList());
        }


        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}