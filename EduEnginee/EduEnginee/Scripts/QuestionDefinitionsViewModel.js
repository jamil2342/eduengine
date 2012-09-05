/// <reference path="_references.js" />

(function (window, undefined) {
    // Define the "MyApp" namespace
    var MyApp = window.MyApp = window.MyApp || {};

    // QuestionDefinition class
    var entityType = "QuestionDefinition:#EduEnginee.Models";
    MyApp.QuestionDefinition = function (data) {
        var self = this;

        // Underlying data
        self.Id = ko.observable(data.Id);
        
        self.SortOrder = ko.observable(data.SortOrder);
        self.QuizDefinitionKey = ko.observable(data.QuizDefinitionKey);
        self.QuestionText = ko.observable(data.QuestionText);
        self.Option1 = ko.observable(data.Option1);
        self.Option2 = ko.observable(data.Option2);
        self.Option3 = ko.observable(data.Option3);
        self.Option4 = ko.observable(data.Option4);
        self.Option5 = ko.observable(data.Option5);
        self.Option6 = ko.observable(data.Option6);
        self.CorrectAns = ko.observable(data.CorrectAns);
        self.CorrectAnsText = ko.observable(data.CorrectAnsText);
        self.Explanation = ko.observable(data.Explanation);
        self.QuizDefinition = ko.observable(upshot.map(data.QuizDefinition, "QuizDefinition:#EduEnginee.Models"));
        upshot.addEntityProperties(self, entityType);
    }

    // QuestionDefinitionsViewModel class
    MyApp.QuestionDefinitionsViewModel = function (options) {
        var self = this;

        // Private properties
        var dataSourceOptions = {
            providerParameters: { url: options.serviceUrl, operationName: "GetQuestionDefinitions" },
            entityType: entityType,
            bufferChanges: true,
            mapping: MyApp.QuestionDefinition
        };
        var gridDataSource = new upshot.RemoteDataSource(dataSourceOptions);
        var editorDataSource = new upshot.RemoteDataSource(dataSourceOptions);
        var parentEntitiesOperationParameters = {};
        var quizDefinitionsDataSource = new upshot.RemoteDataSource({
            providerParameters: { url: options.serviceUrl, operationName: "GetQuizDefinitionOptionsForQuestionDefinition", operationParameters: parentEntitiesOperationParameters },
            entityType: "QuizDefinition:#EduEnginee.Models",
            dataContext: editorDataSource.getDataContext()
        });

        // Data
        self.questionDefinitions = gridDataSource.getEntities();
        self.quizDefinitions = quizDefinitionsDataSource.getEntitiesWithStatus({ capacity: 100 });
        self.editingQuestionDefinition = editorDataSource.getFirstEntity();
        self.successMessage = ko.observable().extend({ notify: "always" });
        self.errorMessage = ko.observable().extend({ notify: "always" });
        self.paging = new upshot.PagingModel(gridDataSource, {
            onPageChange: function (pageIndex, pageSize) {
                self.nav.navigate({ page: pageIndex, pageSize: pageSize });
            }
        });
        self.validationConfig = $.extend({
            resetFormOnChange: self.editingQuestionDefinition,
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
                quizDefinitionsDataSource.reset();

                if (navEntry.params.edit) {
                    parentEntitiesOperationParameters.Id = Number(navEntry.params.edit) || null;
                    
                    // Load the list of quizDefinitions allowed for this particular questionDefinition
                    quizDefinitionsDataSource.refresh();

                    if (navEntry.params.edit == "new") {
                        // Create and begin editing a new questionDefinition instance
                        editorDataSource.getEntities().push(new MyApp.QuestionDefinition({}));
                    } else {
                        // Load and begin editing an existing questionDefinition instance
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
                self.successMessage("Saved QuestionDefinition").errorMessage("");
                self.showGrid();
            });
        }
        self.revertEdit = function () { editorDataSource.revertChanges() }
        self.editQuestionDefinition = function (questionDefinition) { self.nav.navigate({ edit: questionDefinition.Id() }) }
        self.showGrid = function () { self.nav.navigate({ edit: null }) }
        self.createQuestionDefinition = function () { self.nav.navigate({ edit: "new" }) }
        self.deleteQuestionDefinition = function (questionDefinition) {
            editorDataSource.deleteEntity(questionDefinition);
            editorDataSource.commitChanges(function () {
                self.successMessage("Deleted QuestionDefinition").errorMessage("");
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

