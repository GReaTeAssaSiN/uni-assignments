#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//Вывод информации о выданном задании.
	printTask();
	printDash();
	//Выбор 3-х значений из выбранного отрезка [a;b];
	long double x1{}, x2{}, x3{};
	//Организация циклического выполнения программы.
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
			//Выполнение требования, выданного к заданию.
		case '1':
			printDash();
			//Получение 3-х значений из выбранного отрезка [a;b].
			x1 = getXValue(1);
			x2 = getXValue(2);
			x3 = getXValue(3);
			//Вывод информации о полученных значениях.
			printDash();
			std::cout << "Из отрезка [-0.72;-0.7] были выбраны слеующие значения:" << std::endl;
			std::cout << "Первое значение x: " << x1 << std::endl;
			std::cout << "Второе значение x: " << x2 << std::endl;
			std::cout << "Третье значение x: " << x3 << std::endl;
			
			//Вывод таблицы для интерполирования.
			std::cout << std::endl << "Интерполирование: I и II интерполяционная формула Ньютна, интерполяционная формула Лагранжа. "<< std::endl << std::endl;
			printTableInterpolation();
			interpolation_formulas(x1, x2, x3);

			std::cout << std::endl;

			//Вывод таблицы для численного дифференцирования.
			std::cout << std::endl << "Численное дифференцирование, основанное на I и II интерполяционной формуле Ньютона." << std::endl << std::endl;
			printTableNumericalDefferentiation();
			numerical_differentiation_formulas(x1, x2, x3);
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