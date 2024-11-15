#ifndef CONVERT_H
#define CONVERT_H

#include "QString"

class Convert
{
public:
    //Методы преобразования.
    static QString ConvertDecToHex(const int& decNumber);
    static int ConvertHexToDec(const QString& hexNumber);
    static QString SubTwoHexNumbers(const QString& hexNumber1, const QString& hexNumber2);
};

#endif // CONVERT_H
