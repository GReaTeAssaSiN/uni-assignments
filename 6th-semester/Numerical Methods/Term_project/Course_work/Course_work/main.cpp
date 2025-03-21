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
	//Задание n1=10, n2=20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 3 * pow(10, -3)};
	double epsilon2{ 1.1 * pow(10, -7) };
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			//При n = 10.
			std::cout << std::endl << "Приближенное решение задачи Коши для обыкновенного дифференциального уравнения методами производных высших порядков (до второго) " <<
				"при n = " << n1 << " и epsilon = " << epsilon1 << ":" << std::endl;
			second_derivative_method(n1, epsilon1);
			printDash();
			std::cout << std::endl;
			//При n = 10.
			std::cout << std::endl << "Приближенное решение задачи Коши для обыкновенного дифференциального уравнения методами производных высших порядков (до третьего) " <<
				"при n = " << n1 << " и epsilon = " << epsilon1 << ":" << std::endl;
			third_derivative_method(n1, epsilon1);
			printDash();
			std::cout << std::endl;
			//При n = 20.
			std::cout << std::endl << "Приближенное решение задачи Коши для обыкновенного дифференциального уравнения методами производных высших порядков (до второго) " <<
				"при n = " << n2 << " и epsilon = " << epsilon2 << ":" << std::endl;
			second_derivative_method(n2, epsilon2);
			printDash();
			std::cout << std::endl;
			//При n = 20.
			std::cout << std::endl << "Приближенное решение задачи Коши для обыкновенного дифференциального уравнения методами производных высших порядков (до третьего) " <<
				"при n = " << n2 << " и epsilon = " << epsilon2 << ":" << std::endl;
			third_derivative_method(n2, epsilon2);
			break;
		case '2':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}