#include <iostream>
#include <vector>
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
	std::cout << "Заданный двойной интеграл:" << std::endl;
	std::cout << "\n\tДвойной интеграл по области D от функции f(x,y) = e^x,\n\tгде D = {(x,y): y=1; y=2; x=0; y=2x-1 }.\n" << std::endl;
	std::cout << "Точное решение интеграла:\n\t2*(e^(3/2) - e) - (2 - 1) = 2*(e^(3/2) - e) - 1 ~ " << std::setprecision(10) <<
		get_exact_value(B) - get_exact_value(b) << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки таблицы.
void printTable()
{
	std::cout << std::string(86, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "2n" <<
		"|" << std::setw(10) << "2m" <<
		"|" << std::setw(15) << "Iточн." <<
		"|" << std::setw(15) << "Iкуб.ф.с." <<
		"|" << std::setw(25) << "     |Iточн. - Iкуб.ф.с.|     " <<
		"|" << std::endl;
	std::cout << std::string(86, '_') << std::endl;
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
//Получение значения n и m соответственно от пользователя.
int get_n_m_values(const char& n_or_m, const int& i)
{
	while (true)
	{
		if (n_or_m == 'n')
			std::cout << "Введите значение 2n_" << i + 1 << ": ";
		else
			std::cout << "Введите значение 2m_" << i + 1 << ": ";
		std::string str_n_or_m_value{};
		std::getline(std::cin, str_n_or_m_value);
		if (checkStrIsNumeric(str_n_or_m_value))
		{
			long double n_or_m_value{ convertStrToNumber(str_n_or_m_value)};
			if (n_or_m_value <= 0 || static_cast<int>(n_or_m_value) != n_or_m_value || static_cast<int>(n_or_m_value) % 2 != 0)
			{
				if (n_or_m == 'n')
					std::cout << "Значение 2n должно быть > 0 и являться целым четным числом! Повторите ввод." << std::endl;
				else
					std::cout << "Значение 2m должно быть > 0 и являться целым четным числом! Повторите ввод." << std::endl;
			}
			else
				return static_cast<int>(n_or_m_value / 2);
		}
		else
			std::cout << "Вы ввели не число! Повторите ввод." << std::endl;
	}
}
//Вычисление шага h.
long double get_step_h(const int& n)
{
	return ((A - a) / (2 * n));
}
//Вычисление шага k.
long double get_step_k(const int& m)
{
	return ((B - b) / (2 * m));
}
//Вычисление значения f(x,y).
long double get_f(const long double& x, const long double& y)
{
	if (x >= 0 && y >= (2 * x - 1) && y >= 1 && y <= 2)
		return exp(x);
	else
		return 0;
}
//Вычисление xi.
long double get_xi(const int& i, const int& n)
{
	return (x_0 + i * get_step_h(n));
}
//Вычисление yj.
long double get_yj(const int& j, const int& m)
{
	return (y_0 + j * get_step_k(m));
}
//Построение матрицы lambda.
std::vector<std::vector<int>> get_lambda_matrix(const std::size_t& n, const std::size_t& m)
{
	std::vector<std::vector<int>> matrix(2 * m + 1, std::vector<int>(2 * n + 1, 0));

	//Угловые элементы матрицы.
	matrix[0][0] = 1;
	matrix[2 * m][2 * n] = 1;
	matrix[2 * m][0] = 1;
	matrix[0][2 * n] = 1;

	//Элементы первого и последнего столбца матрицы.
	for (int j{ 1 }; j < 2 * m; j++)
	{
		if (((j - 1) % 2) == 1)
		{
			matrix[j][0] = 2;
			matrix[j][2 * n] = 2;
		}
		else
		{
			matrix[j][0] = 4;
			matrix[j][2 * n] = 4;
		}
	}

	//Элементы первой и последней строки матрицы.
	for (int i{ 1 }; i < 2 * n; ++i)
	{
		if (((i - 1) % 2) == 1)
		{
			matrix[0][i] = 2;
			matrix[2 * m][i] = 2;
		}
		else
		{
			matrix[0][i] = 4;
			matrix[2 * m][i] = 4;
		}
	}

	//Все остальные элементы.
	for (int i{ 1 }; i < 2 * m; ++i)
	{
		for (int j{ 1 }; j < 2 * n; ++j)
		{
			matrix[i][j] = matrix[0][j] * matrix[i][0];
		}
	}

	return matrix;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Точное решение двойного интеграла.
long double get_exact_value(const long double& y)
{
	return 2 * exp((y + 1) / 2) - y;
}
//Вычисление решения двойного интеграла по куботурной формуле Симпсона.
void simpsonFormula(const int& n, const int& m)
{
	std::vector<std::vector<int>> lambdaMatrix{ get_lambda_matrix(n, m) };
	long double result{};
	long double h{ get_step_h(n) }, k{ get_step_k(m) };

	for (int j{}; j <= 2 * m; j++)
	{
		for (int i{}; i <= 2 * n; i++)
		{
			long double xi{ get_xi(i, n) };
			long double yj{ get_yj(j, m) };
			result += lambdaMatrix[j][i] * get_f(xi,yj);
		}
	}
	result *= h * k / 9;

	long double I{ get_exact_value(B) - get_exact_value(b) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(10) << std::setprecision(10) << 2*n <<
		"|" << std::setw(10) << std::setprecision(10) << 2*m <<
		"|" << std::setw(15) << std::setprecision(10) << I <<
		"|" << std::setw(15) << std::setprecision(10) << result <<
		"|" << std::setw(30) << std::setprecision(11) << abs(I - result) <<
		"|" << std::endl;
	std::cout << std::string(86, '_') << std::endl;
}
