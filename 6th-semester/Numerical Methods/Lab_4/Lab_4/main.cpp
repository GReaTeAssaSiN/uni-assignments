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
	//Значение a для вычисления шага.
	//double a{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();

			//a = getAvalue();
			printDash();
			std::cout << std::endl;
			//std::cout << "Результаты вычислений при a = " << a << std::endl;
			std::cout << "Метод сеток:" << std::endl;
			grid_method(1.0);

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