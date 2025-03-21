#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

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
	std::cout << "Вариант индивидуального задания: 2." << std::endl;
	std::cout << "Нелинейное уравнение:" << std::endl;
	std::cout << "\tsin(2x) - ln(x) = 0." << std::endl;
	std::cout << "Отрезок [a;b] = [pi/3;(23pi)/48] = [" << std::setprecision(15) << a << "; " << std::setprecision(15) << b << "]." << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки исходной таблицы для МПИ, МН и ММН.
void printTable()
{
	std::cout << std::string(80, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "k + 1" <<
		"|" << std::setw(12) << "x_k" <<
		"|" << std::setw(13) << "x_(k+1)" <<
		"|" << std::setw(20) << "   |x_(k+1) - x_k|  " <<
		"|" << std::setw(20) << "   |f(x_(k+1))|   " 
		"|" << std::endl;
	std::cout << std::string(80, '_') << std::endl;
}

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Запустить программу по умолчанию (выданное требование)." << std::endl <<
		"2) Задать в программе своё значение точности эпсилон и дельта, а затем выполнить МПИ, МН и ММН для заданного нелинейного уравнения." << std::endl <<
		"3) Выйти из программы." << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3")
			return choice[0];
		else
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 1 до 3). Повторите ввод:" << std::endl;
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Получение значения точности эпсилон/дельта от пользователя.
long double getEpsilonDelta(const int&epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "Введите значение эпсилон: ";
		break;
	case 2:
		std::cout << "Введите значение дельта: ";
		break;
	default:;
	}
	std::string f_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, f_epsilon_delta);
		if (checkStrIsNumeric(f_epsilon_delta))
		{
			long double f_numeric_epsilon_delta{ convertStrToNumber(f_epsilon_delta) };
			if (f_numeric_epsilon_delta > 0)
				return f_numeric_epsilon_delta;
			else
			{
				switch (epsilon_delta)
				{
				case 1:
					std::cout << "Ошибка ввода! Значение эпсилон должно быть больше 0 (по условию). Повторите ввод: ";
					break;
				case 2:
					std::cout << "Ошибка ввода! Значение дельта должно быть больше 0 (по условию). Повторите ввод: ";
				default:;
				}
			}
		}
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Выбор нового значения точности эпсилон/дельта от пользователя или сохранение старого.
void reselectEpsilonDeltaValue(long double& f_epsilon_delta, const int& epsilon_delta)
{
	switch (epsilon_delta)
	{
	case 1:
		std::cout << "Вы желаете оставить старое значение точности эпсилон или выбрать новое?(\"enter\"/введите новое)" << std::endl;
		break;
	case 2:
		std::cout << "Вы желаете оставить старое значение точности дельта или выбрать новое?(\"enter\"/введите новое)" << std::endl;
		break;
	default:;
	}
	std::string new_or_old_epsilon_delta{};
	while (true)
	{
		std::getline(std::cin, new_or_old_epsilon_delta);
		if (new_or_old_epsilon_delta.empty())
			break;
		else if (checkStrIsNumeric(new_or_old_epsilon_delta))
		{
			f_epsilon_delta = convertStrToNumber(new_or_old_epsilon_delta);
			break;
		}
		else
			std::cout << "Ошибка ввода! Вы должны нажать Enter или задать новое значение. Повторите ввод: ";
	}
}
//Получение значения начального приближения x_0 из заданного отрезка [pi/3; (23pi)/48].
long double getValueInitApprox(const int& method)
{
	std::string str_init_approx_x_0{};
	while (true)
	{
		std::cout << "x_0 = ";
		std::getline(std::cin, str_init_approx_x_0);
		if (checkStrIsNumeric(str_init_approx_x_0))
		{
			long double value_init_approx_x_0{ convertStrToNumber(str_init_approx_x_0) };
			if (value_init_approx_x_0 >= a && value_init_approx_x_0 <= b)
				return value_init_approx_x_0;
			else
				std::cout << "Ошибка ввода! Вы должны ввести значение начального приближения x_0 из отрезка [pi/3;(23pi)/48] = " <<
				"[" << std::setprecision(15) << a << "; " << std::setprecision(15) << b << "]. Повторите ввод:" << std::endl;
		}
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Задание начального приближения x_0 с проверкой на достаточное условие сходимости соответствующего метода.
bool getInitialApproximation(long double& f_init_approx_x_0, bool& f_flag_init_approx, const int& method)
{
	std::cout << "Задайте начальное приближение x_0:" << std::endl;
	if (!f_flag_init_approx)
	{
		f_init_approx_x_0 = getValueInitApprox(method);
		f_flag_init_approx = true;
	}
	switch (method)
	{
	case 1:
		return true;
		break;
	case 2:
	{
		long double expression_value{ (sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) };
		if (expression_value > 0)
			return true;
		else
			return false;
		break;
	}
	default:;
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Метод простых итераций (МПИ).
void simpleIterationMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//Задание начального приближения x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 1) };
	printDash();
	//Проверка выполнения достаточного условия сходимости не требуется, т.к. всегда выполняется на заданном отрезке.
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//Инициализация переменных для хранения k-го и (k+1)-го приближений, постоянной C.
	long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
	unsigned int k{};
	//Вывод шапки таблицы МПИ.
	printTable();
	//Итерационный процесс.
	while (true)
	{
		//Вычисление приближения на (k+1)-м шаге итерации.
		x_k_plus_1 = x_k + C * (sin(2 * x_k) - std::log(x_k));
		//Заполнение таблицы.
		std::cout << "|" << std::setw(10) << k + 1 <<
			"|" << std::setw(12) << std::setprecision(10) << x_k <<
			"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
			"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
			"|" << std::endl;
		std::cout << std::string(80, '_') << std::endl;
		//Проверка условия окончания итерационного процесса.
		if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
			break;
		//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
		k += 1;
		x_k = x_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение нелинейного уравнения по МПИ с указанной заданной точностью и начальным приближением: x = " << 
		std::setprecision(10) << x_k_plus_1 << "." << std::endl;
}
//Метод Ньютона (МН).
void NewtonsMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//Задание начального приближения x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 2) };
	printDash();
	//Вывод информации для МН.
	std::cout << "Метод Ньютона (МН) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//Проверка выполнения достаточного условия сходимости.
	if (correct_method)
	{
		//Инициализация переменных для хранения k-го и (k+1)-го приближений.
		long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
		unsigned int k{};
		//Вывод шапки таблицы МН.
		printTable();
		//Итерационный процесс.
		while (true)
		{
			//Вычисление приближения на (k+1)-м шаге итерации.
			x_k_plus_1 = x_k - (sin(2 * x_k) - std::log(x_k)) / (2 * cos(2 * x_k) - 1 / x_k);
			//Заполнение таблицы.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(12) << std::setprecision(10) << x_k <<
				"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(80, '_') << std::endl;
			//Проверка условия окончания итерационного процесса.
			if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
				break;
			//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "Таким образом, решение нелинейного уравнения по МН с указанной заданной точностью и начальным приближением: x = " << 
			std::setprecision(10) << x_k_plus_1 << "." << std::endl;
	}
	else
	{
		std::cout << "Не выполняется достаточное условие сходимости МН для заданного нелинейного уравнения." << std::endl << std::endl;
		std::cout << "Значение начального приближения x_0 должно быть выбрано из отрезка [a;b] = [pi/3; (23pi)/48] = [" << 
			std::setprecision(15) << a << ", " << std::setprecision(15) << b << "] так, чтобы " << "выполнялось следующее условие: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, т.е. (sin(2x_0) - ln(x_0)) * (-4sin(2x_0) + 1/(x_0)^2) > 0." << std::endl;
		std::cout << "В данном случае значение выражения равно: " << std::endl << std::setprecision(15) <<
			(sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) << " < 0." << std::endl;
	}
}
//Модифицированный метод Ньютона (ММН).
void modifiedNewtonsMethod(long double& f_epsilon, long double& f_delta, long double& f_init_approx_x_0, bool& f_flag_init_approx)
{
	//Задание начального приближения x_0.
	bool correct_method{ getInitialApproximation(f_init_approx_x_0, f_flag_init_approx, 2) };
	printDash();
	//Вывод информации для МН.
	std::cout << "Модифицированный метод Ньютона (ММН) для заданного нелинейного уравнения." << std::endl;
	std::cout << "Начальное приближение:\t\tx_0 = " << std::setprecision(10) << f_init_approx_x_0 << "." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << std::setprecision(10) << f_epsilon << "." << std::endl;
	std::cout << "Заданная точность дельта:\t" << std::setprecision(10) << f_delta << "." << std::endl;
	//Проверка выполнения достаточного условия сходимости.
	if (correct_method)
	{
		//Инициализация переменных для хранения k-го и (k+1)-го приближений.
		long double x_k{ f_init_approx_x_0 }, x_k_plus_1{};
		unsigned int k{};
		//Вывод шапки таблицы ММН.
		printTable();
		//Итерационный процесс.
		while (true)
		{
			//Вычисление приближения на (k+1)-м шаге итерации.
			x_k_plus_1 = x_k - (sin(2 * x_k) - std::log(x_k)) / (2 * cos(2 * f_init_approx_x_0) - 1 / f_init_approx_x_0);
			//Заполнение таблицы.
			std::cout << "|" << std::setw(10) << k + 1 <<
				"|" << std::setw(12) << std::setprecision(10) << x_k <<
				"|" << std::setw(13) << std::setprecision(10) << x_k_plus_1 <<
				"|" << std::setw(20) << std::setprecision(10) << abs(x_k_plus_1 - x_k) <<
				"|" << std::setw(19) << std::setprecision(10) << sin(2 * x_k_plus_1) - std::log(x_k_plus_1) <<
				"|" << std::endl;
			std::cout << std::string(80, '_') << std::endl;
			//Проверка условия окончания итерационного процесса.
			if (abs(x_k_plus_1 - x_k) <= f_epsilon && (sin(2 * x_k_plus_1) - std::log(x_k_plus_1)) <= f_delta)
				break;
			//Переход к следующей итерации в случае, когда условие выше не было удовлетворено.
			k += 1;
			x_k = x_k_plus_1;
		}
		std::cout << std::endl << "Таким образом, решение нелинейного уравнения по ММН с указанной заданной точностью и начальным приближением: x = " << x_k_plus_1 <<
			"." << std::endl;
	}
	else
	{
		std::cout << "Не выполняется достаточное условие сходимости ММН для заданного нелинейного уравнения." << std::endl << std::endl;
		std::cout << "Значение начального приближения x_0 должно быть выбрано из отрезка [a;b] = [pi/3; (23pi)/48] = [" << 
			std::setprecision(15) << a << ", " << std::setprecision(15) << b << "] так, чтобы " << "выполнялось следующее условие: " << std::endl;
		std::cout << "\tf(x_0)*f\"(x_0) > 0, т.е. (sin(2x_0) - ln(x_0)) * (-4sin(2x_0) + 1/(x_0)^2) > 0." << std::endl;
		std::cout << "В данном случае значение выражения равно: " << std::endl << std::setprecision(15) <<
			(sin(2 * f_init_approx_x_0) - std::log(f_init_approx_x_0)) * (-4 * sin(2 * f_init_approx_x_0) + 1 / pow(f_init_approx_x_0, 2)) << " < 0." << std::endl;
	}
}