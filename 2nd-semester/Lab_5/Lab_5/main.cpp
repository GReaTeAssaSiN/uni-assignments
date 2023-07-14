#include <iostream>
#include <string>
#include <math.h>
#include "myfuncs.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	if (argc == 4)
	{
		unsigned long long nnum;
		unsigned int bit;
		unsigned long long nbit;
		try
		{
			nnum = std::stoull(argv[1]);
			bit = static_cast<unsigned int>(std::stoi(argv[2]));
			nbit = static_cast<unsigned long long>(std::stoi(argv[3]));
		}
		catch (const::std::invalid_argument& ia)
		{
			std::cerr << "Невозможно преобразовать аргумент(-ы) в число типа: " << ia.what() << std::endl;
			return 0;
		}
		unsigned long long copynnum{ nnum };
		unsigned int flag{ 1 };
		if (static_cast<unsigned long long>(nnum) < 0 || static_cast<long long>(nnum) > 18446744073709551615)
		{
			std::cout << "Ошибка ввода числа nnum! Введите в следующий раз число в диапазоне 8 байт (от 0 до 2^64-1)." << std::endl;
			return 0;
		}
		if (nbit >= 0 && nbit <= 64)
		{
			nnum = shiftr(nnum, bit, nbit, flag);
			if (flag != 0)
			{
				std::cout << "Исходное значение nnum : " << copynnum << std::endl;
				std::cout << "Значение nnum после замены бита в указанной позиции: " << nnum << std::endl;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			std::cerr << "Неверно указана позиция записываемого бита nbit!" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "Необходимо указать четыре аргумента командной строки: "
			<< "**путь до программы**, **число nnum**, **бит bit**, **позицию бита nbit**." << std::endl;
	}
	return 0;
}