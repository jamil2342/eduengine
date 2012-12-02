using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Data.Objects;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Visa.Models;

namespace EduEnginee.Areas.Visa.Controllers
{
    public class ContinentController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/Continent/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.ContinentSet.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Visa/Continent/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.ContinentSet.Count().ToString());
            ObjectQuery<ContinentSet> continentset = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<ContinentSet>();
            continentset = continentset.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(continentset.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            ContinentSet continentset = db.ContinentSet.Find(id);
            return PartialView("GridData", new ContinentSet[] { continentset });
        }


        public ActionResult _TabGroup()
        {
            return PartialView(db.ContinentSet.ToList());
        }

        //
        // GET: /Visa/Continent/Create

        public ActionResult Create()
        {
            return PartialView("Edit");
        }

        //
        // POST: /Visa/Continent/Create

        [HttpPost]
        public ActionResult Create(ContinentSet continentset)
        {
            if (ModelState.IsValid)
            {
                db.ContinentSet.Add(continentset);
                db.SaveChanges();
                return PartialView("GridData", new ContinentSet[] { continentset });
            }

            return PartialView("Edit", continentset);
        }

        //
        // GET: /Visa/Continent/Edit/5

        public ActionResult Edit(int id)
        {
            ContinentSet continentset = db.ContinentSet.Find(id);
            return PartialView(continentset);
        }

        //
        // POST: /Visa/Continent/Edit/5

        [HttpPost]
        public ActionResult Edit(ContinentSet continentset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(continentset).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new ContinentSet[] { continentset });
            }

            return PartialView(continentset);
        }

        //
        // POST: /Visa/Continent/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            ContinentSet continentset = db.ContinentSet.Find(id);
            db.ContinentSet.Remove(continentset);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
