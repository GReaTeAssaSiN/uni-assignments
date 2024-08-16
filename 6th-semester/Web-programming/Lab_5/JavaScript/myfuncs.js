/*������ ������*/
//������� ��� ������� ������ ������.
function firstTask(G_OFF) {
    //��������� �������� ������������������ � �������� �� ��������� ������� �� URI-����������.
    var SCALE = parseFloat(getUrlParameter('scale'));
    var V_OFF = parseFloat(getUrlParameter('v_off'));
    document.getElementById('message').textContent = "'scale' = " + SCALE + "; 'v_off' = " + V_OFF + "; 'g_off' = " + G_OFF + ".";
    if (checkURIvalues(SCALE, V_OFF)) {
        //��������� ������� �������.
        const graph = document.getElementById('graph');
        graph.innerHTML = '';
        //���������� ������ � ������ �������, � ����� �������� �� ����������� � ���������.
        const graphWidth = graph.clientWidth;
        const graphHeight = graph.clientHeight;
        var midY = graphHeight / 2;
        var midX = graphWidth / 2;
        //��������� ����.
        var value_of_division = 50;
        for (var i = value_of_division / SCALE; i < graphWidth; i += value_of_division / SCALE) {//���, ������������ ��� �������.
            if (i != midX) {
                drawVerticalLine(i, 0, graphHeight, "gray", 1);
            }
        }
        for (var i = value_of_division / SCALE; i < graphHeight; i += value_of_division / SCALE) {//���, ������������ ��� �������.
            if (i != midY) {
                drawHorizontalLine(0, graphWidth, i, "gray", 1);
            }
        }
        drawAbscissaAxis(0, graphWidth, midY, value_of_division, midX, SCALE);
        drawOrdinateAxis(0, graphHeight, midX, value_of_division, midY, SCALE);
        //��������� �������� 0 � ������.
        document.getElementById('graph').innerHTML += "<div style ='position:absolute; margin-top: " + (midY + 3) + "px; margin-left: " + (midX + 5) + "px'>" + "0" + "</div>";
        //��������� ������� ������� y = 2 - x^3.
        drawGraph(0, graphWidth, 0, graphHeight, midX, midY, value_of_division, "blue", 2, G_OFF, V_OFF, SCALE);
    }
}
//������� ��� ��������� ��� �������.
function drawAbscissaAxis(x1, x2, midY, value_of_division, midX, scale) {
    //��������� ��� �������.
    var xstr = "";
    var xstr0 = "<img src='Images/pixel.png' width=1 height=2 style='position:absolute;";
    var x = x1;
    count = 0;
    value = (x2 - x1) / value_of_division / 2 * (-5) / scale; //���������� �������� ������ �������� �������.
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
    //��������� ������� ������ � �������.
    xstr += "<div style ='position:absolute; margin-top: " + (midY - 10) + "px; margin-left: " + (x2 + 7) + "px'>" + "x" + "</div>";
    xstr += "<div style ='position:absolute; margin-top: " + (midY - 8) + "px; margin-left: " + (x2 - 8) + "px'>&#9658</div>";
    document.getElementById('graph').innerHTML += xstr;
}
//������� ��� ��������� ��� �������.
function drawOrdinateAxis(y1, y2, midX, value_of_division, midY, scale) {
    //��������� ��� �������.
    var ystr = "";
    var ystr0 = "<img src='Images/pixel.png' width=3 height=1 style='position:absolute;";
    var y = y1;
    var count = 0;
    value = (y2 - y1) / value_of_division / 2 * 5 / scale; //���������� �������� �������� �������� �������.
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
    //��������� ������� ����� � �������.
    ystr += "<div style ='position:absolute; margin-top: " + (y1 - 20) + "px; margin-left: " + (midX - 5) + "px'>" + "y" + "</div>";
    ystr += "<div style ='position:absolute; margin-top: " + (y1 - 8) + "px; margin-left: " + (midX - 7) + "px'>&#9650</div>";
    document.getElementById('graph').innerHTML += ystr;
}
//������� ��� ��������� ����, ������������ ��� �������.
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
//������� ��� ��������� ����, ������������ ��� �������.
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
//������� ��� �������� URI-����������.
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
//������� ��� ������ URI-����������.
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
//������� ��� ��������� �������.
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
//������� ��� ���������� � ������ ������� x.
function x_to_3(x) {
    return x * x * x;
}
//�������� ������� �� �����������.
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
/*������ ������*/
//������ �� ��� ����: ��������, ������� ������ ����������� ����.
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
//������� ��� ���������� ������ 5 ���� � �� �����������.
function displayHand() {
    const handContainer = document.getElementById('currentHand');
    handContainer.innerHTML = '';
    //����� ��������� 5 ���� �� ������� � ������� (������, �.�. �����, ��������������).
    const cardKeys = Object.keys(cardImages);
    const shuffledCardKeys = shuffle(cardKeys);
    hand = shuffledCardKeys.slice(0, 5);
    //������� ��������� ������� hand � ������� ������ map, � ����� ���������� ����������� ���� � ��������� handContainer.
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
// ������� ��� ������������� �������.
function shuffle(array) {
    const shuffledArray = [...array];
    for (let i = shuffledArray.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [shuffledArray[i], shuffledArray[j]] = [shuffledArray[j], shuffledArray[i]];
    }
    return shuffledArray;
}
//������� ��� ������� ����.
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
// ������� ��� ����������� ������� ����-����� � ����.
function hasFullHouse() {
    if (hand.length != 0) {
        const ranks = {};
        hand.map(cardKey => cardKey.split('_')[3]).forEach(rank => {
            ranks[rank] = (ranks[rank] || 0) + 1;
        });

        // �������� ������� ���� � ������.
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