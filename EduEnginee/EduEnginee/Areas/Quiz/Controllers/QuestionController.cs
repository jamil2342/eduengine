﻿using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Data.Objects;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Quiz.Models;

namespace EduEnginee.Areas.Quiz.Controllers
{
    public class QuestionController : Controller
    {
        private QuizDbEntities1 db = new QuizDbEntities1();

        //
        // GET: /Quiz/Question/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.QuestionDefinitions.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Quiz/Question/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.QuestionDefinitions.Count().ToString());
            ObjectQuery<QuestionDefinition> questiondefinitions = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<QuestionDefinition>();
            //questiondefinitions = questiondefinitions.Include(q => q.QuizDefinition);
            questiondefinitions = questiondefinitions.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(questiondefinitions.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            return PartialView("GridData", new QuestionDefinition[] { questiondefinition });
        }

        //
        // GET: /Quiz/Question/Create

        public ActionResult Create()
        {
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName");
            return PartialView("Edit");
        }

        //
        // POST: /Quiz/Question/Create

        [HttpPost]
        public ActionResult _Create(QuestionDefinition questiondefinition)
        {
            questiondefinition.QuizDefinitionKey = 3;
            int id = (from s in db.QuestionDefinitions
                      select s.Id).Max();
            questiondefinition.Id = (int)(id + 1);
            if (ModelState.IsValid)
            {
                db.QuestionDefinitions.Add(questiondefinition);
                db.SaveChanges();
                return PartialView("GridData", new QuestionDefinition[] { questiondefinition });
            }

            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return PartialView("Edit", questiondefinition);
        }

        //
        // GET: /Quiz/Question/Edit/5

        public ActionResult Edit(int id)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return PartialView(questiondefinition);
        }

        //
        // POST: /Quiz/Question/Edit/5

        [HttpPost]
        public ActionResult Edit(QuestionDefinition questiondefinition)
        {
            if (ModelState.IsValid)
            {
                db.Entry(questiondefinition).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new QuestionDefinition[] { questiondefinition });
            }

            ViewBag.QuizDefinitionKey = new SelectList(db.QuizDefinitions, "Id", "QuizName", questiondefinition.QuizDefinitionKey);
            return PartialView(questiondefinition);
        }

        //
        // POST: /Quiz/Question/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            QuestionDefinition questiondefinition = db.QuestionDefinitions.Find(id);
            db.QuestionDefinitions.Remove(questiondefinition);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
