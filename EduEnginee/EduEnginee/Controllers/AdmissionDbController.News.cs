using System.Linq;
using System.Web.Http;
using System.Web.Http.Data.EntityFramework;

namespace EduEnginee.Areas.Admission.Controllers
{
    public partial class AdmissionDbController : LinqToEntitiesDataController<EduEnginee.Areas.Admission.Models.AdmissionDbEntities>
    {
        public IQueryable<EduEnginee.Areas.Admission.Models.News> GetNews() {
            return ObjectContext.News.Include("Institute").OrderBy(n => n.Id);
        }

        public void InsertNews(EduEnginee.Areas.Admission.Models.News entity) {
            InsertEntity(entity);
        }

        public void UpdateNews(EduEnginee.Areas.Admission.Models.News entity) {
            UpdateEntity(entity);
        }

        public void DeleteNews(EduEnginee.Areas.Admission.Models.News entity) {
            DeleteEntity(entity);
        }

        public IQueryable<EduEnginee.Areas.Admission.Models.Institute> GetInstituteOptionsForNews(int? id) {
            return ObjectContext.Institutes;
        }
    }
}
