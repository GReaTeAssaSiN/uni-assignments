#ifndef CONVERT_H
#define CONVERT_H

#include "QString"

class Convert
{
private:
    //Внутренние методы для нужного преобразования.
    static QString DecToHex(const int& decNumber);
    static int HexToDec(const QString& hexNumber);
    static QString ConvertHexNumberToSixNumbers(const QString& hexNumber);
    static QString SumHexNumbers(const QString& firstNumber, const QString& secondNumber);
    static QString SubHexNumbers(const QString& firstNumber, const QString& secondNumber);
    static QString ConvertHexNumberToTwoNumbers(const QString& hexNumber);
public:
    Convert() = default;
    //Методы нужного преобразования.
    static QString ConvertDecToHex(const int& decNumber);
    static int ConvertHexToDec(const QString& hexNumber);
    static QString ConvertToSixNumber(const QString& hexNumber);
    static QString SumHexNumbersResult(const QString& firstNumber, const QString& secondNumber);
    static QString SubHexNumbersResult(const QString& firstNumber, const QString& secondNumber);
    static QString ConvertToTwoNumber(const QString& hexNumber);
};

#endif // CONVERT_H
