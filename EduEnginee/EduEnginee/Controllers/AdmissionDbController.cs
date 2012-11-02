using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Data.EntityFramework;
using System.Web.Mvc;
using System.Web.Routing;

namespace EduEnginee.Areas.Admission.Controllers
{
    public partial class AdmissionDbController : LinqToEntitiesDataController<EduEnginee.Areas.Admission.Models.AdmissionDbEntities>
    {
        // Any code added here will apply to all entity types managed by this data controller
    }

    // This provides context-specific route registration
    public class AdmissionDbRouteRegistration : AreaRegistration
    {
        public override string AreaName
        {
            get { return "AdmissionDb"; }
        }

        public override void RegisterArea(AreaRegistrationContext context)
        {
			RouteTable.Routes.MapHttpRoute(
                "AdmissionDb", // Route name
                "api/AdmissionDb/{action}", // URL with parameters
                new { controller = "AdmissionDb" } // Parameter defaults
            );
        }
    }
}
