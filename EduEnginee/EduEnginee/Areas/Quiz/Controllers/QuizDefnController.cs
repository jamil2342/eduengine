using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Quiz.Models;

namespace EduEnginee.Areas.Quiz.Controllers
{
    public class QuizDefnController : Controller
    {
        private QuizDbEntities1 db = new QuizDbEntities1();

        //
        // GET: /Quiz/QuizDefn/

        public ActionResult Index()
        {
            return View(db.QuizDefinitions.ToList());
        }

        //
        // GET: /Quiz/QuizDefn/Details/5

        public ActionResult Details(int id = 0)
        {
            QuizDefinition quizdefinition = db.QuizDefinitions.Find(id);
            if (quizdefinition == null)
            {
                return HttpNotFound();
            }
            return View(quizdefinition);
        }

        //
        // GET: /Quiz/QuizDefn/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Quiz/QuizDefn/Create

        [HttpPost]
        public ActionResult Create(QuizDefinition quizdefinition)
        {
            if (ModelState.IsValid)
            {
                db.QuizDefinitions.Add(quizdefinition);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(quizdefinition);
        }

        //
        // GET: /Quiz/QuizDefn/Edit/5

        public ActionResult Edit(int id = 0)
        {
            QuizDefinition quizdefinition = db.QuizDefinitions.Find(id);
            if (quizdefinition == null)
            {
                return HttpNotFound();
            }
            return View(quizdefinition);
        }

        //
        // POST: /Quiz/QuizDefn/Edit/5

        [HttpPost]
        public ActionResult Edit(QuizDefinition quizdefinition)
        {
            if (ModelState.IsValid)
            {
                db.Entry(quizdefinition).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(quizdefinition);
        }

        //
        // GET: /Quiz/QuizDefn/Delete/5

        public ActionResult Delete(int id = 0)
        {
            QuizDefinition quizdefinition = db.QuizDefinitions.Find(id);
            if (quizdefinition == null)
            {
                return HttpNotFound();
            }
            return View(quizdefinition);
        }

        //
        // POST: /Quiz/QuizDefn/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            QuizDefinition quizdefinition = db.QuizDefinitions.Find(id);
            db.QuizDefinitions.Remove(quizdefinition);
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