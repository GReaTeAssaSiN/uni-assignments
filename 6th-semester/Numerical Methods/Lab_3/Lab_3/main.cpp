#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	//system("color F0");
	setlocale(LC_ALL, "Rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Значение S для неявной схемы метода сеток.
	double S{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();

			S = getSvalue();
			printDash();
			std::cout << std::endl;
			std::cout.unsetf(std::ios::fixed);
			std::cout << "Результаты вычислений при S = " << S << std::endl;
			std::cout << "Метод сеток. Явная схема:" << std::endl;
			explicit_schema();
			std::cout << std::endl;
			std::cout << "Метод сеток. Неявная схема:" << std::endl;
			implicit_schema(S);
			
			break;

			//Выход из программы.
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}