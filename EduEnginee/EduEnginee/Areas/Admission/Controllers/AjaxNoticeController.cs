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
    public class AjaxNoticeController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/AjaxNotice/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.Notices.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/AjaxNotice/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.Notices.Count().ToString());
            ObjectQuery<Notice> notices = db.Notices.Include("Institute");
            notices = notices.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(notices.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            return PartialView("GridData", new Notice[] { notice });
        }

        //
        // GET: /Admission/AjaxNotice/Create

        public ActionResult Create()
        {
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/AjaxNotice/Create

        [HttpPost]
        public ActionResult Create(Notice notice)
        {
            if (ModelState.IsValid)
            {
                db.Notices.AddObject(notice);
                db.SaveChanges();
                return PartialView("GridData", new Notice[] { notice });
            }

            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            return PartialView("Edit", notice);
        }

        //
        // GET: /Admission/AjaxNotice/Edit/5

        public ActionResult Edit(int id)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            return PartialView(notice);
        }

        //
        // POST: /Admission/AjaxNotice/Edit/5

        [HttpPost]
        public ActionResult Edit(Notice notice)
        {
            if (ModelState.IsValid)
            {
                db.Notices.Attach(notice);
                db.ObjectStateManager.ChangeObjectState(notice, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new Notice[] { notice });
            }

            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", notice.InstituteId);
            return PartialView(notice);
        }

        //
        // POST: /Admission/AjaxNotice/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            Notice notice = db.Notices.Single(n => n.Id == id);
            db.Notices.DeleteObject(notice);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
