/*ПЕРВАЯ ЗАДАЧА*/
//Функция для решения первой задачи.
function firstTask(G_OFF) {
    //Получение значений пропорциональности и смещения по вертикали графика из URI-параметров.
    var SCALE = parseFloat(getUrlParameter('scale'));
    var V_OFF = parseFloat(getUrlParameter('v_off'));
    document.getElementById('message').textContent = "'scale' = " + SCALE + "; 'v_off' = " + V_OFF + "; 'g_off' = " + G_OFF + ".";
    if (checkURIvalues(SCALE, V_OFF)) {
        //Отрисовка области графика.
        const graph = document.getElementById('graph');
        graph.innerHTML = '';
        //Вычисление ширины и высоты области, а также середины по горизонтали и вертикали.
        const graphWidth = graph.clientWidth;
        const graphHeight = graph.clientHeight;
        var midY = graphHeight / 2;
        var midX = graphWidth / 2;
        //Отрисовка осей.
        var value_of_division = 50;
        for (var i = value_of_division / SCALE; i < graphWidth; i += value_of_division / SCALE) {//Оси, параллельные оси ординат.
            if (i != midX) {
                drawVerticalLine(i, 0, graphHeight, "gray", 1);
            }
        }
        for (var i = value_of_division / SCALE; i < graphHeight; i += value_of_division / SCALE) {//Оси, параллельные оси абсцисс.
            if (i != midY) {
                drawHorizontalLine(0, graphWidth, i, "gray", 1);
            }
        }
        drawAbscissaAxis(0, graphWidth, midY, value_of_division, midX, SCALE);
        drawOrdinateAxis(0, graphHeight, midX, value_of_division, midY, SCALE);
        //Отрисовка значения 0 в центре.
        document.getElementById('graph').innerHTML += "<div style ='position:absolute; margin-top: " + (midY + 3) + "px; margin-left: " + (midX + 5) + "px'>" + "0" + "</div>";
        //Отрисовка графика функции y = 2 - x^3.
        drawGraph(0, graphWidth, 0, graphHeight, midX, midY, value_of_division, "blue", 2, G_OFF, V_OFF, SCALE);
    }
}
//Функция для отрисовки оси абсцисс.
function drawAbscissaAxis(x1, x2, midY, value_of_division, midX, scale) {
    //Отрисовка оси абсцисс.
    var xstr = "";
    var xstr0 = "<img src='Images/pixel.png' width=1 height=2 style='position:absolute;";
    var x = x1;
    count = 0;
    value = (x2 - x1) / value_of_division / 2 * (-5) / scale; //Вычисление крайнего левого значения деления.
    while (x <= x2) {
        xstr += xstr0 + "margin-top:" + midY + "px;margin-left:" + x + "px'>";
        if (count == value_of_division) {
            value += 5 / scale;
            if (x != midX && x != x1 && x != x2) {
                drawVerticalLine(x, midY - 5, midY + 7, "black", 2);
                xstr += "<div style ='position:absolute; margin-top: " + (midY + 5) + "px; margin-left: " + (x + 5) + "px; font-size: 10px'>" + value.toFixed(2) + "</div>";
            }
            count = 0;
        }
        x++;
        count += 1;
    }
    //Отрисовка стрелки вправо и подписи.
    xstr += "<div style ='position:absolute; margin-top: " + (midY - 10) + "px; margin-left: " + (x2 + 7) + "px'>" + "x" + "</div>";
    xstr += "<div style ='position:absolute; margin-top: " + (midY - 8) + "px; margin-left: " + (x2 - 8) + "px'>&#9658</div>";
    document.getElementById('graph').innerHTML += xstr;
}
//Функция для отрисовки оси ординат.
function drawOrdinateAxis(y1, y2, midX, value_of_division, midY, scale) {
    //Отрисовка оси ординат.
    var ystr = "";
    var ystr0 = "<img src='Images/pixel.png' width=3 height=1 style='position:absolute;";
    var y = y1;
    var count = 0;
    value = (y2 - y1) / value_of_division / 2 * 5 / scale; //Вычисление крайнего верхнего значения деления.
    while (y <= y2) {
        ystr += ystr0 + "margin-top:" + y + "px;margin-left:" + midX + "px'>";
        if (count == value_of_division) {
            value -= 5 / scale;
            if (y != midY && y != y1 && y != y2) {
                drawHorizontalLine(midX - 5, midX + 7, y, "black", 2);
                ystr += "<div style ='position:absolute; margin-top: " + (y - 5) + "px; margin-left: " + (midX + 10) + "px; font-size: 10px'>" + value.toFixed(2) + "</div>";
            }
            count = 0;
        }
        y++;
        count++;
    }
    //Отрисовка стрелки вверх и подписи.
    ystr += "<div style ='position:absolute; margin-top: " + (y1 - 20) + "px; margin-left: " + (midX - 5) + "px'>" + "y" + "</div>";
    ystr += "<div style ='position:absolute; margin-top: " + (y1 - 8) + "px; margin-left: " + (midX - 7) + "px'>&#9650</div>";
    document.getElementById('graph').innerHTML += ystr;
}
//Функция для отрисовки осей, параллельных оси абсцисс.
function drawHorizontalLine(x1, x2, y, color, w) {
    var xstr = "";
    var xstr0 = "<div class='dot' style='position:absolute; background-color:" + color + "; width: " + w + "px ; height: " + w + "px;";
    var x = x1;
    while (x <= x2) {
        xstr += xstr0 + "margin-top:" + y + "px;margin-left:" + x + "px'></div>";
        x ++;
    }
    document.getElementById('graph').innerHTML += xstr;
}
//Функция для отрисовки осей, параллельных оси ординат.
function drawVerticalLine(x, y1, y2, color, w) {
    var ystr = "";
    var ystr0 = "<div class='dot' style='position:absolute; background-color:" + color + "; width: " + w + "px ; height: " + w + "px;";
    var y = y1;
    while (y <= y2) {
        ystr += ystr0 + "margin-top:" + y + "px;margin-left:" + x + "px'></div>";
        y++;
    }
    document.getElementById('graph').innerHTML += ystr;
}
//Функция для проверки URI-параметров.
function checkURIvalues(SCALE, V_OFF) {
    var correct = true;
    if (isNaN(SCALE) || SCALE != 0.5 && SCALE != 1 && SCALE != 2 && SCALE != 3 && SCALE != 4) {
        document.getElementById('message').textContent = "ERROR: URI-parameter 'scale' must be 0.5;1;2;3 or 5.";
        correct = false;
    }
    if (correct == true && (isNaN(V_OFF) || V_OFF > 30 / SCALE || V_OFF < -30 / SCALE)) {
        document.getElementById('message').textContent = "ERROR: URI-parameter 'v_off' must be >= " + (-30 / SCALE) + " and <= " + (30 / SCALE) + ".";
        correct = false;
    }
    return correct;
}
//Функция для чтения URI-параметров.
function getUrlParameter(sParam) {
    const sPageURL = decodeURIComponent(window.location.search.substring(1));
    const sURLVariables = sPageURL.split('&');
    for (let i = 0; i < sURLVariables.length; i++) {
        const sParameterName = sURLVariables[i].split('=');
        if (sParameterName[0] === sParam) {
            return sParameterName[1] === undefined ? false : sParameterName[1];
        }
    }
    return false;
}
//Функция для отрисовки графика.
function drawGraph(x1, x2, y1, y2, midX, midY, value_of_division, color, w, g_off, v_off, scale) {
    var gstr = "";
    var gstr0 = "<div class='dot' style='position:absolute; background-color:" + color + "; width: " + w + "px ; height: " + w + "px;";
    var x_left = (x2 - x1) / value_of_division / 2 * (-5) / scale;
    var x_right = (x2 - x1) / value_of_division / 2 * 5 / scale;
    var y_up = (y2 - y1) / value_of_division / 2 * 5 / scale;
    var y_down = (y2 - y1) / value_of_division / 2 * (-5) / scale;
    var x_current = x_left;
    while (x_current <= x_right) {
        var y = 2 - x_to_3(x_current);
        if ((y - v_off >= y_down) && (y - v_off <= y_up) && (x_current + g_off >= x_left) && (x_current + g_off <= x_right)) {
            gstr += gstr0 + "margin-top:" + (midY - y * 10 * scale + v_off * 10 * scale) + "px;margin-left:" + (midX + x_current * 10 * scale + g_off * 10 * scale) + "px'></div>";
        }
        x_current += 0.0005 / scale;
    }
    document.getElementById('graph').innerHTML += gstr;
}
//Функция для возведения в третью степень x.
function x_to_3(x) {
    return x * x * x;
}
//Смещение графика по горизонтали.
var G_OFF = 0;
function left() {
    G_OFF -= 1;
    firstTask(G_OFF);
}
function right() {
    G_OFF += 1;
    firstTask(G_OFF);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*ВТОРАЯ ЗАДАЧА*/
//Объект из пар ключ: значение, который хранит изображения карт.
const cardImages = {
    'Playing_card_spade_2': 'Images/40px-Playing_card_spade_2.svg.png',
    'Playing_card_heart_2': 'Images/40px-Playing_card_heart_2.svg.png',
    'Playing_card_diamond_2': 'Images/40px-Playing_card_diamond_2.svg.png',
    'Playing_card_club_2': 'Images/40px-Playing_card_club_2.svg.png',
    'Playing_card_spade_3': 'Images/40px-Playing_card_spade_3.svg.png',
    'Playing_card_heart_3': 'Images/40px-Playing_card_heart_3.svg.png',
    'Playing_card_diamond_3': 'Images/40px-Playing_card_diamond_3.svg.png',
    'Playing_card_club_3': 'Images/40px-Playing_card_club_3.svg.png',
    'Playing_card_spade_4': 'Images/40px-Playing_card_spade_4.svg.png',
    'Playing_card_heart_4': 'Images/40px-Playing_card_heart_4.svg.png',
    'Playing_card_diamond_4': 'Images/40px-Playing_card_diamond_4.svg.png',
    'Playing_card_club_4': 'Images/40px-Playing_card_club_4.svg.png',
    'Playing_card_spade_5': 'Images/40px-Playing_card_spade_5.svg.png',
    'Playing_card_heart_5': 'Images/40px-Playing_card_heart_5.svg.png',
    'Playing_card_diamond_5': 'Images/40px-Playing_card_diamond_5.svg.png',
    'Playing_card_club_5': 'Images/40px-Playing_card_club_5.svg.png',
    'Playing_card_spade_6': 'Images/40px-Playing_card_spade_6.svg.png',
    'Playing_card_heart_6': 'Images/40px-Playing_card_heart_6.svg.png',
    'Playing_card_diamond_6': 'Images/40px-Playing_card_diamond_6.svg.png',
    'Playing_card_club_6': 'Images/40px-Playing_card_club_6.svg.png',
    'Playing_card_spade_7': 'Images/40px-Playing_card_spade_7.svg.png',
    'Playing_card_heart_7': 'Images/40px-Playing_card_heart_7.svg.png',
    'Playing_card_diamond_7': 'Images/40px-Playing_card_diamond_7.svg.png',
    'Playing_card_club_7': 'Images/40px-Playing_card_club_7.svg.png',
    'Playing_card_spade_8': 'Images/40px-Playing_card_spade_8.svg.png',
    'Playing_card_heart_8': 'Images/40px-Playing_card_heart_8.svg.png',
    'Playing_card_diamond_8': 'Images/40px-Playing_card_diamond_8.svg.png',
    'Playing_card_club_8': 'Images/40px-Playing_card_club_8.svg.png',
    'Playing_card_spade_9': 'Images/40px-Playing_card_spade_9.svg.png',
    'Playing_card_heart_9': 'Images/40px-Playing_card_heart_9.svg.png',
    'Playing_card_diamond_9': 'Images/40px-Playing_card_diamond_9.svg.png',
    'Playing_card_club_9': 'Images/40px-Playing_card_club_9.svg.png',
    'Playing_card_spade_10': 'Images/40px-Playing_card_spade_10.svg.png',
    'Playing_card_heart_10': 'Images/40px-Playing_card_heart_10.svg.png',
    'Playing_card_diamond_10': 'Images/40px-Playing_card_diamond_10.svg.png',
    'Playing_card_club_10': 'Images/40px-Playing_card_club_10.svg.png',
    'Playing_card_spade_J': 'Images/40px-Playing_card_spade_J.svg.png',
    'Playing_card_heart_J': 'Images/40px-Playing_card_heart_J.svg.png',
    'Playing_card_diamond_J': 'Images/40px-Playing_card_diamond_J.svg.png',
    'Playing_card_club_J': 'Images/40px-Playing_card_club_J.svg.png',
    'Playing_card_spade_Q': 'Images/40px-Playing_card_spade_Q.svg.png',
    'Playing_card_heart_Q': 'Images/40px-Playing_card_heart_Q.svg.png',
    'Playing_card_diamond_Q': 'Images/40px-Playing_card_diamond_Q.svg.png',
    'Playing_card_club_Q': 'Images/40px-Playing_card_club_Q.svg.png',
    'Playing_card_spade_K': 'Images/40px-Playing_card_spade_K.svg.png',
    'Playing_card_heart_K': 'Images/40px-Playing_card_heart_K.svg.png',
    'Playing_card_diamond_K': 'Images/40px-Playing_card_diamond_K.svg.png',
    'Playing_card_club_K': 'Images/40px-Playing_card_club_K.svg.png',
    'Playing_card_spade_A': 'Images/40px-Playing_card_spade_A.svg.png',
    'Playing_card_heart_A': 'Images/40px-Playing_card_heart_A.svg.png',
    'Playing_card_diamond_A': 'Images/40px-Playing_card_diamond_A.svg.png',
    'Playing_card_club_A': 'Images/40px-Playing_card_club_A.svg.png'
};
let hand = [];
//Функция для случайного выбора 5 карт и их отображения.
function displayHand() {
    const handContainer = document.getElementById('currentHand');
    handContainer.innerHTML = '';
    //Выбор случайных 5 карт из массива с ключами (массив, т.е. карты, перемешивается).
    const cardKeys = Object.keys(cardImages);
    const shuffledCardKeys = shuffle(cardKeys);
    hand = shuffledCardKeys.slice(0, 5);
    //Перебор элементов массива hand с помощью метода map, а затем добавление изображений карт в контейнер handContainer.
    hand.map(cardKey => {
        const img = document.createElement('img');
        img.src = cardImages[cardKey];
        img.alt = 'Playing card';
        img.title = cardKey;
        return img;
    }).forEach(img => {
        handContainer.appendChild(img);
    });
}
// Функция для перемешивания массива.
function shuffle(array) {
    const shuffledArray = [...array];
    for (let i = shuffledArray.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [shuffledArray[i], shuffledArray[j]] = [shuffledArray[j], shuffledArray[i]];
    }
    return shuffledArray;
}
//Функция для очистки руки.
function clearHand() {
    if (hand.length != 0) {
        const handContainer = document.getElementById('currentHand');
        handContainer.innerHTML = '';
        hand = [];
        document.getElementById('playerMessage').textContent = "";
    }
    else
        document.getElementById('playerMessage').textContent = "ERROR: You must take the cards.";
}
// Функция для определения наличия фулл-хауса в руке.
function hasFullHouse() {
    if (hand.length != 0) {
        const ranks = {};
        hand.map(cardKey => cardKey.split('_')[3]).forEach(rank => {
            ranks[rank] = (ranks[rank] || 0) + 1;
        });

        // Проверка наличия пары и тройки.
        let hasPair = false;
        let hasThreeOfAKind = false;

        Object.values(ranks).forEach(count => {
            if (count === 2) {
                hasPair = true;
            } else if (count === 3) {
                hasThreeOfAKind = true;
            }
        });

        if (hasPair && hasThreeOfAKind) {
            document.getElementById('playerMessage').textContent = "There is a FULL-HOUSE! YOU'RE WINNER!:)";
        } else if (hasPair) {
            document.getElementById('playerMessage').textContent = "There is no three, but there is a couple.";
        } else if (hasThreeOfAKind) {
            document.getElementById('playerMessage').textContent = "There is no pair, but there is a three.";
        } else {
            document.getElementById('playerMessage').textContent = "There are no pairs or threes. No game!:(";
            throw new Error("ERROR: NO GAME!");
        }
    }
    else
        document.getElementById('playerMessage').textContent = "ERROR: You must take the cards.";
}