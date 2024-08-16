#include <iostream>
#include <string.h>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Инициализация заданной точности эпсилон и массива, характеризующего начальное приближение.
	double epsilon{}, init_approx_mas[3]{};
	//Флаг для учета выбора компонент начального приближения.
	bool flag_init_approx{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			//Задание точности эпсилон pow(10,-3).
			epsilon = 0.001;

			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//1)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, init_approx_mas, flag_init_approx);

			//2)
			//Информационная часть.
			printDash();
			std::cout << "Метод Зейделя (МЗ)." << std::endl;
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, init_approx_mas, flag_init_approx);

			//3)
			//Информационная часть.
			printDash();
			std::cout << "Метод релаксации (ослабления) (МР)." << std::endl;
			//Метод релаксации (ослабления) (МР).
			relaxationMethod(epsilon, init_approx_mas, flag_init_approx);

			//Задание точности эпсилон pow(10,-5).
			epsilon = 0.00001;

			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//4)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, init_approx_mas, flag_init_approx);

			//5))
			//Информационная часть.
			printDash();
			std::cout << "Метод Зейделя (МЗ)." << std::endl;
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, init_approx_mas, flag_init_approx);

			//6)
			//Информационная часть.
			printDash();
			std::cout << "Метод релаксации (ослабления) (МР)." << std::endl;
			//Метод релаксации (ослабления) (МР).
			relaxationMethod(epsilon, init_approx_mas, flag_init_approx);

			flag_init_approx = false;
			break;

			//Выбор другого значения точности эпсилон.
		case '2':
			printDash();
			//Задание точности эпсилон.
			if (epsilon == 0)
				epsilon = getEpsilon();
			else
				reselectEpsilonValue(epsilon);

			/*ЧИСЛЕННЫЕ МЕТОДЫ*/
			//1)
			//Информационная часть.
			printDash();
			std::cout << "Метод простых итераций (МПИ)." << std::endl;
			//Метод простых итераций (МПИ).
			simpleIterationMethod(epsilon, init_approx_mas, flag_init_approx);

			//2)
			//Информационная часть.
			printDash();
			std::cout << "Метод Зейделя (МЗ)." << std::endl;
			//Метод Зейделя (МЗ).
			seidelMethod(epsilon, init_approx_mas, flag_init_approx);

			//3)
			//Информационная часть.
			printDash();
			std::cout << "Метод релаксации (ослабления) (МР)." << std::endl;
			//Метод релаксации (ослабления) (МР).
			relaxationMethod(epsilon, init_approx_mas, flag_init_approx);
			
			flag_init_approx = false;
			break;

			//Выход из программы.
		case '3':
			cycle = false;
			break;
		default:;
		}
		printDash();
	}
	return 0;
}