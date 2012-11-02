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
    public class AjaxNewsController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/AjaxNews/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.News.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Admission/AjaxNews/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.News.Count().ToString());
            ObjectQuery<News> news = db.News.Include("Institute");
            news = news.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(news.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            News news = db.News.Single(n => n.Id == id);
            return PartialView("GridData", new News[] { news });
        }

        //
        // GET: /Admission/AjaxNews/Create

        public ActionResult Create()
        {
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Admission/AjaxNews/Create

        [HttpPost]
        public ActionResult Create(News news)
        {
            if (ModelState.IsValid)
            {
                db.News.AddObject(news);
                db.SaveChanges();
                return PartialView("GridData", new News[] { news });
            }

            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return PartialView("Edit", news);
        }

        //
        // GET: /Admission/AjaxNews/Edit/5

        public ActionResult Edit(int id)
        {
            News news = db.News.Single(n => n.Id == id);
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return PartialView(news);
        }

        //
        // POST: /Admission/AjaxNews/Edit/5

        [HttpPost]
        public ActionResult Edit(News news)
        {
            if (ModelState.IsValid)
            {
                db.News.Attach(news);
                db.ObjectStateManager.ChangeObjectState(news, EntityState.Modified);
                db.SaveChanges();
                return PartialView("GridData", new News[] { news });
            }

            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return PartialView(news);
        }

        //
        // POST: /Admission/AjaxNews/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            News news = db.News.Single(n => n.Id == id);
            db.News.DeleteObject(news);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
