using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using EduEnginee.Areas.Admission.Models;
using EduEnginee.Areas.Admission.Controllers;

namespace EduEnginee.Areas.Admission.Controllers
{
    public class InController : Controller
    {
        private AdmissionDbEntities db = new AdmissionDbEntities();

        //
        // GET: /Admission/In/


        public void PopulateInstituteDropDownList()
        {
            var instituteQry = from d in db.Institutes
                               orderby d.Title
                               where !String.IsNullOrEmpty(d.Title)
                               select d;
            ViewBag.InstituteId = new SelectList(instituteQry, "Id", "Title");
        }

        public ActionResult Index()
        {
            return View(db.InstituteTypes.ToList());
        }


        public ActionResult _insCat(int InsTypeId)
        {
            var qry = from q in db.InstituteCataries
                      where q.InstituteTypeId == InsTypeId
                      select q;
            return PartialView(qry.ToList());
        }


        public ActionResult InsSubCatList(int? InsCatId)
        {
            var qry = from q in db.InstituteSubcataries
                      where q.InstituteCataryId == InsCatId
                      select q;

            return View(qry.ToList());
        }





        public ActionResult InstituteList(int insSubCatId)
        {
            var qry = from q in db.Institutes
                      where q.InstituteSubcataryId == insSubCatId && !String.IsNullOrEmpty(q.Title) && !q.Title.Contains("N/A")
                      select q;
            return PartialView(qry.ToList());
        }



        public ActionResult _ShortDetails(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            return PartialView(institute);
        }

        //
        // GET: /Admission/In/Details/5

        public ActionResult Details(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            return View("Details",institute);
        }





        //
        // GET: /Admission/In/Create
        [Authorize(Roles="admin")]
        public ActionResult _Create()
        {
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name");
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title");
            return PartialView();
        }
        //
        // GET: /Admission/In/Create
        [Authorize(Roles="admin")]
        public ActionResult Create(string mode)
        {
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name");
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title");
            if (mode!="partial")
            {
                return View(); 
            }
            else
            {
                return PartialView("_Create");
            }
        }

        //
        // POST: /Admission/In/Create
        [Authorize(Roles="admin")]
        [HttpPost]
        public ActionResult Create(Institute institute)
        {
            institute.CreatedBy = User.Identity.Name;
            institute.CreatedDate = System.DateTime.Now;

            institute.UpdatedBy = User.Identity.Name;
            institute.UpdatedDate = System.DateTime.Now;

            if (ModelState.IsValid)
            {
                db.Institutes.AddObject(institute);
                db.SaveChanges();
                //return RedirectToAction("Index");
            }

            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return Details(institute.Id);
        }

        //
        // GET: /Admission/In/Edit/5
        [Authorize(Roles="admin")]
        public ActionResult Edit(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return View(institute);
        }

        //
        // POST: /Admission/In/Edit/5
        [Authorize(Roles="admin")]
        [HttpPost]
        public ActionResult Edit(Institute institute)
        {
            institute.UpdatedBy = User.Identity.Name;
            institute.UpdatedDate = System.DateTime.Now;

            if (ModelState.IsValid)
            {
                db.Institutes.Attach(institute);
                db.ObjectStateManager.ChangeObjectState(institute, EntityState.Modified);
                db.SaveChanges();
                //return RedirectToAction("Index");
            }
            ViewBag.CountryId = new SelectList(db.Countries, "Id", "Name", institute.CountryId);
            ViewBag.InstituteSubcataryId = new SelectList(db.InstituteSubcataries, "Id", "Title", institute.InstituteSubcataryId);
            return Details(institute.Id);
        }

        //
        // GET: /Admission/In/Delete/5
        [Authorize(Roles="admin")]
        public ActionResult Delete(int id = 0)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            if (institute == null)
            {
                return HttpNotFound();
            }
            return View(institute);
        }

        //
        // POST: /Admission/In/Delete/5
        [Authorize(Roles="admin")]
        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {
            Institute institute = db.Institutes.Single(i => i.Id == id);
            db.Institutes.DeleteObject(institute);
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