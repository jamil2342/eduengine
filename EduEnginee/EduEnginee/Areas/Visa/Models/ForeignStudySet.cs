//------------------------------------------------------------------------------
// <auto-generated>
//    This code was generated from a template.
//
//    Manual changes to this file may cause unexpected behavior in your application.
//    Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace EduEnginee.Areas.Visa.Models
{
    using System;
    using System.Collections.Generic;
    
    public partial class ForeignStudySet
    {
        public int Id { get; set; }
        public int VisaTypeId { get; set; }
        public int CountryId { get; set; }
        public string Degrees { get; set; }
        public string SemesterOffer { get; set; }
        public string RequirementsForBachelorsProgram { get; set; }
        public string RequirementsForMastersProgram { get; set; }
        public string Subjects { get; set; }
        public string Expenses { get; set; }
        public string ApplyProcedure { get; set; }
        public string SupportingDocuments { get; set; }
        public string CreditTransfer { get; set; }
        public string OtherInformation { get; set; }
        public int Country_Id { get; set; }
    
        public virtual CountrySet CountrySet { get; set; }
    }
}
