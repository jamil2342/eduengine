/// <reference path="_references.js" />

(function (window, undefined) {
    // Define the "MyApp" namespace
    var MyApp = window.MyApp = window.MyApp || {};

    // News class
    var entityType = "News:#EduEnginee.Areas.Admission.Models";
    MyApp.News = function (data) {
        var self = this;

        // Underlying data
        self.Id = ko.observable(data.Id);
        self.Title = ko.observable(data.Title);
        self.InstituteId = ko.observable(data.InstituteId);
        self.CreatedBy = ko.observable(data.CreatedBy);
        self.CreatedDate = ko.observable(data.CreatedDate);
        self.UpdatedBy = ko.observable(data.UpdatedBy);
        self.UpdatedDate = ko.observable(data.UpdatedDate);
        self.Description = ko.observable(data.Description);
        self.Date = ko.observable(data.Date);
        self.Institute = ko.observable(upshot.map(data.Institute, "Institute:#EduEnginee.Areas.Admission.Models"));
        upshot.addEntityProperties(self, entityType);
    }

    // NewsViewModel class
    MyApp.NewsViewModel = function (options) {
        var self = this;

        // Private properties
        var dataSourceOptions = {
            providerParameters: { url: options.serviceUrl, operationName: "GetNews" },
            entityType: entityType,
            bufferChanges: true,
            mapping: MyApp.News
        };
        var gridDataSource = new upshot.RemoteDataSource(dataSourceOptions);
        var editorDataSource = new upshot.RemoteDataSource(dataSourceOptions);
        var parentEntitiesOperationParameters = {};
        var institutesDataSource = new upshot.RemoteDataSource({
            providerParameters: { url: options.serviceUrl, operationName: "GetInstituteOptionsForNews", operationParameters: parentEntitiesOperationParameters },
            entityType: "Institute:#EduEnginee.Areas.Admission.Models",
            dataContext: editorDataSource.getDataContext()
        });

        // Data
        self.news = gridDataSource.getEntities();
        self.institutes = institutesDataSource.getEntitiesWithStatus({ capacity: 100 });
        self.editingNews = editorDataSource.getFirstEntity();
        self.successMessage = ko.observable().extend({ notify: "always" });
        self.errorMessage = ko.observable().extend({ notify: "always" });
        self.paging = new upshot.PagingModel(gridDataSource, {
            onPageChange: function (pageIndex, pageSize) {
                self.nav.navigate({ page: pageIndex, pageSize: pageSize });
            }
        });
        self.validationConfig = $.extend({
            resetFormOnChange: self.editingNews,
            submitHandler: function () { self.saveEdit() }
        }, editorDataSource.getEntityValidationRules());

        // Client-side navigation
        self.nav = new NavHistory({
            params: { edit: null, page: 1, pageSize: 10 },
            onNavigate: function (navEntry, navInfo) {
                self.paging.moveTo(navEntry.params.page, navEntry.params.pageSize);

                // Wipe out any old data so that it is not displayed in the UI while new data is being loaded 
                editorDataSource.revertChanges();
                editorDataSource.reset();
                institutesDataSource.reset();

                if (navEntry.params.edit) {
                    parentEntitiesOperationParameters.Id = Number(navEntry.params.edit) || null;
                    
                    // Load the list of institutes allowed for this particular news
                    institutesDataSource.refresh();

                    if (navEntry.params.edit == "new") {
                        // Create and begin editing a new news instance
                        editorDataSource.getEntities().push(new MyApp.News({}));
                    } else {
                        // Load and begin editing an existing news instance
                        editorDataSource.setFilter({ property: "Id", value: Number(navEntry.params.edit) }).refresh();
                    }
                } else {
                    // Not editing, so load the requested page of data to display in the grid
                    gridDataSource.refresh();
                }
            }
        }).initialize({ linkToUrl: true });

        // Public operations
        self.saveEdit = function () {
            editorDataSource.commitChanges(function () {
                self.successMessage("Saved News").errorMessage("");
                self.showGrid();
            });
        }
        self.revertEdit = function () { editorDataSource.revertChanges() }
        self.editNews = function (news) { self.nav.navigate({ edit: news.Id() }) }
        self.showGrid = function () { self.nav.navigate({ edit: null }) }
        self.createNews = function () { self.nav.navigate({ edit: "new" }) }
        self.deleteNews = function (news) {
            editorDataSource.deleteEntity(news);
            editorDataSource.commitChanges(function () {
                self.successMessage("Deleted News").errorMessage("");
                self.showGrid();
            });
        };

        // Error handling
        var handleServerError = function (httpStatus, message) {
            if (httpStatus === 200) {
                // Application domain error (e.g., validation error)
                self.errorMessage(message).successMessage("");
            } else {
                // System error (e.g., unhandled exception)
                self.errorMessage("Server error: HTTP status code: " + httpStatus + ", message: " + message).successMessage("");
            }
        }
        
        gridDataSource.bind({ refreshError: handleServerError, commitError: handleServerError });
        editorDataSource.bind({ refreshError: handleServerError, commitError: handleServerError });
    }
})(window);

