#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

unsigned char get_0_1()
{
    while (true)
    {
        char sm;
        std::cin >> sm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (sm == '0' || sm == '1')
        {
            return sm;
        }
        else
        {
            std::cout << "Ошибка ввода. Введите 0 или 1: \n";
        }
    }
}

bool getNext()
{
    std::cout << "Хотите повторить ввод исходных данных? Да - 1, Нет - 0:" << "\t";
    while (true)
    {
        char sm;
        std::cin >> sm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (sm == '0' || sm == '1')
        {
            return sm == '1' ? true : false;
        }
        else
        {
            std::cout << "Ошибка ввода. Введите 0 или 1: \n";
        }
    }
}

bool init(double mass[NM], unsigned &size)
{
    size = getSize();
    if (checksize(size))
    {
        for (unsigned i = 0; i < size; i++)
        {
            std::cout << "[" << i << "] = ";
            mass[i] = getValue();
        }
    }
    else
    {
        std::cout << "Введённое количество исходных конденсаторов в системе слишком большое, ноль или отрицательное." << std::endl;
        return false;
    }
    return true;
}

bool finit(std::ifstream& f, double mass[NM], unsigned& size)
{
    double b;
    f >> b;
    size = int(b);
    if (f.fail() || b <= 0 || b != size)
    {
        std::cout << "Ошибка ввода из файла \"in.txt\" количества конденсаторов. Проверьте, чтобы было натуральное число." << std::endl;
        return false;
    }
    for (unsigned i = 0; i < size; i++)
    {
        f >> mass[i];
        if (f.fail())
        {
            std::cout << "Ошибка ввода из файла \"in.txt\" элемента ["
                << i << "]." << std::endl;
            return false;
        }
    }
    return true;
}

unsigned getSize()
{
    std::cout << "Введите колиество исходных конденсаторов в системе: ";
    while (true)
    {
        unsigned a;
        std::cin >> a;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Вы ввели не число. Потвторите ввод: \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

bool checksize(unsigned &size)
{
    return (size > 0 && size < NM) ? true : false;
}

double getValue()
{
    while (true)
    {
        double a;
        std::cin >> a;
        if (std::cin.fail() || a <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Вы ввели не положительное число. Повторите ввод: \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

void connection_capasitor(std::ostream& f, double mass[NM], unsigned &size)
{
    f << "Исходный массив:" << std::endl;
    for (unsigned i = 0; i < size; i++)
        f << mass[i] << "\t";
    f << std::endl;
    f << "Емкость системы при последовательном соединении исходных конденсаторов:" << std::endl;
    double sum{ 0 };
    for (unsigned i = 0; i < size; i++)
        sum += (1 / mass[i]);
    f << 1 / sum << std::endl << std::endl;
    f << "Емкость системы при параллельном соединении исходных конденсаторов:" << std::endl;
    sum = 0;
    for (unsigned i = 0; i < size; i++)
        sum += mass[i];
    f << sum << std::endl << std::endl;
}