var main = function () {
    "use strict";
    $(".tabs a span").toArray().forEach(function (element) {
        $(element).on("click", function () {
            var $element = $(element),
                $content;
            $(".tabs a span").removeClass("active");
            $element.addClass("active");
            $("main .content").empty();
            //Новые -> Старые.
            if ($element.parent().is(":nth-child(1)")) {
                fetch("api/manufactures", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (manufactures) {
                        $content = $("<div>");
                        manufactures.reverse();
                        manufactures.forEach(function (item) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");

                            $infoClassDiv.append($("<h4>").text("Название инструмента: " + item.toolName));
                            $infoClassDiv.append($("<h4>").text("ФИО ответственного: " + item.respPersonFullName));
                            $infoClassDiv.append($("<h4>").text("Дата выдачи: " + item.issueDate));

                            $infoClassDiv.append($("<p>").text("Производитель(-и) инструмента:"));
                            var $innerUl = $("<ul>");

                            item.manufacturer.split(',').forEach(function (manufacturer) {
                                var $innerLi = $("<li>").text(manufacturer);
                                $innerUl.append($innerLi);
                            });
                            $infoClassDiv.append($innerUl);
                            $content.append($infoClassDiv);
                        });
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Старые -> Новые.
            } else if ($element.parent().is(":nth-child(2)")) {
                fetch("api/manufactures", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (manufactures) {
                        $content = $("<div>");
                        manufactures.forEach(function (item) {
                            var $infoClassDiv = $("<div>").addClass("infoClass");

                            $infoClassDiv.append($("<h4>").text("Название инструмента: " + item.toolName));
                            $infoClassDiv.append($("<h4>").text("ФИО ответственного: " + item.respPersonFullName));
                            $infoClassDiv.append($("<h4>").text("Дата выдачи: " + item.issueDate));

                            $infoClassDiv.append($("<p>").text("Производитель(-и) инструмента:"));
                            var $innerUl = $("<ul>");

                            item.manufacturer.split(',').forEach(function (manufacturer) {
                                var $innerLi = $("<li>").text(manufacturer);
                                $innerUl.append($innerLi);
                            });
                            $infoClassDiv.append($innerUl);
                            $content.append($infoClassDiv);
                        });
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Группировка по производителю.
            } else if ($element.parent().is(":nth-child(3)")) {
                fetch("api/manufactures", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (manufactures) {
                        var manufacturers = {};
                        manufactures.forEach(function (item) {
                            item.manufacturer.split(',').forEach(function (manufacturer) {
                                if (manufacturers.hasOwnProperty(manufacturer)) {
                                    manufacturers[manufacturer].push(item);
                                } else {
                                    manufacturers[manufacturer] = [item];
                                }
                            });
                        });

                        $content = $("<div>");
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
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            //Группировка по ФИО ответственного и названию инструмента.
            } else if ($element.parent().is(":nth-child(4)")) {
                fetch("api/manufactures", {
                    method: "GET",
                    headers: { "Accept": "application/json" }
                })
                    .then(function (response) {
                        if (response.ok) {
                            return response.json();
                        } else {
                            throw new Error('Ошибка получения данных');
                        }
                    })
                    .then(function (manufactures) {
                        var responsiblesAndTools = {};

                        manufactures.forEach(function (item) {
                            var key = item.respPersonFullName + "|" + item.toolName;
                            if (responsiblesAndTools.hasOwnProperty(key)) {
                                responsiblesAndTools[key].push(item);
                            } else {
                                responsiblesAndTools[key] = [item];
                            }
                        });

                        $content = $("<div>");
                        for (var key in responsiblesAndTools) {
                            if (responsiblesAndTools.hasOwnProperty(key)) {
                                var $responsibleToolClassDiv = $("<div>").addClass("responsibleToolClass");
                                var keys = key.split("|");
                                $responsibleToolClassDiv.append($("<p>").text("ФИО ответственного: " + keys[0]));
                                $responsibleToolClassDiv.append($("<p>").text("Название инструмента: " + keys[1]));

                                responsiblesAndTools[key].forEach(function (additional_info) {
                                    var $infoClassDiv = $("<div>").addClass("infoClass");
                                    $infoClassDiv.append($("<h4>").text("Дата выдачи: " + additional_info.issueDate));
                                    // Здесь нужно обработать разделение на производителей, если он представлен в формате строки, как и ранее.
                                    $infoClassDiv.append($("<h4>").text("Производитель(-и): " + additional_info.manufacturer));
                                    $responsibleToolClassDiv.append($infoClassDiv);
                                });
                                $content.append($responsibleToolClassDiv);
                            }
                        }
                        $("main .content").append($content);
                    })
                    .catch(function (error) {
                        console.error('Произошла ошибка при получении данных:', error);
                    });
            } else if ($element.parent().is(":nth-child(5)")) {
                $("main .content").empty();
                //Форма ввода.
                const $form = $("<form>").attr("id", "dataForm");
                $form.append(
                    $("<label>").text("ФИО ответственного:"),
                    $("<input>").attr({ type: "text", id: "respPersonFullName", name: "respPersonFullName" }),
                    $("<br>"),
                    $("<label>").text("Название инструмента:"),
                    $("<input>").attr({ type: "text", id: "toolName", name: "toolName" }),
                    $("<br>"),
                    $("<label>").text("Дата выдачи:"),
                    $("<input>").attr({ type: "date", id: "issueDate", name: "issueDate" }),
                    $("<br>"),
                    $("<label>").text("Производитель(-и):"),
                    $("<input>").attr({ type: "text", id: "manufacturer", name: "manufacturer" }),
                    $("<br>"),
                    $("<button>").attr({ type: "button", id: "saveBtn" }).addClass("btn").text("Сохранить"),
                    $("<button>").attr({ type: "button", id: "resetBtn" }).addClass("btn").text("Сбросить")
                );
                //Таблица.
                const $table = $("<table>").attr("id", "dataTable");
                $table.append(
                    $("<thead>").append(
                        $("<tr>").append(
                            $("<th>").text("ФИО ответственного"),
                            $("<th>").text("Название инструмента"),
                            $("<th>").text("Дата выдачи"),
                            $("<th>").text("Производитель(-и)"),
                            $("<th>").text("Действия")
                        )
                    ),
                    $("<tbody>")
                );
                
                $("main .content").append($form, $("<h2>").text("Записи в базе данных"), $table);

                // Функция для загрузки данных в таблицу.
                function loadData() {
                    fetch("api/manufactures", {
                        method: "GET",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                return response.json();
                            } else {
                                throw new Error('Ошибка получения данных');
                            }
                        })
                        .then(manufactures => {
                            const $tbody = $("#dataTable tbody");
                            $tbody.empty();

                            manufactures.forEach(manufacture => {
                                const $row = $("<tr>").append(
                                    $("<td>").text(manufacture.respPersonFullName),
                                    $("<td>").text(manufacture.toolName),
                                    $("<td>").text(manufacture.issueDate),
                                    $("<td>").text(manufacture.manufacturer),
                                    $("<td>").append(
                                        $("<button>")
                                            .attr("data-id", manufacture._id)
                                            .addClass("btn")
                                            .addClass("editBtn")
                                            .text("Изменить"),
                                        $("<button>")
                                            .attr("data-id", manufacture._id)
                                            .addClass("btn")
                                            .addClass("deleteBtn")
                                            .text("Удалить")
                                    )
                                );
                                $tbody.append($row);
                            });
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при получении данных:', error);
                        });
                }
                loadData();

                // Обработчик для кнопки изменения.
                $(document).on("click", ".editBtn", function () {
                    const id = $(this).attr("data-id");

                    fetch(`api/manufactures/${id}`, {
                        method: "GET",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                return response.json();
                            } else {
                                throw new Error('Ошибка получения данных');
                            }
                        })
                        .then(manufacture => {
                            // Заполнение формы данными текущей записи
                            $("#respPersonFullName").val(manufacture.respPersonFullName);
                            $("#toolName").val(manufacture.toolName);
                            $("#issueDate").val(manufacture.issueDate);
                            $("#manufacturer").val(manufacture.manufacturer);

                            // Сохранение идентификатора записи в скрытом поле формы или переменной
                            $("#dataForm").data("current-id", manufacture._id);
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при получении данных для изменения:', error);
                        });
                });

                // Обработчик для кнопки сохранения.
                $("#saveBtn").on("click", function () {
                    const respPersonFullName = $("#respPersonFullName").val().trim();
                    const toolName = $("#toolName").val().trim();
                    const issueDate = $("#issueDate").val().trim();
                    const manufacturer = $("#manufacturer").val().trim();

                    if (!respPersonFullName || !toolName || !issueDate || !manufacturer) {
                        alert("Пожалуйста, заполните все поля");
                        return;
                    }

                    const data = {
                        respPersonFullName: respPersonFullName,
                        toolName: toolName,
                        issueDate: issueDate,
                        manufacturer: manufacturer
                    };

                    const id = $("#dataForm").data("current-id");

                    const method = id ? "PUT" : "POST";
                    const url = id ? `api/manufactures/${id}` : "api/manufactures";

                    fetch(url, {
                        method: method,
                        headers: { "Content-Type": "application/json" },
                        body: JSON.stringify(data)
                    })
                        .then(response => {
                            if (response.ok) {
                                loadData();
                                alert(`Запись успешно ${id ? "изменена" : "добавлена"}`);
                                $("#dataForm")[0].reset();
                                $("#dataForm").removeData("current-id");
                            } else {
                                throw new Error(`Ошибка ${id ? "изменения" : "добавления"} записи`);
                            }
                        })
                        .catch(error => {
                            console.error(`Произошла ошибка при ${id ? "изменении" : "добавлении"} записи:`, error);
                        });
                });


                // Обработчик для кнопки сброса.
                $("#resetBtn").on("click", function () {
                    $("#dataForm")[0].reset();
                });

                // Обработчик для кнопки удаления.
                $(document).on("click", ".deleteBtn", function () {
                    const id = $(this).attr("data-id");

                    fetch(`api/manufactures/${id}`, {
                        method: "DELETE",
                        headers: { "Accept": "application/json" }
                    })
                        .then(response => {
                            if (response.ok) {
                                loadData();
                                alert("Запись успешно удалена");
                            } else {
                                throw new Error('Ошибка удаления записи');
                            }
                        })
                        .catch(error => {
                            console.error('Произошла ошибка при удалении записи:', error);
                        });
                });
            }
            return false;
        });
    });
    // Автоматически активируем первую вкладку
    $(".tabs a:first-child span").trigger("click");
};

$(document).ready(function () {
    main();
});
