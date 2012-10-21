
-- --------------------------------------------------
-- Entity Designer DDL Script for SQL Server 2005, 2008, and Azure
-- --------------------------------------------------
-- Date Created: 10/21/2012 08:33:18
-- Generated from EDMX file: D:\Code\EduEnginee\EduEnginee\Areas\Temp\Models\Admission.edmx
-- --------------------------------------------------

SET QUOTED_IDENTIFIER OFF;

USE [AdmissionDb];

IF SCHEMA_ID(N'dbo') IS NULL EXECUTE(N'CREATE SCHEMA [dbo]');


-- --------------------------------------------------
-- Dropping existing FOREIGN KEY constraints
-- --------------------------------------------------


-- --------------------------------------------------
-- Dropping existing tables
-- --------------------------------------------------


-- --------------------------------------------------
-- Creating all tables
-- --------------------------------------------------

-- Creating table 'InstituteTypes'
CREATE TABLE [dbo].[InstituteTypes] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Title] nvarchar(max)  NOT NULL
);


-- Creating table 'InstituteCataries'
CREATE TABLE [dbo].[InstituteCataries] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteTypeId] int  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Title] nvarchar(max)  NOT NULL
);


-- Creating table 'InstituteSubcataries'
CREATE TABLE [dbo].[InstituteSubcataries] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteCataryId] int  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Title] nvarchar(max)  NOT NULL
);


-- Creating table 'Institutes'
CREATE TABLE [dbo].[Institutes] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteSubcataryId] int  NOT NULL,
    [CountryId] int  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Title] nvarchar(max)  NOT NULL,
    [Phone] nvarchar(max)  NOT NULL,
    [EmailAddress] nvarchar(max)  NOT NULL,
    [WebSite] nvarchar(max)  NOT NULL,
    [EstablishDate] datetime  NOT NULL,
    [LoDirectory] nvarchar(max)  NOT NULL,
    [NoOfMaleStd] int  NOT NULL,
    [NoOfFemaleStd] int  NOT NULL,
    [NoOfTeacher] int  NULL,
    [NoOfMaleHostelSit] int  NOT NULL,
    [NoOfFemaleHostelSit] int  NOT NULL,
    [Location] nvarchar(max)  NOT NULL
);


-- Creating table 'Countries'
CREATE TABLE [dbo].[Countries] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [Name] nvarchar(max)  NOT NULL,
    [IsEnable] bit  NOT NULL
);


-- Creating table 'Comments'
CREATE TABLE [dbo].[Comments] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteId] int  NOT NULL,
    [CommentText] nvarchar(max)  NOT NULL,
    [CircularId] int  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL
);


-- Creating table 'Circulars'
CREATE TABLE [dbo].[Circulars] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteId] int  NOT NULL,
    [SeatPlan] varbinary(max)  NOT NULL,
    [Result] varbinary(max)  NOT NULL,
    [ResultLink] nvarchar(max)  NOT NULL,
    [SeatPlanLink] nvarchar(max)  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Session] nvarchar(max)  NOT NULL,
    [CourseType] nvarchar(max)  NOT NULL,
    [AdmissionReq] nvarchar(max)  NOT NULL,
    [ApplyProc] nvarchar(max)  NOT NULL,
    [AppStart] datetime  NULL,
    [AppEnd] datetime  NULL,
    [SubStart] datetime  NULL,
    [SubEnd] datetime  NULL,
    [EligibleCanDate] datetime  NULL,
    [AddDate] datetime  NULL,
    [ResDate] datetime  NULL,
    [AdmissionTypeId] int  NOT NULL,
    [Title] nvarchar(max)  NOT NULL
);


-- Creating table 'Subjects'
CREATE TABLE [dbo].[Subjects] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [CircularId] int  NOT NULL,
    [IsEnable] bit  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Credit] int  NULL,
    [DurationInMnth] int  NULL,
    [NoOfTeacher] int  NULL,
    [NoOfMaleStudent] int  NULL,
    [NoOfFemaleStudent] int  NULL
);


-- Creating table 'Notices'
CREATE TABLE [dbo].[Notices] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteId] int  NOT NULL,
    [Title] nvarchar(max)  NOT NULL,
    [Description] nvarchar(max)  NOT NULL,
    [Date] datetime  NULL
);


-- Creating table 'News'
CREATE TABLE [dbo].[News] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [InstituteId] int  NOT NULL,
    [CreatedBy] nvarchar(max)  NOT NULL,
    [CreatedDate] datetime  NOT NULL,
    [UpdatedBy] nvarchar(max)  NOT NULL,
    [UpdatedDate] datetime  NOT NULL,
    [Title] nvarchar(max)  NOT NULL,
    [Description] nvarchar(max)  NOT NULL,
    [Date] datetime  NULL
);


-- Creating table 'AdmissionTypes'
CREATE TABLE [dbo].[AdmissionTypes] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [Title] nvarchar(max)  NOT NULL
);


-- --------------------------------------------------
-- Creating all PRIMARY KEY constraints
-- --------------------------------------------------

-- Creating primary key on [Id] in table 'InstituteTypes'
ALTER TABLE [dbo].[InstituteTypes]
ADD CONSTRAINT [PK_InstituteTypes]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'InstituteCataries'
ALTER TABLE [dbo].[InstituteCataries]
ADD CONSTRAINT [PK_InstituteCataries]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'InstituteSubcataries'
ALTER TABLE [dbo].[InstituteSubcataries]
ADD CONSTRAINT [PK_InstituteSubcataries]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Institutes'
ALTER TABLE [dbo].[Institutes]
ADD CONSTRAINT [PK_Institutes]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Countries'
ALTER TABLE [dbo].[Countries]
ADD CONSTRAINT [PK_Countries]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Comments'
ALTER TABLE [dbo].[Comments]
ADD CONSTRAINT [PK_Comments]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Circulars'
ALTER TABLE [dbo].[Circulars]
ADD CONSTRAINT [PK_Circulars]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Subjects'
ALTER TABLE [dbo].[Subjects]
ADD CONSTRAINT [PK_Subjects]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'Notices'
ALTER TABLE [dbo].[Notices]
ADD CONSTRAINT [PK_Notices]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'News'
ALTER TABLE [dbo].[News]
ADD CONSTRAINT [PK_News]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- Creating primary key on [Id] in table 'AdmissionTypes'
ALTER TABLE [dbo].[AdmissionTypes]
ADD CONSTRAINT [PK_AdmissionTypes]
    PRIMARY KEY CLUSTERED ([Id] ASC);


-- --------------------------------------------------
-- Creating all FOREIGN KEY constraints
-- --------------------------------------------------

-- Creating foreign key on [InstituteTypeId] in table 'InstituteCataries'
ALTER TABLE [dbo].[InstituteCataries]
ADD CONSTRAINT [FK_InstituteTypeInstituteCatary]
    FOREIGN KEY ([InstituteTypeId])
    REFERENCES [dbo].[InstituteTypes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteTypeInstituteCatary'
CREATE INDEX [IX_FK_InstituteTypeInstituteCatary]
ON [dbo].[InstituteCataries]
    ([InstituteTypeId]);


-- Creating foreign key on [InstituteCataryId] in table 'InstituteSubcataries'
ALTER TABLE [dbo].[InstituteSubcataries]
ADD CONSTRAINT [FK_InstituteCataryInstituteSubcatary]
    FOREIGN KEY ([InstituteCataryId])
    REFERENCES [dbo].[InstituteCataries]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteCataryInstituteSubcatary'
CREATE INDEX [IX_FK_InstituteCataryInstituteSubcatary]
ON [dbo].[InstituteSubcataries]
    ([InstituteCataryId]);


-- Creating foreign key on [InstituteSubcataryId] in table 'Institutes'
ALTER TABLE [dbo].[Institutes]
ADD CONSTRAINT [FK_InstituteSubcataryInstitute]
    FOREIGN KEY ([InstituteSubcataryId])
    REFERENCES [dbo].[InstituteSubcataries]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteSubcataryInstitute'
CREATE INDEX [IX_FK_InstituteSubcataryInstitute]
ON [dbo].[Institutes]
    ([InstituteSubcataryId]);


-- Creating foreign key on [CountryId] in table 'Institutes'
ALTER TABLE [dbo].[Institutes]
ADD CONSTRAINT [FK_CountryInstitute]
    FOREIGN KEY ([CountryId])
    REFERENCES [dbo].[Countries]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_CountryInstitute'
CREATE INDEX [IX_FK_CountryInstitute]
ON [dbo].[Institutes]
    ([CountryId]);


-- Creating foreign key on [InstituteId] in table 'Comments'
ALTER TABLE [dbo].[Comments]
ADD CONSTRAINT [FK_InstituteComment]
    FOREIGN KEY ([InstituteId])
    REFERENCES [dbo].[Institutes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteComment'
CREATE INDEX [IX_FK_InstituteComment]
ON [dbo].[Comments]
    ([InstituteId]);


-- Creating foreign key on [InstituteId] in table 'Circulars'
ALTER TABLE [dbo].[Circulars]
ADD CONSTRAINT [FK_InstituteCircular]
    FOREIGN KEY ([InstituteId])
    REFERENCES [dbo].[Institutes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteCircular'
CREATE INDEX [IX_FK_InstituteCircular]
ON [dbo].[Circulars]
    ([InstituteId]);


-- Creating foreign key on [CircularId] in table 'Subjects'
ALTER TABLE [dbo].[Subjects]
ADD CONSTRAINT [FK_CircularSubject]
    FOREIGN KEY ([CircularId])
    REFERENCES [dbo].[Circulars]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_CircularSubject'
CREATE INDEX [IX_FK_CircularSubject]
ON [dbo].[Subjects]
    ([CircularId]);


-- Creating foreign key on [CircularId] in table 'Comments'
ALTER TABLE [dbo].[Comments]
ADD CONSTRAINT [FK_CircularComment]
    FOREIGN KEY ([CircularId])
    REFERENCES [dbo].[Circulars]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_CircularComment'
CREATE INDEX [IX_FK_CircularComment]
ON [dbo].[Comments]
    ([CircularId]);


-- Creating foreign key on [InstituteId] in table 'Notices'
ALTER TABLE [dbo].[Notices]
ADD CONSTRAINT [FK_InstituteNotice]
    FOREIGN KEY ([InstituteId])
    REFERENCES [dbo].[Institutes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteNotice'
CREATE INDEX [IX_FK_InstituteNotice]
ON [dbo].[Notices]
    ([InstituteId]);


-- Creating foreign key on [InstituteId] in table 'News'
ALTER TABLE [dbo].[News]
ADD CONSTRAINT [FK_InstituteNews]
    FOREIGN KEY ([InstituteId])
    REFERENCES [dbo].[Institutes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_InstituteNews'
CREATE INDEX [IX_FK_InstituteNews]
ON [dbo].[News]
    ([InstituteId]);


-- Creating foreign key on [AdmissionTypeId] in table 'Circulars'
ALTER TABLE [dbo].[Circulars]
ADD CONSTRAINT [FK_AdmissionTypeCircular]
    FOREIGN KEY ([AdmissionTypeId])
    REFERENCES [dbo].[AdmissionTypes]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;

-- Creating non-clustered index for FOREIGN KEY 'FK_AdmissionTypeCircular'
CREATE INDEX [IX_FK_AdmissionTypeCircular]
ON [dbo].[Circulars]
    ([AdmissionTypeId]);


-- --------------------------------------------------
-- Script has ended
-- --------------------------------------------------