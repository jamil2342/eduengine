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
    public class NewsController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/News/

        public ActionResult Index()
        {
            var news = db.News.Include("Institute");
            return View(news.ToList());
        }




        ///////////////////////viewer//////////////////////////////////////////
        public ActionResult ViewerCirIndex(int? insCat)
        {
            var qry = from q in db.Institutes
                      where !String.IsNullOrEmpty(q.Title) && q.News.Count > 0
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

        public ActionResult _NewsList(int? instituteId)
        {
            var qry = from q in db.News
                      where q.InstituteId == instituteId
                      select q;
            return PartialView(qry.ToList());
        }





        //
        // GET: /Admission/News/Details/5

        public ActionResult Details(int id = 0)
        {
            News news = db.News.Single(n => n.Id == id);
            if (news == null)
            {
                return HttpNotFound();
            }
            return View(news);
        }

        //
        // GET: /Admission/News/Create

        public ActionResult Create()
        {
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title");
            return View();
        }

        //
        // POST: /Admission/News/Create

        [HttpPost]
        public ActionResult Create(News news)
        {
            if (ModelState.IsValid)
            {
                db.News.AddObject(news);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return View(news);
        }

        //
        // GET: /Admission/News/Edit/5

        public ActionResult Edit(int id = 0)
        {
            News news = db.News.Single(n => n.Id == id);
            if (news == null)
            {
                return HttpNotFound();
            }
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return View(news);
        }

        //
        // POST: /Admission/News/Edit/5

        [HttpPost]
        public ActionResult Edit(News news)
        {
            if (ModelState.IsValid)
            {
                db.News.Attach(news);
                db.ObjectStateManager.ChangeObjectState(news, EntityState.Modified);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.InstituteId = new SelectList(db.Institutes, "Id", "Title", news.InstituteId);
            return View(news);
        }

        //
        // GET: /Admission/News/Delete/5

        public ActionResult Delete(int id = 0)
        {
            News news = db.News.Single(n => n.Id == id);
            if (news == null)
            {
                return HttpNotFound();
            }
            return View(news);
        }

        //
        // POST: /Admission/News/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            News news = db.News.Single(n => n.Id == id);
            db.News.DeleteObject(news);
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