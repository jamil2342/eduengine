﻿//------------------------------------------------------------------------------
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
    using System.Data.Entity;
    using System.Data.Entity.Infrastructure;
    
    public partial class VisaEntities : DbContext
    {
        public VisaEntities()
            : base("name=VisaEntities")
        {
        }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            throw new UnintentionalCodeFirstException();
        }
    
        public DbSet<ContinentSet> ContinentSet { get; set; }
        public DbSet<CouncellingFirmSet> CouncellingFirmSet { get; set; }
        public DbSet<CountrySet> CountrySet { get; set; }
        public DbSet<ForeignStudySet> ForeignStudySet { get; set; }
        public DbSet<VisaProcedureSet> VisaProcedureSet { get; set; }
        public DbSet<VisaTypeSet> VisaTypeSet { get; set; }
    }
}