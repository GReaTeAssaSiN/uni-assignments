#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	system("color F0");
	setlocale(LC_ALL, "Rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Задание n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 0.0009};
	double epsilon2{ 3 * pow(10, -5) };
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();

			//Вывод первой таблицы.
			//При n = 10.
			std::cout << std::endl << "Приближенное решение задачи Коши методами Эйлера, Рунге-Кутта 4-го порядка точности без пересчета и методом Адамса " <<
				"при n = " << n1 << ":" << std::endl;
			printTableOne();
			FirstTable_methods(n1);
			std::cout << std::endl;
			//При n = 20.
			std::cout << std::endl << "Приближенное решение задачи Коши методами Эйлера, Рунге-Кутта 4-го порядка точности без пересчета и методом Адамса " <<
				"при n = " << n2 << ":" << std::endl;
			printTableOne();
			FirstTable_methods(n2);

			std::cout << std::endl;

			//Вывод второй таблицы.
			//При n = 10, epsilon = 0.0001.
			std::cout << std::endl << "Приближенное решение задачи Коши методом Рунге-Кутта 4-го порядка точности с пересчетом " <<
				"при n = " << n1 << ", h = " << (b - a) / n1 << " (до двойного пересчета) и epsilon = " << epsilon1 << ":" << std::endl;
			printTableTwo();
			SecondTable_methods(n1, epsilon1);
			std::cout << std::endl;
			//При n = 20, epsilon = 0.0001.
			std::cout << std::endl << "Приближенное решение задачи Коши методом Рунге-Кутта 4-го порядка точности с пересчетом " <<
				"при n = " << n2 << ", h = " << (b - a) / n2 << " (до двойного пересчета) и epsilon = " << epsilon2 << ":" << std::endl;
			printTableTwo();
			SecondTable_methods(n2, epsilon2);

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