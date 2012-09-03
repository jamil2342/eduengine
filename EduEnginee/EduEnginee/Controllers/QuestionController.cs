using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Models;

namespace EduEnginee.Controllers
{
    public class QuestionController : Controller
    {
        private QuizDbEntities db = new QuizDbEntities();

        //
        // GET: /Question/

        public ActionResult Index()
        {
            var questiondefinitions = db.QuestionDefinitions.Include(q => q.QuizDefinition);
            return View(questiondefinitions.ToList());
        }

        //
        // GET: /Question/Details/5

        public ActionResult Details(int id = 0)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            if (questiondefinition == null)
            {
                return HttpNotFound();
            }
            return View(questiondefinition);
        }

        //
        // GET: /Question/Create

        public ActionResult Create()
        {
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName");
            return PartialView("_Create");
        }
        public ActionResult _Create()
        {
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName");
            return PartialView("_Create");
        }




        //
        // POST: /Question/Create

        [HttpPost]
        public ActionResult Create(QuestionDefinition questiondefinition)
        {
            if (ModelState.IsValid)
            {
                db.QuestionDefinitions.Add(questiondefinition);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return View(questiondefinition);
        }

        //
        // GET: /Question/Edit/5

        public ActionResult Edit(int id = 0)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            if (questiondefinition == null)
            {
                return HttpNotFound();
            }
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return View(questiondefinition);
        }

        //
        // POST: /Question/Edit/5

        [HttpPost]
        public ActionResult Edit(QuestionDefinition questiondefinition)
        {
            if (ModelState.IsValid)
            {
                db.Entry(questiondefinition).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return View(questiondefinition);
        }

        //
        // GET: /Question/Delete/5
        [HttpPost]
        public void Delete(int id = 0)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            db.QuestionDefinitions.Remove(questiondefinition);
            db.SaveChanges();
        }

        //
        // POST: /Question/Delete/5

        [HttpPost, ActionName("Delete")]
        public void DeleteConfirmed(int id)
        {

            //return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}