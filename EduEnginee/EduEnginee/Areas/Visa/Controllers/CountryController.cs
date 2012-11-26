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
    public class CountryController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/Country/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.CountrySet.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Visa/Country/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.CountrySet.Count().ToString());
            ObjectQuery<CountrySet> countryset = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<CountrySet>();
            //countryset = countryset.Include(c => c.ContinentSet);
            countryset = countryset.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(countryset.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            CountrySet countryset = db.CountrySet.Find(id);
            return PartialView("GridData", new CountrySet[] { countryset });
        }

        //
        // GET: /Visa/Country/Create

        public ActionResult Create()
        {
            ViewBag.ContinentId = new SelectList(db.ContinentSet, "Id", "Title");
            return PartialView("Edit");
        }

        //
        // POST: /Visa/Country/Create

        [HttpPost]
        public ActionResult Create(CountrySet countryset)
        {
            if (ModelState.IsValid)
            {
                db.CountrySet.Add(countryset);
                db.SaveChanges();
                return PartialView("GridData", new CountrySet[] { countryset });
            }

            ViewBag.ContinentId = new SelectList(db.ContinentSet, "Id", "Title", countryset.ContinentId);
            return PartialView("Edit", countryset);
        }

        //
        // GET: /Visa/Country/Edit/5

        public ActionResult Edit(int id)
        {
            CountrySet countryset = db.CountrySet.Find(id);
            ViewBag.ContinentId = new SelectList(db.ContinentSet, "Id", "Title", countryset.ContinentId);
            return PartialView(countryset);
        }

        //
        // POST: /Visa/Country/Edit/5

        [HttpPost]
        public ActionResult Edit(CountrySet countryset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(countryset).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new CountrySet[] { countryset });
            }

            ViewBag.ContinentId = new SelectList(db.ContinentSet, "Id", "Title", countryset.ContinentId);
            return PartialView(countryset);
        }

        //
        // POST: /Visa/Country/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            CountrySet countryset = db.CountrySet.Find(id);
            db.CountrySet.Remove(countryset);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
