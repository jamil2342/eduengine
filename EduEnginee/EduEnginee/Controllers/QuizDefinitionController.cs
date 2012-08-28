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
    [Authorize]
    public class QuizDefinitionController : Controller
    {
        private QuizDbEntities db = new QuizDbEntities();

        //
        // GET: /QuizDefinition/

        public ActionResult Index()
        {
            return View(db.QuizDefinitions.ToList());
        }

        //
        // GET: /QuizDefinition/Details/5

        public ActionResult Details(int id = 0)
        {
            QuizDefinition quizdefinition = db.QuizDefinitions.Find(id);
            if (quizdefinition == null)
            {
                return HttpNotFound();
            }
            return PartialView(quizdefinition);
            
        }

        //
        // GET: /QuizDefinition/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /QuizDefinition/Create

        [HttpPost]
        public ActionResult Create(QuizDefinition quizdefinition)
        {
            if (ModelState.IsValid)
            {
                quizdefinition.CreatedBy = User.Identity.Name;
                quizdefinition.CreatedDate = System.DateTime.Now;
                quizdefinition.UpdatedBy = User.Identity.Name;
                quizdefinition.UpdatedDate = System.DateTime.Now;
                
                
                db.QuizDefinitions.Add(quizdefinition);
                
                db.SaveChanges();
                return RedirectToAction("Index");
            }
           

            return View(quizdefinition);
        }

        //
        // GET: /QuizDefinition/Edit/5

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
        // POST: /QuizDefinition/Edit/5

        [HttpPost]
        public ActionResult Edit(QuizDefinition quizdefinition)
        {
            if (ModelState.IsValid)
            {
                quizdefinition.UpdatedBy = User.Identity.Name;
                quizdefinition.UpdatedDate = System.DateTime.Now;


                db.Entry(quizdefinition).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(quizdefinition);
        }

        //
        // GET: /QuizDefinition/Delete/5

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
        // POST: /QuizDefinition/Delete/5

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