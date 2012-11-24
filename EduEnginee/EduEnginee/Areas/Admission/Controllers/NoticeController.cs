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
    public class NoticeController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/Notice/

        public ActionResult Index()
        {
            var notices = db.Notices.Include("Institute");
            return View(notices.ToList());
        }

        private void PopulateInstituteDropDownList(object selectedInstitute = null)
        {
            var instituteQry = from d in db.Institutes
                               orderby d.Title
                               where !String.IsNullOrEmpty(d.Title)
                               select d;
            ViewBag.InstituteId = new SelectList(instituteQry, "Id", "Title", selectedInstitute);
        }

        ///////////////////////viewer//////////////////////////////////////////
        public ActionResult ViewerCirIndex(int? insCat)
        {
            var qry = from q in db.Institutes
                      where !String.IsNullOrEmpty(q.Title) && q.Notices.Count > 0
                      select q;

            if (insCat != null)
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

        public ActionResult _NoticeList(int? instituteId)
        {
            var qry = from q in db.Notices
                      where q.InstituteId == instituteId
                      select q;
            return PartialView(qry.ToList());
        }




        //
        // GET: /Admission/Notice/Details/5

        public ActionResult Details(int id = 0)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            if (notice == null)
            {
                return HttpNotFound();
            }
            return View("Details",notice);
        }

        //
        // GET: /Admission/Notice/Create
        [Authorize(Roles="admin")]
        public ActionResult Create()
        {
            //ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title");
            PopulateInstituteDropDownList();
            return View();
        }

        //
        // POST: /Admission/Notice/Create
        [Authorize(Roles="admin")]
        [HttpPost]
        public ActionResult Create(Notice notice)
        {
            if (ModelState.IsValid)
            {
                db.Notices.AddObject(notice);
                db.SaveChanges();
                //return RedirectToAction("Index");
            }

            //ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            PopulateInstituteDropDownList();
            return Details(notice.Id);
        }

        //
        // GET: /Admission/Notice/Edit/5
        [Authorize(Roles="admin")]
        public ActionResult Edit(int id = 0)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            if (notice == null)
            {
                return HttpNotFound();
            }
            //ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            PopulateInstituteDropDownList(notice.InstituteId);
            return View(notice);
        }

        //
        // POST: /Admission/Notice/Edit/5
        [Authorize(Roles="admin")]
        [HttpPost]
        public ActionResult Edit(Notice notice)
        {
            if (ModelState.IsValid)
            {
                db.Notices.Attach(notice);
                db.ObjectStateManager.ChangeObjectState(notice, EntityState.Modified);
                db.SaveChanges();
                //return RedirectToAction("Index");
            }
            //ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            PopulateInstituteDropDownList();
            return Details(notice.Id);
        }

        //
        // GET: /Admission/Notice/Delete/5
        [Authorize(Roles="admin")]
        public ActionResult Delete(int id = 0)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            if (notice == null)
            {
                return HttpNotFound();
            }
            return View(notice);
        }

        //
        // POST: /Admission/Notice/Delete/5
        [Authorize(Roles="admin")]
        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            db.Notices.DeleteObject(notice);
            db.SaveChanges();
            return RedirectToAction("ViewerCirIndex");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}