using System.Linq;
using System.Web.Http;
using System.Web.Http.Data.EntityFramework;

namespace EduEnginee.Controllers
{
    public partial class QuizDbController : DbDataController<EduEnginee.Models.QuizDbEntities>
    {
        public IQueryable<EduEnginee.Models.QuestionDefinition> GetQuestionDefinitions() {
            return DbContext.QuestionDefinitions.Include("QuizDefinition").OrderBy(q => q.Id);
        }

        public void InsertQuestionDefinition(EduEnginee.Models.QuestionDefinition entity) {
            InsertEntity(entity);
        }

        public void UpdateQuestionDefinition(EduEnginee.Models.QuestionDefinition entity) {
            UpdateEntity(entity);
        }

        public void DeleteQuestionDefinition(EduEnginee.Models.QuestionDefinition entity) {
            DeleteEntity(entity);
        }

        public IQueryable<EduEnginee.Models.QuizDefinition> GetQuizDefinitionOptionsForQuestionDefinition(int? id) {
            return DbContext.QuizDefinitions;
        }
    }
}
