using System.Web.Mvc;

namespace EduEnginee.Areas.StudyAbroad
{
    public class StudyAbroadAreaRegistration : AreaRegistration
    {
        public override string AreaName
        {
            get
            {
                return "StudyAbroad";
            }
        }

        public override void RegisterArea(AreaRegistrationContext context)
        {
            context.MapRoute(
                "StudyAbroad_default",
                "StudyAbroad/{controller}/{action}/{id}",
                new { action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}
