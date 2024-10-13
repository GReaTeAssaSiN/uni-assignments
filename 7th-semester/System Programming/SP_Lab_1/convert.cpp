#include "convert.h"
#include "array"

//Преобразование из десятичной СИ в шестнадцатиричную СИ.
QString Convert::DecToHex(const int& decNumber)
{
    QString hexNumber{""};
    std::array<char, 16>  hexMass = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
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
int Convert::HexToDec(const QString &hexNumber)
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

//Дополнение нулями числа в шестнадцатиричной СИ до 6 символов.
QString Convert::ConvertHexNumberToSixNumbers(const QString &hexNumber)
{
    const int lengthNumber{6};
    QString convertHexNumber{};
    //Если входная строка пустая, то вернуть "".
    if (hexNumber.isEmpty()){
        return "";
    }
    //Если длина входной строки <= 6, то привести к нужному виду.
    if (hexNumber.length() <= lengthNumber){
        int needZero = lengthNumber - hexNumber.length();//Количество нужных нулей.
        convertHexNumber.append(QString(needZero, '0'));
        convertHexNumber+=hexNumber;
    }
    else{//Иначе возвращается сама строка.
        convertHexNumber = hexNumber;
    }
    return convertHexNumber;
}

//Сложение двух чисел в шестнадцатиричной СИ.
QString Convert::SumHexNumbers(const QString &firstNumber, const QString &secondNumber)
{
    const int lengthNumber{6};
    QString sum{""};
    std::vector<QChar> sumChars(lengthNumber);
    QString hexNumbers{"0123456789ABCDEF"};

    if (firstNumber.isEmpty() || secondNumber.isEmpty()){
        return "";
    }

    bool carry{false}; //Для логики сложения и переноса (>15).

    //Обход чисел с конца.
    for (int i = lengthNumber - 1; i >=0; --i){
        int index1 = hexNumbers.indexOf(firstNumber[i]);
        int index2 = hexNumbers.indexOf(secondNumber[i]);

        int currentSum = index1 + index2 + (carry ? 1 : 0);

        carry = currentSum > 15;
        sumChars[i] = hexNumbers[currentSum % 16];

        if (i == 0 && carry){
            return "";
        }
    }

    for (const auto& ch : sumChars){
        sum += ch;
    }
    return sum;
}

//Вычитание двух чисел в шестнадцатиричной СИ.
QString Convert::SubHexNumbers(const QString &firstNumber, const QString &secondNumber)
{
    const int lengthNumber{6};
    QString sub{""};
    std::vector<QChar> subChars(lengthNumber);
    QString hexNumbers{"0123456789ABCDEF0123456789ABCDEF"};

    if (firstNumber.isEmpty() || secondNumber.isEmpty()){
        return "";
    }

    bool borrow{false}; //Для логики заимствования.
    int chr1;

    for (int i = lengthNumber - 1; i>=0; --i){
        if (borrow) {
            chr1 = hexNumbers.indexOf(firstNumber[i])-1;
        }
        else{
            chr1 = hexNumbers.indexOf(firstNumber[i]);
        }

        int chr2 = hexNumbers.indexOf(secondNumber[i]);

        if (chr1 >= chr2){
            subChars[i] = hexNumbers[chr1-chr2];
            borrow = false;
        }
        else{
            subChars[i]=hexNumbers[chr1+16-chr2];
            borrow = true;
        }
    }

    for (const auto& ch : subChars){
        sub += ch;
    }

    return sub;
}

//Дополнение нулями числа в шестнадцатиричной СИ до 2 символов.
QString Convert::ConvertHexNumberToTwoNumbers(const QString &hexNumber)
{
    const int lengthNumber{2};
    QString convertHexNumber{};
    //Если входная строка пустая, то вернуть "".
    if (hexNumber.isEmpty()){
        return "";
    }
    //Если длина входной строки <= 2, то привести к нужному виду.
    if (hexNumber.length() <= lengthNumber){
        int needZero = lengthNumber - hexNumber.length();//Количество нужных нулей.
        convertHexNumber.append(QString(needZero, '0'));
        convertHexNumber+=hexNumber;
    }
    else{//Иначе возвращается сама строка.
        convertHexNumber = hexNumber;
    }
    return convertHexNumber;
}

//Метод: 10 -> 16 СИ.
QString Convert::ConvertDecToHex(const int &decNumber)
{
    return DecToHex(decNumber);
}

//Метод: 16 -> 10 СИ.
int Convert::ConvertHexToDec(const QString &hexNumber)
{
    return HexToDec(hexNumber);
}

//Метод: 16 СИ с 6 символами.
QString Convert::ConvertToSixNumber(const QString& hexNumber){
    return ConvertHexNumberToSixNumbers(hexNumber);
}

//Результат сложения двух чисел в шестнадцатиричной СИ.
QString Convert::SumHexNumbersResult(const QString &firstNumber, const QString &secondNumber)
{
    return SumHexNumbers(firstNumber, secondNumber);
}

//Результат вычитания двух чисел в шестнадцатиричной СИ.
QString Convert::SubHexNumbersResult(const QString &firstNumber, const QString &secondNumber)
{
    return SubHexNumbers(firstNumber, secondNumber);
}

//Метод: 16 СИ с 2 символами.
QString Convert::ConvertToTwoNumber(const QString &hexNumber)
{
    return ConvertHexNumberToTwoNumbers(hexNumber);
}
