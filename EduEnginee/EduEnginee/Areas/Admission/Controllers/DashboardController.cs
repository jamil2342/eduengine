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
    public class DashboardController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/Dashboard/

        public ActionResult Index()
        {
            return View(db.InstituteTypes.ToList());
        }


        public ActionResult _insCat(int InsTypeId)
        {
            var qry = from q in db.InstituteCataries
                      where q.InstituteTypeId == InsTypeId
                      select q;
            return PartialView(qry.ToList());
        }


        public ActionResult InsSubCatList(int? InsCatId)
        {
            var qry = from q in db.InstituteSubcataries
                      where q.InstituteCataryId == InsCatId
                      select q;

            return View(qry.ToList());
        }





        public ActionResult InstituteList(int insSubCatId)
        {
            var qry = from q in db.Institutes
                      where q.InstituteSubcataryId == insSubCatId && !String.IsNullOrEmpty(q.Title)&& !q.Title.Contains("N/A")
                      select q;
            return PartialView(qry.ToList());
        }




        public ActionResult _Details(int id = 0)
        {
            InstituteType institutetype = db.InstituteTypes.Single(i => i.Id == id);
            if (institutetype == null)
            {
                return HttpNotFound();
            }
            return View(institutetype);
        }
        
        //
        // GET: /Admission/Dashboard/Details/5

        public ActionResult Details(int id = 0)
        {
            InstituteType institutetype = db.InstituteTypes.Single(i => i.Id == id);
            if (institutetype == null)
            {
                return HttpNotFound();
            }
            return View(institutetype);
        }

        //
        // GET: /Admission/Dashboard/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Admission/Dashboard/Create

        [HttpPost]
        public ActionResult Create(InstituteType institutetype)
        {
            if (ModelState.IsValid)
            {
                db.InstituteTypes.AddObject(institutetype);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(institutetype);
        }

        //
        // GET: /Admission/Dashboard/Edit/5

        public ActionResult Edit(int id = 0)
        {
            InstituteType institutetype = db.InstituteTypes.Single(i => i.Id == id);
            if (institutetype == null)
            {
                return HttpNotFound();
            }
            return View(institutetype);
        }

        //
        // POST: /Admission/Dashboard/Edit/5

        [HttpPost]
        public ActionResult Edit(InstituteType institutetype)
        {
            if (ModelState.IsValid)
            {
                db.InstituteTypes.Attach(institutetype);
                db.ObjectStateManager.ChangeObjectState(institutetype, EntityState.Modified);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(institutetype);
        }

        //
        // GET: /Admission/Dashboard/Delete/5

        public ActionResult Delete(int id = 0)
        {
            InstituteType institutetype = db.InstituteTypes.Single(i => i.Id == id);
            if (institutetype == null)
            {
                return HttpNotFound();
            }
            return View(institutetype);
        }

        //
        // POST: /Admission/Dashboard/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            InstituteType institutetype = db.InstituteTypes.Single(i => i.Id == id);
            db.InstituteTypes.DeleteObject(institutetype);
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