#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"
#include "math.h"

/*ФУНКЦИИ ДЛЯ ПРОВЕРКИ ПОЛЗОВАТЕЛЬСКОГО ВВОДА*/
//Проверка введённой пользователем строки на возможность преобразования в число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if (!separator && i != 0 && (i != tempStr.length() - 1) && (tempStr[i] == '.' || tempStr[i] == ',' || tempStr[i] == '/'))
		{
			separator = true;
			continue;
		}
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразование введённой пользователем строки в число.
long double convertStrToNumber(std::string convertStr)
{
	long double number{}, number_for_fraction{};
	bool negative_number{ false }, fraction{ false };
	int separator_index{ -1 }, k{};
	for (int i{}; i < convertStr.length(); i++)
	{
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
		}
	}
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && convertStr[i] == '-')
		{
			negative_number = true;
			continue;
		}
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
			continue;
		if (separator_index == -1)
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_for_fraction) : static_cast<long double>(number / number_for_fraction);
}

/*ФУНКЦИИ ДЛЯ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод информации об авторе, варианте, задании.
void printTask()
{
	std::cout << std::setw(210) << "Горшков Алексей Олегович," << std::endl << std::setw(209) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 9." << std::endl << std::endl;
	std::cout << "Параметры:" << std::endl;
	std::cout << "\tgamma\t=    " << gamma << std::endl;
	std::cout << "\tm\t=     " << m << std::endl;
	std::cout << "\talpha\t=    " << alpha << std::endl;
	std::cout << "\tbeta\t=     " << beta << std::endl;
	std::cout << "\tM\t=    " << M << std::endl;
	std::cout << "\tN\t=    " << N << std::endl << std::endl;
	std::cout << "Начальные условия:\n";
	std::cout << "  _\n | u(x,0) = -1 + cosx\n<\n |_u'_t(x,0) = -e^x + 0.5 * cosx\n" << std::endl;
	std::cout << "Граничные условия:\n";
	std::cout << "  _\n | u(0,t) = -t + sin(0.5t)\n<\n |_u(l,t) = e^(-0.7t) - 0.7\n" << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Запустить программу (выданное требование)." << std::endl <<
		"2) Выйти из программы." << std::endl;
}
//Запрос дейтсвий у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода! Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 2). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Получение значений a от пользователя.
//long double getAvalue()
//{
//	std::cout << "Введите значение a: ";
//	std::string A_value{};
//	while (true)
//	{
//		std::getline(std::cin, A_value);
//		if (checkStrIsNumeric(A_value))
//		{
//			long double numeric_A_value{ convertStrToNumber(A_value) };
//			if (numeric_A_value > 0)
//				return numeric_A_value;
//			else
//				std::cout << "a должно быть положительным числом. Повторите ввод: ";
//		}
//		else
//			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
//	}
//}

//Вывод таблицы.
void printTable(const double* const& x, const double* const& t, const double* const& u_virtual, const double* const* const& u)
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "    t     " << "|";
	for (int i{}; i < n + 1; i++)
	{
		std::cout << std::setw(5) << std::right << "x=" << std::fixed << std::setprecision(2) << std::right << x[i] << "  |";
	}
	std::cout << std::endl;
	std::cout << std::string(144, '_') << std::endl;

	std::cout << "|" << "Вирт.слой:" << "|";
	for (int i{}; i < n + 1; i++) 
	{
		if (i == 0 || i == n) 
		{
			std::cout << std::setw(11) << "" << "|";
		}
		else 
		{
			if (u_virtual[i] < 0)
				std::cout << std::setw(2) << "";
			else
				std::cout << std::setw(3) << "";
			std::cout << std::setw(6) << std::setprecision(4) << u_virtual[i] << std::setw(2) << "" << "|";

		}
	}
	std::cout << std::endl;
	std::cout << std::string(144, '_') << std::endl;

	for (int j{}; j < n + 1; j++)
	{
		std::cout << "|" << std::setw(3) << " t=" << std::setw(7) << std::left << std::setprecision(4) << t[j] << "|";
		for (int i{}; i < n + 1; i++)
		{
			if (u[i][j] < 0)
				std::cout << std::setw(2) << "";
			else
				std::cout << std::setw(3) << "";
			std::cout << std::setw(6) << std::setprecision(4) << u[i][j] << std::setw(2) << "" << "|";
		}
		std::cout << std::endl;
		std::cout << std::string(144, '_') << std::endl;
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
void grid_method(const double& a) {
	//Вычисление шагов h по оси x и k по оси t.
	double h{ l / n };
	double k{ h / a };

	//Массив со значениями xi.
	double* x = new double[n + 1] {};
	//Массив со значениями tj.
	double* t = new double[n + 1] {};
	//Массив со значениями u(xi,-1) на "виртуальном" слое.
	double* u_virtual = new double[n + 1] {};
	//Массив со значениями u't_i0=u't(xi,0).
	double* u_t = new double[n + 1] {};
	//Двумерный массив со значениями uij=u(xi,tj).
	double** u = new double* [n + 1] {};
	for (int iter{}; iter < n + 1; iter++) {
		u[iter] = new double[n + 1] {};
	}

	//Заполнение массива со значениями xi.
	for (int i{}; i < n + 1; i++) {
		x[i] = i * h;
	}
	//Заполнения массива со значениями tj.
	for (int j{}; j < n + 1; j++) {
		t[j] = j * k;
	}
	//Заполнение двумерного массива со значениями uij=u(xi,tj) и массива со значениями u't_i0=u't(xi,0).
	/*По начальным условиям*/
	for (int i{}; i < n + 1; i++) {
		u[i][0] = -1 + cos(x[i]); //f_i
	}
	for (int i{}; i < n + 1; i++) {
		u_t[i] = -exp(x[i]) + 0.5 * cos(x[i]); //F_i
	}
	/*По граничным условиям*/
	for (int j{1}; j < n + 1; j++)
	{
		u[0][j] = -t[j] + sin(0.5 * t[j]); //phi_j
		u[n][j] = exp(-0.7 * t[j]) - 0.7; //psi_j
	}

	//Заполнение массива со значениями u(xi,-1) на "виртуальном" слое.
	for (int i{ 1 }; i < n; i++){
		u_virtual[i] = u[i][0] - k * u_t[i];
	}

	/*По конечно-разностному соотношению*/
	for (int j{}; j < n; j++) {
		for (int i{ 1 }; i < n; i++)
		{
			if (j - 1 == -1) {
				u[i][j + 1] = u[i + 1][j] + u[i - 1][j] - u_virtual[i];
			}
			else {
				u[i][j + 1] = u[i + 1][j] + u[i - 1][j] - u[i][j - 1];
			}
		}
	}

	//Вывод таблицы.
	printTable(x, t, u_virtual, u);

	//Освобождение выделенной динамической памяти.
	delete[] x;
	delete[] t;
	delete[] u_virtual;
	delete[] u_t;
	for (int i{}; i < n + 1; i++)
		delete[] u[i];
	delete[] u;
}