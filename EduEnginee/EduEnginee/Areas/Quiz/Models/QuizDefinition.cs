//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;

namespace EduEnginee.Areas.Quiz.Models
{
    public partial class QuizDefinition
    {
        public QuizDefinition()
        {
            this.QuestionDefinitions = new HashSet<QuestionDefinition>();
            this.Quizzes = new HashSet<Quizze>();
        }
    
        public int Id { get; set; }
        public string QuizName { get; set; }
        public string Description { get; set; }
        public int TimeLimitInMinutes { get; set; }
        public string CreatedBy { get; set; }
        public Nullable<System.DateTime> CreatedDate { get; set; }
        public string UpdatedBy { get; set; }
        public Nullable<System.DateTime> UpdatedDate { get; set; }
    
        public virtual ICollection<QuestionDefinition> QuestionDefinitions { get; set; }
        public virtual ICollection<Quizze> Quizzes { get; set; }
    }
    
}