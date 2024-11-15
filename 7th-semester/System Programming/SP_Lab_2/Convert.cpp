#include "convert.h"
#include "array"

//Преобразование из десятичной СИ в шестнадцатиричную СИ.
QString Convert::ConvertDecToHex(const int& decNumber)
{
    QString hexNumber{""};
    std::array<QChar, 16>  hexMass = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int div = decNumber;

    //Если число меньше 16, то добавляем его к hexNumber.
    if (div < 16){
        hexNumber += hexMass[div];
    }
    else{
        std::vector<int> mod; //Для хранения остатков в процессе перевода.
        while (div >= 16){
            mod.push_back(div % 16);
            div /= 16;
        }
        hexNumber += hexMass[div];//Добавляем последний остаток в шестнадцатиричной СИ.

        //Остальные остатки добавляются в обратном порядке.
        for (int i = mod.size() - 1; i >= 0; --i){
            hexNumber += hexMass[mod[i]];
        }
    }
    return hexNumber;
}

//Преобразование из шестнадцатиричной СИ в десятичную СИ.
int Convert::ConvertHexToDec(const QString &hexNumber)
{
    int decNumber{};
    const QString hexDigits{"0123456789ABCDEF"};

    for (int i{}; i < hexNumber.length(); ++i){
        int index = hexDigits.indexOf(hexNumber[i]);
        if (index != -1){//Если символ найден.
            decNumber += index * static_cast<int>(std::pow(16, hexNumber.length()-1-i));//Умножаем на 16 в степени позиции.
        }
        else{//Иначе ошибка.
            return -1;
        }
    }
    return decNumber;
}

//Преобразование разности двух чисел в 16 СИ с учетом отрицательного числа.
QString Convert::SubTwoHexNumbers(const QString &hexNumber1, const QString &hexNumber2)
{
    const int lengthNumber = 6; // Ожидаемая длина чисел.
    QString result = "";
    std::array<QChar, 16> hexNumbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if (hexNumber1.isEmpty() || hexNumber2.isEmpty()) {
        return "";
    }

    bool flag = false; // Флаг для заимствования.

    for (int i = lengthNumber - 1; i >= 0; i--)
    {
        // Получаем символы на текущей позиции.
        QChar chr1 = hexNumber1[i];
        QChar chr2 = hexNumber2[i];

        // Ищем индексы символов в массиве hexNumbers.
        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < 16; ++j) {
            if (hexNumbers[j] == chr1) {
                idx1 = j;
            }
            if (hexNumbers[j] == chr2) {
                idx2 = j;
            }
        }

        if (flag) {
            idx1 -= 1; // Если есть заимствование, уменьшаем значение первого числа.
        }

        // Если первый разряд больше или равен второму, вычитаем.
        if (idx1 >= idx2) {
            result += hexNumbers.at(idx1 - idx2);
            flag = false; // Нет заимствования.
        } else {
            // Если первый разряд меньше, значит нужно заимствовать.
            result += hexNumbers.at(idx1 + 16 - idx2);
            flag = true; // Устанавливаем флаг заимствования.
        }
    }

    // Переворачиваем строку, так как цифры добавлялись с конца.
    std::reverse(result.begin(), result.end());

    return result;
}
