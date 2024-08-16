/*ВМЕСТО ФУНКЦИЙ ИСПОЛЬЗУЮТСЯ ФУНКЦИОНАЛЬНЫЕ ЛИТЕРАЛЫ*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЯ С ДАТАМИ*/

//Функция-обработчик для инициализации вычисления запрошенной даты по нажатию на интерактивный элемент.
var dateCalculator = function () {
    // Установка текста для указанных элементов документа.
    document.getElementById("current_date").textContent = getCurrentDate();
    document.getElementById("week_day").textContent = getWeekDay();
    document.getElementById("required_days").value = getSessionDays();
}
//Функция-исполнитель для вычисления текущей даты при загрузке HTML-страницы.
var getCurrentDate = function () {

    var date = new Date();

    var day = date.getDate();
    var month = date.getMonth();
    var year = date.getFullYear();

    if (day < 10) {
        day = '0' + day;
    }
    if (month < 10) {
        month = '0' + month;
    }

    return day + '.' + month + '.' + year;
}
//Функция-исполнитель для вычисления текущего дня недели при загрузке HTML-страницы.
var getWeekDay = function () {
    // Создаем объект для хранения названий дней недели.
    var daysOfWeek = {};

    // Заполняем объект свойствами для каждого дня недели.
    daysOfWeek[0] = "Sunday";
    daysOfWeek[1] = "Monday";
    daysOfWeek[2] = "Tuesday";
    daysOfWeek[3] = "Wednesday";
    daysOfWeek[4] = "Thursday";
    daysOfWeek[5] = "Friday";
    daysOfWeek[6] = "Saturday";

    // Получаем текущий день недели по номеру дня в неделе.
    var date = new Date();
    var dayIndex = date.getDay();
    var day_of_week = daysOfWeek[dayIndex];

    return day_of_week;
};

//Функция-исполнитель для вычисления дней, оставшихся до сессии.
var getSessionDays = function () {

    var current_date = new Date();
    var session_date = new Date(2024, 5, 10);
    return Math.ceil((session_date - current_date) / (1000 * 60 * 60 * 24));
}


//Функция-обработчик для вычисления дней, прошедших с памятной даты.
var getMemorableDate = function () {
    document.getElementById("memorable_button").innerText = calculateNumberDays();
}
//Функция-исполнитель для вычисления дней, прошедших с памятной даты.
var calculateNumberDays = function () {
    var memorableDate = prompt("Enter a memorable date for you (format: DD.MM.YYYY)", "04.03.2003");
    if (memorableDate !== null) {
        if (isValidDate(memorableDate)) {
            var parts = memorableDate.split('.');
            var entered_day = parseInt(parts[0]);
            var entered_month = parseInt(parts[1]);
            var entered_year = parseInt(parts[2]);
            var entered_date = new Date(entered_year, entered_month - 1, entered_day);
            var current_date = new Date();
            required_days = Math.ceil((current_date - entered_date) / (1000 * 60 * 60 * 24));
            //Проверка логической корректности вводимой даты.
            if (entered_date > current_date) {
                alert("The entered date should be in the past.");
                return;
            }
            if (entered_month < 1 || entered_month > 12) {
                alert("Incorrect month! Please enter a month between 01 and 12.");
                return;
            }
            var last_day_of_month = new Date(entered_year, entered_month, 0).getDate();
            if (entered_day < 1 || entered_day > last_day_of_month) {
                alert("Incorrect day! Please enter a day between 01 and " + last_day_of_month + " for the entered month.");
                return;
            }
            if (required_days > 365) {
                return required_days;
            }
            else {
                alert("The number of days must be greater than 365. Current number of days:" + required_days);
                return;
            }
        } else {
            alert("Incorrect date format! Please enter the date in DD.MM.YYYY format.");
            return;
        }
    }
}
//Функция-исполнитель для проверки корректности ввода даты.
var isValidDate = function (dateString) {
    var pattern = /^\d{2}\.\d{2}\.\d{4}$/;
    return pattern.test(dateString);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЕ ИЗ ЛАБОРАТОРНОЙ РАБОТЫ №3*/
// Функция-обработчик для проверки чисел.
var executeDigits = function () {
    document.getElementById("result_text").textContent = checkDigits();
}
// Функция-исполнитель для проверки чисел.
var checkDigits = function () {
    // Получение введенных пользователем чисел m и n.
    var numberM = document.getElementById('m').value;
    var numberN = document.getElementById('n').value;

    // Проверка на натуральное число, меньшее 9999.
    if (validateNumberFormat(numberM) && validateNumberFormat(numberN) && numberM < 9999 && numberN < 9999) {
        // Преобразование числа в объект с ключами, соответствующими цифрам.
        var digitsM = convertToDigitsObject(numberM);
        var digitsN = convertToDigitsObject(numberN);

        // Проверка совпадения цифр.
        var commonDigits = findCommonDigits(digitsM, digitsN);

        // Вывод результата в диалоговом окне.
        var resultMessage = '';

        if (commonDigits.length > 0) {
            resultMessage += 'The digits in number m that match digits in number n are: ' + commonDigits.join(', ');
        } else {
            resultMessage += 'The digits in the entered numbers do not match.';
        }

        return resultMessage;
    }
    else {
        return "Input error! Make sure both numbers m and n are entered correctly and are natural numbers less than 9999.";
    }
}
// Функция-исполнитель для проверки корректности вводимых чисел.
function validateNumberFormat(number) {
    var regex = /^[1-9]\d{0,3}$/;
    return regex.test(number);
}
// Функция-исполнитель для преобразования числа в объект с ключами, соответствующими цифрам.
function convertToDigitsObject(number) {
    var digitsObject = {};
    var digits = number.toString().split('').map(Number);
    digits.forEach(function (digit) {
        digitsObject[digit] = true;
    });
    return digitsObject;
}
// Функция-исполнитель для поиска общих цифр в двух объектах с цифрами.
function findCommonDigits(digitsObject1, digitsObject2) {
    var commonDigits = {};
    for (var digit in digitsObject1) {
        if (digitsObject2.hasOwnProperty(digit)) {
            commonDigits[digit] = true;
        }
    }
    return Object.keys(commonDigits);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/*ЗАДАНИЕ С ПОСЛЕДОВАТЕЛЬНОСТЬЮ*/
// Функция-обработчик вычисления суммы.
var calculateSum = function () {
    document.getElementById("calculated_sum").innerText = calculatingSum();
}
// Функция-исполнитель вычисления суммы.
var calculatingSum = function () {
    var userInput = document.getElementById("sequence").value;
    var flag = true;
    var number_first_elem;
    var number_of_elems;
    userInput = userInput.split(" ");
    if (userInput.length !== 2) {
        flag = false;
    }
    else {
        number_first_elem = userInput[0].trim();
        number_of_elems = userInput[1].trim();
        //Проверка корректности введенных данных.
        if (!isInteger(number_first_elem) || !isInteger(number_of_elems) || number_first_elem === "" || number_of_elems === "") {
            flag = false;
        }
    }
    if (!flag) {
        return "Error! Enter whole numbers or all numbers as specified.";
    }
    else {
        var sum = 0;
        var begin = parseInt(number_first_elem);
        var end = parseInt(number_first_elem) + parseInt(number_of_elems);
        for (var i = begin; i <= end; i++) {
            var term = 1 + Math.pow(-2, i);
            sum += term;
        }

        return "The sum of the terms of the sequence from the " + begin + " to the " + end + " numbers inclusive: " + sum;
    }
}
//Функция-исполнитель для проверки корректности введенных данных.
var isInteger = function (value) {
    for (var i = 0; i < value.length; i++) {
        if (value[i] < '0' || value[i] > '9') {
            return false;
        }
    }
    return true;
}