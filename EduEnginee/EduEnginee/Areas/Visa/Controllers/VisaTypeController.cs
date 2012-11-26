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
    public class VisaTypeController : Controller
    {
        private VisaEntities db = new VisaEntities();

        //
        // GET: /Visa/VisaType/

        public ViewResult Index(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            ViewBag.Count = db.VisaTypeSet.Count();
            ViewBag.Start = start;
            ViewBag.ItemsPerPage = itemsPerPage;
            ViewBag.OrderBy = orderBy;
            ViewBag.Desc = desc;

            return View();
        }

        //
        // GET: /Visa/VisaType/GridData/?start=0&itemsPerPage=20&orderBy=Id&desc=true

        public ActionResult GridData(int start = 0, int itemsPerPage = 20, string orderBy = "Id", bool desc = false)
        {
            Response.AppendHeader("X-Total-Row-Count", db.VisaTypeSet.Count().ToString());
            ObjectQuery<VisaTypeSet> visatypeset = (db as IObjectContextAdapter).ObjectContext.CreateObjectSet<VisaTypeSet>();
            visatypeset = visatypeset.OrderBy("it." + orderBy + (desc ? " desc" : ""));

            return PartialView(visatypeset.Skip(start).Take(itemsPerPage));
        }

        //
        // GET: /Default5/RowData/5

        public ActionResult RowData(int id)
        {
            VisaTypeSet visatypeset = db.VisaTypeSet.Find(id);
            return PartialView("GridData", new VisaTypeSet[] { visatypeset });
        }

        //
        // GET: /Visa/VisaType/Create

        public ActionResult Create()
        {
            return PartialView("Edit");
        }

        //
        // POST: /Visa/VisaType/Create

        [HttpPost]
        public ActionResult Create(VisaTypeSet visatypeset)
        {
            if (ModelState.IsValid)
            {
                db.VisaTypeSet.Add(visatypeset);
                db.SaveChanges();
                return PartialView("GridData", new VisaTypeSet[] { visatypeset });
            }

            return PartialView("Edit", visatypeset);
        }

        //
        // GET: /Visa/VisaType/Edit/5

        public ActionResult Edit(int id)
        {
            VisaTypeSet visatypeset = db.VisaTypeSet.Find(id);
            return PartialView(visatypeset);
        }

        //
        // POST: /Visa/VisaType/Edit/5

        [HttpPost]
        public ActionResult Edit(VisaTypeSet visatypeset)
        {
            if (ModelState.IsValid)
            {
                db.Entry(visatypeset).State = EntityState.Modified;
                db.SaveChanges();
                return PartialView("GridData", new VisaTypeSet[] { visatypeset });
            }

            return PartialView(visatypeset);
        }

        //
        // POST: /Visa/VisaType/Delete/5

        [HttpPost]
        public void Delete(int id)
        {
            VisaTypeSet visatypeset = db.VisaTypeSet.Find(id);
            db.VisaTypeSet.Remove(visatypeset);
            db.SaveChanges();
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
