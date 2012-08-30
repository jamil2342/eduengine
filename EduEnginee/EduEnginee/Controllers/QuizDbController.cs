using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Data.EntityFramework;
using System.Web.Mvc;
using System.Web.Routing;

namespace EduEnginee.Controllers
{
    public partial class QuizDbController : DbDataController<EduEnginee.Models.QuizDbEntities>
    {
        // Any code added here will apply to all entity types managed by this data controller
    }

    // This provides context-specific route registration
    public class QuizDbRouteRegistration : AreaRegistration
    {
        public override string AreaName
        {
            get { return "QuizDb"; }
        }

        public override void RegisterArea(AreaRegistrationContext context)
        {
			RouteTable.Routes.MapHttpRoute(
                "QuizDb", // Route name
                "api/QuizDb/{action}", // URL with parameters
                new { controller = "QuizDb" } // Parameter defaults
            );
        }
    }
}
