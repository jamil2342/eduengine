/****** Object:  ForeignKey [FK_CountryCouncellingFirm_CouncellingFirm]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_CouncellingFirm]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm] DROP CONSTRAINT [FK_CountryCouncellingFirm_CouncellingFirm]
GO
/****** Object:  ForeignKey [FK_CountryCouncellingFirm_Country]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_Country]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm] DROP CONSTRAINT [FK_CountryCouncellingFirm_Country]
GO
/****** Object:  ForeignKey [FK_ContinentCountry]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_ContinentCountry]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountrySet]'))
ALTER TABLE [dbo].[CountrySet] DROP CONSTRAINT [FK_ContinentCountry]
GO
/****** Object:  ForeignKey [FK_CountryForeignStudy]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryForeignStudy]') AND parent_object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]'))
ALTER TABLE [dbo].[ForeignStudySet] DROP CONSTRAINT [FK_CountryForeignStudy]
GO
/****** Object:  ForeignKey [FK_CountryVisaProcedure]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet] DROP CONSTRAINT [FK_CountryVisaProcedure]
GO
/****** Object:  ForeignKey [FK_VisaTypeVisaProcedure]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_VisaTypeVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet] DROP CONSTRAINT [FK_VisaTypeVisaProcedure]
GO
/****** Object:  Table [dbo].[CountryCouncellingFirm]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]') AND type in (N'U'))
DROP TABLE [dbo].[CountryCouncellingFirm]
GO
/****** Object:  Table [dbo].[ForeignStudySet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]') AND type in (N'U'))
DROP TABLE [dbo].[ForeignStudySet]
GO
/****** Object:  Table [dbo].[VisaProcedureSet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]') AND type in (N'U'))
DROP TABLE [dbo].[VisaProcedureSet]
GO
/****** Object:  Table [dbo].[CountrySet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CountrySet]') AND type in (N'U'))
DROP TABLE [dbo].[CountrySet]
GO
/****** Object:  Table [dbo].[ContinentSet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ContinentSet]') AND type in (N'U'))
DROP TABLE [dbo].[ContinentSet]
GO
/****** Object:  Table [dbo].[CouncellingFirmSet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CouncellingFirmSet]') AND type in (N'U'))
DROP TABLE [dbo].[CouncellingFirmSet]
GO
/****** Object:  Table [dbo].[VisaTypeSet]    Script Date: 11/28/2012 09:23:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[VisaTypeSet]') AND type in (N'U'))
DROP TABLE [dbo].[VisaTypeSet]
GO
/****** Object:  Table [dbo].[VisaTypeSet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[VisaTypeSet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[VisaTypeSet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
 CONSTRAINT [PK_VisaTypeSet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
SET IDENTITY_INSERT [dbo].[VisaTypeSet] ON
INSERT [dbo].[VisaTypeSet] ([Id], [Title]) VALUES (1, N'Student Visa')
INSERT [dbo].[VisaTypeSet] ([Id], [Title]) VALUES (2, N'Medical')
SET IDENTITY_INSERT [dbo].[VisaTypeSet] OFF
/****** Object:  Table [dbo].[CouncellingFirmSet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CouncellingFirmSet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[CouncellingFirmSet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Mobile] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Phone] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Fax] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Email] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Web] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Description] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[DirectorName] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Address] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
 CONSTRAINT [PK_CouncellingFirmSet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
SET IDENTITY_INSERT [dbo].[CouncellingFirmSet] ON
INSERT [dbo].[CouncellingFirmSet] ([Id], [Mobile], [Phone], [Fax], [Email], [Web], [Description], [DirectorName], [Address]) VALUES (1, N'01748293456', N'111', N'dfsa', N'jamil.0505038@gmail.com', N'www.google.com', N'This quiz is for normal purpose', N'jamil', N'Dhaka')
INSERT [dbo].[CouncellingFirmSet] ([Id], [Mobile], [Phone], [Fax], [Email], [Web], [Description], [DirectorName], [Address]) VALUES (2, N'0000000', N'000000', N'0000', N'00000', N'www.google.com', N'dsjklf
jkdl;s
', N'jdfsl', N'dsf')
INSERT [dbo].[CouncellingFirmSet] ([Id], [Mobile], [Phone], [Fax], [Email], [Web], [Description], [DirectorName], [Address]) VALUES (3, N'55555', N'000000', N'0000', N'jamil.0505038@gmail.com', N'www.google.com', N'ads
aaa', N'jamil', N'jjj
jjj')
SET IDENTITY_INSERT [dbo].[CouncellingFirmSet] OFF
/****** Object:  Table [dbo].[ContinentSet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ContinentSet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[ContinentSet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
 CONSTRAINT [PK_ContinentSet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
SET IDENTITY_INSERT [dbo].[ContinentSet] ON
INSERT [dbo].[ContinentSet] ([Id], [Title]) VALUES (1, N'Africa')
INSERT [dbo].[ContinentSet] ([Id], [Title]) VALUES (4, N'Australia')
INSERT [dbo].[ContinentSet] ([Id], [Title]) VALUES (5, N'America')
INSERT [dbo].[ContinentSet] ([Id], [Title]) VALUES (6, N'Entarctika')
INSERT [dbo].[ContinentSet] ([Id], [Title]) VALUES (7, N'Europe')
SET IDENTITY_INSERT [dbo].[ContinentSet] OFF
/****** Object:  Table [dbo].[CountrySet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CountrySet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[CountrySet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[ContinentId] [int] NOT NULL,
	[Title] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
 CONSTRAINT [PK_CountrySet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[CountrySet]') AND name = N'IX_FK_ContinentCountry')
CREATE NONCLUSTERED INDEX [IX_FK_ContinentCountry] ON [dbo].[CountrySet] 
(
	[ContinentId] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
GO
SET IDENTITY_INSERT [dbo].[CountrySet] ON
INSERT [dbo].[CountrySet] ([Id], [ContinentId], [Title]) VALUES (2, 1, N'Ruanda')
INSERT [dbo].[CountrySet] ([Id], [ContinentId], [Title]) VALUES (3, 4, N'Newzeland')
INSERT [dbo].[CountrySet] ([Id], [ContinentId], [Title]) VALUES (5, 5, N'Mexico')
INSERT [dbo].[CountrySet] ([Id], [ContinentId], [Title]) VALUES (7, 1, N'dsaf')
SET IDENTITY_INSERT [dbo].[CountrySet] OFF
/****** Object:  Table [dbo].[VisaProcedureSet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[VisaProcedureSet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Visafee] [nvarchar](50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[RequiredDocument] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Where_toApply] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[SpecialNote] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[PhotographyInformation] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[BasicRequirement] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[VisaTypeId] [int] NOT NULL,
	[Country_Id] [int] NOT NULL,
 CONSTRAINT [PK_VisaProcedureSet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]') AND name = N'IX_FK_CountryVisaProcedure')
CREATE NONCLUSTERED INDEX [IX_FK_CountryVisaProcedure] ON [dbo].[VisaProcedureSet] 
(
	[Country_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
GO
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]') AND name = N'IX_FK_VisaTypeVisaProcedure')
CREATE NONCLUSTERED INDEX [IX_FK_VisaTypeVisaProcedure] ON [dbo].[VisaProcedureSet] 
(
	[VisaTypeId] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
GO
SET IDENTITY_INSERT [dbo].[VisaProcedureSet] ON
INSERT [dbo].[VisaProcedureSet] ([Id], [Visafee], [RequiredDocument], [Where_toApply], [SpecialNote], [PhotographyInformation], [BasicRequirement], [VisaTypeId], [Country_Id]) VALUES (2, N'100', N'Hello world', N'Dhaka', N'fingerprint', N'there', N'Honours', 1, 2)
INSERT [dbo].[VisaProcedureSet] ([Id], [Visafee], [RequiredDocument], [Where_toApply], [SpecialNote], [PhotographyInformation], [BasicRequirement], [VisaTypeId], [Country_Id]) VALUES (3, N'100 taka', N'Hello world', N'Dhaka', N'dsfa', N'dasf', N'dasf', 1, 3)
SET IDENTITY_INSERT [dbo].[VisaProcedureSet] OFF
/****** Object:  Table [dbo].[ForeignStudySet]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[ForeignStudySet](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[VisaTypeId] [int] NOT NULL,
	[CountryId] [int] NOT NULL,
	[Degrees] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[SemesterOffer] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[RequirementsForBachelorsProgram] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[RequirementsForMastersProgram] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Subjects] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Expenses] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[ApplyProcedure] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[SupportingDocuments] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[CreditTransfer] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[OtherInformation] [nvarchar](max) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL,
	[Country_Id] [int] NOT NULL,
 CONSTRAINT [PK_ForeignStudySet] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]') AND name = N'IX_FK_CountryForeignStudy')
CREATE NONCLUSTERED INDEX [IX_FK_CountryForeignStudy] ON [dbo].[ForeignStudySet] 
(
	[Country_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
GO
SET IDENTITY_INSERT [dbo].[ForeignStudySet] ON
INSERT [dbo].[ForeignStudySet] ([Id], [VisaTypeId], [CountryId], [Degrees], [SemesterOffer], [RequirementsForBachelorsProgram], [RequirementsForMastersProgram], [Subjects], [Expenses], [ApplyProcedure], [SupportingDocuments], [CreditTransfer], [OtherInformation], [Country_Id]) VALUES (1, 1, 1, N'dsf', N'sdf', N'dfsa', N'df', N'dfs', N'adf', N'dsf', N'dsaf', N'df', N'ds', 3)
SET IDENTITY_INSERT [dbo].[ForeignStudySet] OFF
/****** Object:  Table [dbo].[CountryCouncellingFirm]    Script Date: 11/28/2012 09:23:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[CountryCouncellingFirm](
	[Country_Id] [int] NOT NULL,
	[CouncellingFirm_Id] [int] NOT NULL,
 CONSTRAINT [PK_CountryCouncellingFirm] PRIMARY KEY NONCLUSTERED 
(
	[Country_Id] ASC,
	[CouncellingFirm_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
)
END
GO
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]') AND name = N'IX_FK_CountryCouncellingFirm_CouncellingFirm')
CREATE NONCLUSTERED INDEX [IX_FK_CountryCouncellingFirm_CouncellingFirm] ON [dbo].[CountryCouncellingFirm] 
(
	[CouncellingFirm_Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON)
GO
/****** Object:  ForeignKey [FK_CountryCouncellingFirm_CouncellingFirm]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_CouncellingFirm]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm]  WITH CHECK ADD  CONSTRAINT [FK_CountryCouncellingFirm_CouncellingFirm] FOREIGN KEY([CouncellingFirm_Id])
REFERENCES [dbo].[CouncellingFirmSet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_CouncellingFirm]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm] CHECK CONSTRAINT [FK_CountryCouncellingFirm_CouncellingFirm]
GO
/****** Object:  ForeignKey [FK_CountryCouncellingFirm_Country]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_Country]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm]  WITH CHECK ADD  CONSTRAINT [FK_CountryCouncellingFirm_Country] FOREIGN KEY([Country_Id])
REFERENCES [dbo].[CountrySet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryCouncellingFirm_Country]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountryCouncellingFirm]'))
ALTER TABLE [dbo].[CountryCouncellingFirm] CHECK CONSTRAINT [FK_CountryCouncellingFirm_Country]
GO
/****** Object:  ForeignKey [FK_ContinentCountry]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_ContinentCountry]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountrySet]'))
ALTER TABLE [dbo].[CountrySet]  WITH CHECK ADD  CONSTRAINT [FK_ContinentCountry] FOREIGN KEY([ContinentId])
REFERENCES [dbo].[ContinentSet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_ContinentCountry]') AND parent_object_id = OBJECT_ID(N'[dbo].[CountrySet]'))
ALTER TABLE [dbo].[CountrySet] CHECK CONSTRAINT [FK_ContinentCountry]
GO
/****** Object:  ForeignKey [FK_CountryForeignStudy]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryForeignStudy]') AND parent_object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]'))
ALTER TABLE [dbo].[ForeignStudySet]  WITH CHECK ADD  CONSTRAINT [FK_CountryForeignStudy] FOREIGN KEY([Country_Id])
REFERENCES [dbo].[CountrySet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryForeignStudy]') AND parent_object_id = OBJECT_ID(N'[dbo].[ForeignStudySet]'))
ALTER TABLE [dbo].[ForeignStudySet] CHECK CONSTRAINT [FK_CountryForeignStudy]
GO
/****** Object:  ForeignKey [FK_CountryVisaProcedure]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet]  WITH CHECK ADD  CONSTRAINT [FK_CountryVisaProcedure] FOREIGN KEY([Country_Id])
REFERENCES [dbo].[CountrySet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_CountryVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet] CHECK CONSTRAINT [FK_CountryVisaProcedure]
GO
/****** Object:  ForeignKey [FK_VisaTypeVisaProcedure]    Script Date: 11/28/2012 09:23:21 ******/
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_VisaTypeVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet]  WITH CHECK ADD  CONSTRAINT [FK_VisaTypeVisaProcedure] FOREIGN KEY([VisaTypeId])
REFERENCES [dbo].[VisaTypeSet] ([Id])
GO
IF  EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_VisaTypeVisaProcedure]') AND parent_object_id = OBJECT_ID(N'[dbo].[VisaProcedureSet]'))
ALTER TABLE [dbo].[VisaProcedureSet] CHECK CONSTRAINT [FK_VisaTypeVisaProcedure]
GO
