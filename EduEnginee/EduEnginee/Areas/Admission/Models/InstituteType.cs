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

namespace EduEnginee.Areas.Admission.Models
{
    public partial class InstituteType
    {
        public InstituteType()
        {
            this.InstituteCataries = new HashSet<InstituteCatary>();
        }
    
        public int Id { get; set; }
        public bool IsEnable { get; set; }
        public string CreatedBy { get; set; }
        public System.DateTime CreatedDate { get; set; }
        public string UpdatedBy { get; set; }
        public System.DateTime UpdatedDate { get; set; }
        public string Title { get; set; }
    
        public virtual ICollection<InstituteCatary> InstituteCataries { get; set; }
    }
    
}
