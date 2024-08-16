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
	//Задание n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			
			//Вывод таблицы при n=10.
			std::cout << std::endl << "Решение заданной краевой задачи методом прогонки при n = " << n1 << ":" << std::endl;
			printTable();
			sweep_method(n1);

			//Вывод таблицы при n=20.
			std::cout << std::endl << "Решение заданной краевой задачи методом прогонки при n = " << n2 << ":" << std::endl;
			printTable();
			sweep_method(n2);

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