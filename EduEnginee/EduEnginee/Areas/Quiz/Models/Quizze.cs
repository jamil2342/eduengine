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
    public partial class Quizze
    {
        public Quizze()
        {
            this.QuizAnswers = new HashSet<QuizAnswer>();
        }
    
        public int Id { get; set; }
        public string Password { get; set; }
        public string Name { get; set; }
        public System.DateTime StartDate { get; set; }
        public System.DateTime EndDate { get; set; }
        public bool IsNameOptional { get; set; }
        public bool HasEnded { get; set; }
        public int QuizDefinitionID { get; set; }
    
        public virtual ICollection<QuizAnswer> QuizAnswers { get; set; }
        public virtual QuizDefinition QuizDefinition { get; set; }
    }
    
}