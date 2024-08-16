var main = function (toDoObjects) {
    "use strict";
    var toDos = toDoObjects.map(function (toDo) {
        var manufacturers = [];
        toDo.manufacturers.forEach(function (manufacturer) {
            manufacturers.push(manufacturer);
        });
        return [toDo.toolName, toDo.respPersonFullName, toDo.issueDate, manufacturers];
    });
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            //Проверка нажатой кнопки (ссылки)
            if ($element.parent().is(":nth-child(1)")) {
                $content = $("<div>");
                for (var i = toDoObjects.length - 1; i >= 0; i--) {
                    var $infoClassDiv = $("<div>").addClass("infoClass");

                    $infoClassDiv.append($("<h4>").text("Название инструмента: " + toDos[i][0]));
                    $infoClassDiv.append($("<h4>").text("ФИО ответственного: " + toDos[i][1]));
                    $infoClassDiv.append($("<h4>").text("Дата выдачи: " + toDos[i][2]));

                    $infoClassDiv.append($("<p>").text("Производитель(-и) инструмента:"));
                    var $innerUl = $("<ul>");
                    for (var j = 0; j < toDos[i][3].length; j++) {
                        var $innerLi = $("<li>").text(toDos[i][3][j]);
                        $innerUl.append($innerLi);
                    }
                    $infoClassDiv.append($innerUl);
                    $content.append($infoClassDiv);
                }
            }
            else if ($element.parent().is(":nth-child(2)")) {
                $content = $("<div>");
                for (var i = 0; i < toDoObjects.length; i++) {
                    var $infoClassDiv = $("<div>").addClass("infoClass");

                    $infoClassDiv.append($("<h4>").text("Название инструмента: " + toDos[i][0]));
                    $infoClassDiv.append($("<h4>").text("ФИО ответственного: " + toDos[i][1]));
                    $infoClassDiv.append($("<h4>").text("Дата выдачи: " + toDos[i][2]));

                    $infoClassDiv.append($("<p>").text("Производитель(-и) инструмента:"));
                    var $innerUl = $("<ul>");
                    for (var j = 0; j < toDos[i][3].length; j++) {
                        var $innerLi = $("<li>").text(toDos[i][3][j]);
                        $innerUl.append($innerLi);
                    }
                    $infoClassDiv.append($innerUl);
                    $content.append($infoClassDiv);
                }
            }
            else if ($element.parent().is(":nth-child(3)")) {
                $content = $("<div>");
                var manufacturers = {};
                for (var i = 0; i < toDoObjects.length; i++) {
                    for (var j = 0; j < toDoObjects[i].manufacturers.length; j++) {
                        var manufacturer = toDoObjects[i].manufacturers[j];
                        if (manufacturers.hasOwnProperty(manufacturer)) {
                            manufacturers[manufacturer].push(toDoObjects[i]);
                        } else {
                            manufacturers[manufacturer] = [toDoObjects[i]];
                        }
                    }
                }

                for (var manufacturer in manufacturers) {
                    if (manufacturers.hasOwnProperty(manufacturer)) {
                        var $manufacturerClassDiv = $("<div>").addClass("manufacturerClass");
                        $manufacturerClassDiv.append($("<p>").text("Производитель: " + manufacturer));
                        var $innerContent = $("<div>");
                        manufacturers[manufacturer].forEach(function (tool) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");
                            $infoClassDiv.append($("<h4>").text("Название инструмента: " + tool.toolName));
                            $infoClassDiv.append($("<h4>").text("ФИО ответственного: " + tool.respPersonFullName));
                            $infoClassDiv.append($("<h4>").text("Дата выдачи: " + tool.issueDate));
                            $innerContent.append($infoClassDiv);
                        });
                        $manufacturerClassDiv.append($innerContent);
                        $content.append($manufacturerClassDiv);
                    }
                }
            }
            else if ($element.parent().is(":nth-child(4)")) {
                $content = $("<div>");
                var responsiblesAndTools = {};
                for (var i = 0; i < toDoObjects.length; i++) {
                    var key = toDoObjects[i].respPersonFullName + "|" + toDoObjects[i].toolName;
                    if (responsiblesAndTools.hasOwnProperty(key)) {
                        responsiblesAndTools[key].push(toDoObjects[i]);
                    } else {
                        responsiblesAndTools[key] = [toDoObjects[i]];
                    }
                }

                for (var key in responsiblesAndTools) {
                    if (responsiblesAndTools.hasOwnProperty(key)) {
                        var $responsibleToolClassDiv = $("<div>").addClass("responsibleToolClass");
                        var keys = key.split("|");
                        $responsibleToolClassDiv.append($("<p>").text("ФИО ответственного: " + keys[0]));
                        $responsibleToolClassDiv.append($("<p>").text("Название инструмента: " + keys[1]));

                        responsiblesAndTools[key].forEach(function (additional_info) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");
                            $infoClassDiv.append($("<h4>").text("Дата выдачи: " + additional_info.issueDate));
                            $infoClassDiv.append($("<h4>").text("Производитель(-и): " + additional_info.manufacturers.join(", ")));
                            $responsibleToolClassDiv.append($infoClassDiv);
                        });
                        $content.append($responsibleToolClassDiv);
                    }
                }
            }
            else if ($element.parent().is(":nth-child(5)")) {
                //Добавление необходимых элементов.
                var $toolNameLabel = $("<p>").text("Название инструмента: "),
                    $toolNameInput = $("<input>").addClass("toolName"),
                    $respFullNameLabel = $("<p>").text("ФИО ответственного: "),
                    $respFullNameInput = $("<input>").addClass("respFullName"),
                    $issueDateLabel = $("<p>").text("Дата выдачи: "),
                    $issueDateInput = $("<input>").addClass("issueDate"),
                    $manufacturersLabel = $("<p>").text("Производитель(-и): "),
                    $manufacturersInput = $("<input>").addClass("manufacturers"),
                    $button = $("<button>").text("Добавить новую запись учета инструментов");

                $content = $("<div>").addClass("addNewData");
                $content.append($toolNameLabel);
                $content.append($toolNameInput);
                $content.append($respFullNameLabel);
                $content.append($respFullNameInput);
                $content.append($issueDateLabel);
                $content.append($issueDateInput);
                $content.append($manufacturersLabel);
                $content.append($manufacturersInput);
                $content.append($button);

                //Добавление новой записи учета инструментов.
                var addNewDataFromInputBox = function () {
                    if ($toolNameInput.val() !== "" && $respFullNameInput.val() !== "" && $issueDateInput.val() !== "" && $manufacturersInput.val() !== "") {
                        //Обработка данных при нажатии кнопки.
                        var tool = $toolNameInput.val();
                        var resp = $respFullNameInput.val();
                        var date = $issueDateInput.val();
                        var manufacturers = $manufacturersInput.val().split(",");
                        var taskData = [tool, resp, date, manufacturers];
                        toDos.push(taskData);
                        toDoObjects.push({
                            "toolName": tool,
                            "respPersonFullName": resp,
                            "issueDate": date,
                            "manufacturers": manufacturers
                        });
                        $toolNameInput.val("");
                        $respFullNameInput.val("");
                        $issueDateInput.val("");
                        $manufacturersInput.val("");
                    }
                }
                $button.on("click", function (event) {
                    addNewDataFromInputBox();
                });
                //Добавление записи учета инструментов при нажатии Enter в одном из полей ввода.
                $toolNameInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $respFullNameInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $issueDateInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
                $manufacturersInput.on("keypress", function (event) {
                    if (event.keyCode === 13) {
                        addNewDataFromInputBox();
                    }
                });
            }
            $("main .content").append($content);
            return false;
        });
    });
    $(".tabs a:first-child span").trigger("click");
};
$(document).ready(function () {
    $.getJSON("todos.json", function (classesObjs) {
        main(classesObjs);
    });
});