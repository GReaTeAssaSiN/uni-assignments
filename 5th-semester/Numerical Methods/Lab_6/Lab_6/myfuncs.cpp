#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

/*ФУНКЦИИ ДЛЯ ВЫВОДА ИНФОРМАЦИИ НА КОНСОЛЬ*/
//Вывод информации об авторе, варианте, задании.
void printTask()
{
	std::cout << std::setw(210) << "Горшков Алексей Олегович," << std::endl << std::setw(209) << "группа 4312" << std::endl;
	printDash();
	std::cout << "Вариант индивидуального задания: 2." << std::endl;
	std::cout << "Заданный определенный интеграл:" << std::endl;
	std::cout << "Интеграл от " << a << " до " << b << " от функции y(x) = 1/(1+e^x) по dx." << std::endl;
	std::cout << "Первообразная интеграла: F(x) = x - ln(1+e^x)." << std::endl;
	std::cout << "\t\t\t\t\t       b" << std::endl;
	std::cout << "Формула Ньютона-Лейбница и точное решение: F(x)| = F(b) - F(a) = F(1) - F(0) = (1 - ln(1+e^1)) - (0 - ln(1+e^0)) ~ " << 
		std::setprecision(10) << get_exact_value(b) - get_exact_value(a) << "." << std::endl;
	std::cout << "\t\t\t\t\t       a" << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки таблицы.
void printTable()
{
	std::cout << std::string(139, '_') << std::endl;
	std::cout << "|" << std::setw(10) << "n" <<
		"|" << std::setw(15) << "I" <<
		"|" << std::setw(15) << "Iтр." <<
		"|" << std::setw(20) << "|I - Iтр.|    " <<
		"|" << std::setw(15) << "Iкв.ф.с." <<
		"|" << std::setw(20) << "|I - Iкв.ф.с.|  " <<
		"|" << std::setw(15) << "Iкв.ф.г." <<
		"|" << std::setw(20) << "|I - Iкв.ф.г.|  " <<
		"|" << std::endl;
	std::cout << std::string(139, '_') << std::endl;
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

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Точное решение определенного интеграла.
long double get_exact_value(const long double& x)
{
	return (x - log(1 + exp(x)));
}
//Формула трапеций, квадратурная формула Симпсона, квадратурная формула Гаусса для n=4.
void formulas_for_n_4()
{
	//Общее.
	long double I{ get_exact_value(b) - get_exact_value(a) };
	//Общее для формулы трапеций и квадр. формула Симпсона.
	float h{ static_cast<float>((b - a)) / 4 };
	double y0{ 1 / (1 + exp(a)) }, y1{ 1 / (1 + exp(a + h)) }, y2{ 1 / (1 + exp(a + 2 * h)) }, y3{ 1 / (1 + exp(a + 3 * h)) }, y4{ 1 / (1 + exp(b)) };
	//ФОРМУЛА ТРАПЕЦИЙ. 
	double Itr{ h * ((y0 + y4) / 2 + y1 + y2 + y3) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(10) << "4" <<
		"|" << std::setw(15) << std::setprecision(10) << I <<
		"|" << std::setw(15) << std::setprecision(10) << Itr <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Itr);
	//КВАДРАТУРНАЯ ФОРМУЛА СИМПСОНА.
	double Ikvfs{ h / 3 * (y0 + y4 + 4 * (y1 + y3) + 2 * y2) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(15) << std::setprecision(10) << Ikvfs <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfs);
	//КВАДРАТУРНАЯ ФОРМУЛА ГАУССА.
	//Коэффициенты для квадратурной формулы Гаусса.
	const double t1{ -0.86113631 }, t2{ -0.33998104 }, t3{ 0.33998104 }, t4{ 0.86113631 };
	const double A1{ 0.34785484 }, A2{ 0.65214516 }, A3{ 0.65214516 }, A4{ 0.34785484 };
	//Вычисление.
	double Ikvfg{ 0.5 * ((A1 * 1 / (1 + exp(0.5 + 0.5 * t1))) + (A2 * 1 / (1 + exp(0.5 + 0.5 * t2))) + (A3 * 1 / (1 + exp(0.5 + 0.5 * t3))) + (A4 * 1 / (1 + exp(0.5 + 0.5 * t4)))) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(15) << std::setprecision(10) << Ikvfg <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfg) <<
		"|" << std::endl;
	std::cout << std::string(139, '_') << std::endl;
}
//Формула трапеций, квадратурная формула Симпсона, квадратурная формула Гаусса для n=8.
void formulas_for_n_8()
{
	//Общее.
	long double I{ get_exact_value(b) - get_exact_value(a) };
	//Общее для формулы трапеций и квадр. формула Симпсона.
	float h{ static_cast<float>((b - a)) / 8 };
	double y0{ 1 / (1 + exp(a)) }, y1{ 1 / (1 + exp(a + h)) }, y2{ 1 / (1 + exp(a + 2 * h)) }, y3{ 1 / (1 + exp(a + 3 * h)) }, y4{ 1 / (1 + exp(a + 4 * h)) },
		y5{ 1 / (1 + exp(a + 5 * h)) }, y6{ 1 / (1 + exp(a + 6 * h)) }, y7{ 1 / (1 + exp(a + 7 * h)) }, y8{ 1 / (1 + exp(b)) };
	//ФОРМУЛА ТРАПЕЦИЙ. 
	double Itr{ h * ((y0 + y8) / 2 + y1 + y2 + y3 + y4 + y5 + y6 + y7) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(10) << "8" <<
		"|" << std::setw(15) << std::setprecision(10) << I <<
		"|" << std::setw(15) << std::setprecision(10) << Itr <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Itr);
	//КВАДРАТУРНАЯ ФОРМУЛА СИМПСОНА.
	double Ikvfs{ h / 3 * (y0 + y8 + 4 * (y1 + y3 + y5 + y7) + 2 * (y2 + y4 + y6)) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(15) << std::setprecision(10) << Ikvfs <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfs);
	//КВАДРАТУРНАЯ ФОРМУЛА ГАУССА.
	//Коэффициенты для квадратурной формулы Гаусса.
	const double t1{ -0.96028986 }, t2{ -0.79666648 }, t3{ -0.52553242 }, t4{ -0.18343464 }, t5{ 0.18343464 }, t6{ 0.52553242 }, t7{ 0.79666648 }, t8{ 0.96028986 };
	const double A1{ 0.10122854 }, A2{ 0.22238104 }, A3{ 0.31370664 }, A4{ 0.36268378 }, A5{ 0.36268378 }, A6{ 0.31370664 }, A7{ 0.22238104 }, A8{ 0.10122854 };
	//Вычисление.
	double Ikvfg{ 0.5 * ((A1 * 1 / (1 + exp(0.5 + 0.5 * t1))) + (A2 * 1 / (1 + exp(0.5 + 0.5 * t2))) + (A3 * 1 / (1 + exp(0.5 + 0.5 * t3))) + (A4 * 1 / (1 + exp(0.5 + 0.5 * t4))) +
		+(A5 * 1 / (1 + exp(0.5 + 0.5 * t5))) + (A6 * 1 / (1 + exp(0.5 + 0.5 * t6))) + (A7 * 1 / (1 + exp(0.5 + 0.5 * t7))) + (A8 * 1 / (1 + exp(0.5 + 0.5 * t8)))) };
	//Заполнение таблицы.
	std::cout << "|" << std::setw(15) << std::setprecision(10) << Ikvfg <<
		"|" << std::setw(20) << std::setprecision(10) << abs(I - Ikvfg) <<
		"|" << std::endl;
	std::cout << std::string(139, '_') << std::endl;
}