#include <iostream>
#include <string>
#include <iomanip>
#include "myfuncs.h"

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
double convertStrToNumber(std::string convertStr)
{
	double number{}, number_for_fraction{};
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
			number += static_cast<double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}	
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<double>(-number) : static_cast<double>(number);
	else
		return negative_number ? static_cast<double>(-number / number_for_fraction) : static_cast<double>(number / number_for_fraction);
}

/*ФУНКЦИИ ДЛЯ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод информации об авторе, варианте, задании.
void printTask()
{
	std::cout << std::setw(210) << "Горшков Алексей Олегович," << std::endl << std::setw(209) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 2." << std::endl;
	std::cout << "Система линейных алгебраических уравнений (СЛАУ):" << std::endl;
	std::cout << " _\n|  3x - y + z = 3;\n|\n<  2x - 6y - 3z = -7;\n|\n|_ x + y - 3x = -1." << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки исходной таблицы для МПИ и МЗ.
void printSIMandSMTable()
{
	std::cout << std::string(168, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k + 1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(12) << "y_k"
		"|" << std::setw(12) << "z_k"
		"|" << std::setw(15) << "x_(k+1)"
		"|" << std::setw(15) << "y_(k+1)"
		"|" << std::setw(15) << "z_(k+1)"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(20) << "   |y_(k+1) - y_k|   "
		"|" << std::setw(20) << "   |z_(k+1) - z_k|   "
		"|" << std::setw(14) << "Сумма|" << std::endl;
	std::cout << std::string(168, '_') << std::endl;
}
//Вывод шапки исходной таблицы для МР.
void printRMTable()
{
	std::cout << std::string(108, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(12) << "y_k"
		"|" << std::setw(12) << "z_k"
		"|" << std::setw(15) << "R_x^(k)"
		"|" << std::setw(15) << "R_y^(k)"
		"|" << std::setw(15) << "R_z^(k)"
		"|" << std::setw(20) << "   max|R^(k)|   |" << std::endl;
	std::cout << std::string(108, '_') << std::endl;
}

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1) Запустить программу по умолчанию (выданное требование)." << std::endl <<
		"2) Задать в программе своё значение точности эпсилон, а затем выполнить МПИ, МЗ и МР для заданного СЛАУ." << std::endl <<
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
//Получение значения точности эпсилон от пользователя.
double getEpsilon()
{
	std::cout << "Введите значение эпсилон: ";
	std::string f_epsilon{};
	while (true)
	{
		std::getline(std::cin, f_epsilon);
		if (checkStrIsNumeric(f_epsilon))
		{
			double f_numeric_epsilon{ convertStrToNumber(f_epsilon) };
			if (f_numeric_epsilon > 0)
				return f_numeric_epsilon;
			else
				std::cout << "Ошибка ввода! Значение эпсилон должно быть больше 0 (по условию). Повторите ввод: ";
		}
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Выбор нового значения точности эпсилон от пользователя или сохранение старого.
void reselectEpsilonValue(double& f_epsilon)
{
	std::cout << "Вы желаете оставить старое значение точности эпсилон или выбрать новое?(\"enter\"/введите новое)" << std::endl;
	std::string new_or_old_epsilon{};
	while (true)
	{
		std::getline(std::cin, new_or_old_epsilon);
		if (new_or_old_epsilon.empty())
			break;
		else if (checkStrIsNumeric(new_or_old_epsilon))
		{
			f_epsilon = convertStrToNumber(new_or_old_epsilon);
			break;
		}
		else
			std::cout << "Ошибка ввода! Вы должны нажать Enter или задать новое значение. Повторите ввод: ";
	}
}
//Получение одной из компонент начального приближения от пользователя.
double getComponentOfInitApprox()
{
	std::string componet_initApprox{};
	while (true)
	{
		std::getline(std::cin, componet_initApprox);
		if (checkStrIsNumeric(componet_initApprox))
			return convertStrToNumber(componet_initApprox);
		else
			std::cout << "Ошибка ввода! Вы ввели не число. Повторите ввод: ";
	}
}
//Задание начального приближения.
void getInitialApproximation(double f_init_approx_mas[], bool& f_flag_init_approx)
{
	std::cout << "Задайте начальное приближение:" << std::endl;
	if (!f_flag_init_approx)
	{
		std::cout << "x^(0) = ";
		f_init_approx_mas[0] = getComponentOfInitApprox();
		std::cout << "y^(0) = ";
		f_init_approx_mas[1] = getComponentOfInitApprox();
		std::cout << "z^(0) = ";
		f_init_approx_mas[2] = getComponentOfInitApprox();
		f_flag_init_approx = true;
	}
	else
	{
		std::cout << "Компонента начального приближения x^(0): " << f_init_approx_mas[0] << "." << std::endl;
		std::cout << "Компонента начального приближения y^(0): " << f_init_approx_mas[1] << "." << std::endl;
		std::cout << "Компонента начального приближения z^(0): " << f_init_approx_mas[2] << "." << std::endl;
	}
}
//Получение максимума из 3-х чисел.
double getMaxOfThreeNumbers(const double& number_1, const double& number_2, const double& number_3)
{
	double max_value{};
	if (number_1 > max_value) max_value = number_1;
	if (number_2 > max_value) max_value = number_2;
	if (number_3 > max_value) max_value = number_3;
	return max_value;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Метод простых итераций (МПИ).
void simpleIterationMethod(double& f_epsilon, double f_init_approx_mas[], bool& f_flag_init_approx)
{
	//Задание начального приближения.
	getInitialApproximation(f_init_approx_mas, f_flag_init_approx);
	printDash();
	//Вывод информации для МПИ.
	std::cout << "Метод простых итераций (МПИ) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(33) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\tW^(0) = " << "(" << f_init_approx_mas[0] << ", " << f_init_approx_mas[1] << ", " << f_init_approx_mas[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << f_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-го и (k+1)-го приближения.
	double x_k{ f_init_approx_mas[0] }, y_k{ f_init_approx_mas[1] }, z_k{ f_init_approx_mas[2] },
		x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//Вывод шапки таблицы МПИ.
	printSIMandSMTable();
	//Итерационный процесс.
	while (true)
	{
		//Вычисление приближения на (k+1)-м шаге итерации.
		x_k_plus_1 = 1 + 1.f / 3.f * y_k - 1.f / 3.f * z_k;
		y_k_plus_1 = 7.f / 6.f + 1.f / 3.f * x_k - 1.f / 2.f * z_k;
		z_k_plus_1 = 1.f / 3.f + 1.f / 3.f * x_k + 1.f / 3.f * y_k;
		//Заполнение таблицы.
		std::cout << "|" << std::setw(5) << k << 
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|"	<< std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(14) << y_k_plus_1 <<
			"|" << std::setw(14) << z_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
			"|" << std::setw(21) << abs(z_k_plus_1 - z_k) <<
			"|"	<< std::setw(13) << abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <<
			"|" << std::endl;
		std::cout << std::string(168, '_') << std::endl;
		//Проверка условия окончания итерационного процесса.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= f_epsilon)
			break;
		//Переход к следующей итерации в случае, когда условие выше не было удоволетворено.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МПИ с указанной заданной точностью и начальным приближением: (x,y,z) = " <<
		"(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//Метод Зейделя (МЗ).
void seidelMethod(double& f_epsilon, double f_init_approx_mas[], bool& f_flag_init_approx)
{
	//Задание начального приближения.
	getInitialApproximation(f_init_approx_mas, f_flag_init_approx);
	printDash();
	//Вывод информации для МЗ.
	std::cout << "Метод Зейделя (МЗ) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(33) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\tW^(0) = " << "(" << f_init_approx_mas[0] << ", " << f_init_approx_mas[1] << ", " << f_init_approx_mas[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << f_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-го и (k+1)-го приближения.
	double x_k{ f_init_approx_mas[0] }, y_k{ f_init_approx_mas[1] }, z_k{ f_init_approx_mas[2] },
		x_k_plus_1{}, y_k_plus_1{}, z_k_plus_1{};
	unsigned int k{ 1 };
	//Вывод шапки таблицы МЗ.
	printSIMandSMTable();
	//Итерационный процесс.
	while (true)
	{
		//Вычисление приближения на (k+1)-м шаге итерации.
		x_k_plus_1 = 1 + 1.f / 3.f * y_k - 1.f / 3.f * z_k;
		y_k_plus_1 = 7.f / 6.f + 1.f / 3.f * x_k_plus_1 - 1.f / 2.f * z_k;
		z_k_plus_1 = 1.f / 3.f + 1.f / 3.f * x_k_plus_1 + 1.f / 3.f * y_k_plus_1;
		//Заполнение таблицы.
		std::cout << "|" << std::setw(5) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|" << std::setw(14) << x_k_plus_1 <<
			"|" << std::setw(14) << y_k_plus_1 <<
			"|" << std::setw(14) << z_k_plus_1 <<
			"|" << std::setw(21) << abs(x_k_plus_1 - x_k) <<
			"|" << std::setw(21) << abs(y_k_plus_1 - y_k) <<
			"|" << std::setw(21) << abs(z_k_plus_1 - z_k) <<
			"|" << std::setw(13) << abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <<
			"|" << std::endl;
		std::cout << std::string(168, '_') << std::endl;
		//Проверка условия окончания итерационного процесса.
		if (abs(x_k_plus_1 - x_k) + abs(y_k_plus_1 - y_k) + abs(z_k_plus_1 - z_k) <= f_epsilon)
			break;
		//Переход к следующей итерации в случае, когда условие выше не было удоволетворено.
		k += 1;
		x_k = x_k_plus_1;
		y_k = y_k_plus_1;
		z_k = z_k_plus_1;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МЗ с указанной заданной точностью и начальным приближением: (x,y,z) = " <<
		"(" << x_k_plus_1 << ", " << y_k_plus_1 << ", " << z_k_plus_1 << ")." << std::endl;
}
//Метод релаксации (ослабления) (МР).
void relaxationMethod(double& f_epsilon, double f_init_approx_mas[], bool& f_flag_init_approx)
{
	//Задание начального приближения.
	getInitialApproximation(f_init_approx_mas, f_flag_init_approx);
	printDash();
	//Вывод информации для МР.
	std::cout << "Метод релаксации (ослабления) (МР) для заданной СЛАУ." << std::endl;
	std::cout << std::setw(33) << "_" << std::endl;
	std::cout << "Начальное приближение:\t\tW^(0) = " << "(" << f_init_approx_mas[0] << ", " << f_init_approx_mas[1] << ", " << f_init_approx_mas[2] << ")." << std::endl;
	std::cout << "Заданная точность эпсилон:\t" << f_epsilon << "." << std::endl;
	//Инициализация переменных для хранения k-го приближения и невязок МР на k-ой итерации, а также максимальной по модулю невязки.
	double x_k{ f_init_approx_mas[0] }, y_k{ f_init_approx_mas[1] }, z_k{ f_init_approx_mas[2] },
		R_x_k{}, R_y_k{}, R_z_k{};
	unsigned int k{};
	//Вывод шапки таблицы МР.
	printRMTable();
	//Итерационный процесс.
	while (true)
	{
		//Вычисление невязок на k-м шаге итерации.
		R_x_k = 1 - x_k + 1.f / 3.f * y_k - 1.f / 3.f * z_k;
		R_y_k = 7.f / 6.f + 1.f / 3.f * x_k - y_k - 1.f / 2.f * z_k;
		R_z_k = 1.f / 3.f + 1.f / 3.f * x_k + 1.f / 3.f * y_k - z_k;
		//Вычисление максимальной по модулю невязки из получившихся трёх.
		double max_abs_R_k{ getMaxOfThreeNumbers(abs(R_x_k), abs(R_y_k), abs(R_z_k)) };
		//Заполнение таблицы.
		std::cout << "|" << std::setw(6) << k <<
			"|" << std::setw(11) << x_k <<
			"|" << std::setw(11) << y_k <<
			"|" << std::setw(11) << z_k <<
			"|" << std::setw(14) << R_x_k <<
			"|" << std::setw(14) << R_y_k <<
			"|" << std::setw(14) << R_z_k <<
			"|" << std::setw(19) << max_abs_R_k <<
			"|" << std::endl;
		std::cout << std::string(108, '_') << std::endl;
		//Проверка условия окончания итерационного процесса.
		if ((abs(R_x_k) <= f_epsilon) && (abs(R_y_k) <= f_epsilon) && (abs(R_z_k) <= f_epsilon))
			break;
		//Переход к следующей итерации в случае, когда условие выше не было удоволетворено.
		k += 1;
		if (max_abs_R_k == abs(R_x_k))
			x_k += R_x_k;
		else if (max_abs_R_k == abs(R_y_k))
			y_k += R_y_k;
		else
			z_k += R_z_k;
	}
	std::cout << std::endl << "Таким образом, решение СЛАУ по МР с указанной заданной точностью и начальным приближением: (x,y,z) = " <<
		"(" << x_k << ", " << y_k << ", " << z_k << ")." << std::endl;
}