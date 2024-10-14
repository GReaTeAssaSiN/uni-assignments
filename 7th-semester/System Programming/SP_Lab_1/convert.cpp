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
