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
	std::cout << "Вариант индивидуального задания: 9." << std::endl << std::endl;
	std::cout << "Краевая задача:" << std::endl;
	std::cout << "  Дифференциальное уравнение:\t y\" + (x-4)y' - 3.1y = 2x" << std::endl;
	std::cout << "  Краевые условия:\t\t -y'(0) + y(0) = 1, y(1) = 1.7" << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки исходной таблицы.	
void printTable()
{
	std::cout << std::string(116, '_') << std::endl;
	std::cout << "|" << std::setw(2) << "" <<
		"|" << std::setw(15) << "xi       " <<
		"|" << std::setw(15) << "yi       " <<
		"|" << std::setw(15) << "mi       " <<
		"|" << std::setw(15) << "ri       " <<
		"|" << std::setw(15) << "cpi       " <<
		"|" << std::setw(15) << "ci       " <<
		"|" << std::setw(15) << "di       " <<
		"|" << std::endl;
	std::cout << std::string(116, '_') << std::endl;
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

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИ*/
//Получение массива mass_x со значениями xi.
double* get_mass_x(const int& n, const double& h)
{
	double* mass_x = new double[n + 1] {};
	mass_x[0] = a;
	for (int i{ 1 }; i <= n; i++)
		mass_x[i] = mass_x[i - 1] + h;
	return mass_x;
}
//Получение массива mass_p со значениями pi.
double* get_mass_p(const double* const mass_x, const int& n, const double& h)
{
	double* mass_p = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_p[i] = mass_x[i] - 4;
	return mass_p;
}
//Получение массива mass_q со значениями qi.
double* get_mass_q(const double* const mass_x, const int& n, const double& h)
{
	double* mass_q = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_q[i] = -3.1;
	return mass_q;
}
//Получение массива mass_f со значениями fi.
double* get_mass_f(const double* const mass_x, const int& n, const double& h)
{
	double* mass_f = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_f[i] = 2 * mass_x[i];
	return mass_f;
}
//Получение массива mass_m со значениями mi.
double* get_mass_m(const double* const mass_q, const double* const mass_p, const int& n, const double& h)
{
	double* mass_m = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_m[i] = (2 * pow(h, 2) * mass_q[i] - 4) / (2 + h * mass_p[i]);
	return mass_m;
}
//Получение массива mass_ri со значениями ri.
double* get_mass_r(const double* const mass_p, const int& n, const double& h)
{
	double* mass_r = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_r[i] = (2 - h * mass_p[i]) / (2 + h * mass_p[i]);
	return mass_r;
}
//Получение массива mass_cp со значениями cpi.
double* get_mass_cp(const double* const mass_p, const double* const mass_f, const int& n, const double& h)
{
	double* mass_cp = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_cp[i] = (2 * pow(h, 2)) / (2 + h * mass_p[i]) * mass_f[i];
	return mass_cp;
}
//Получение массива mass_c со значениями ci.
double* get_mass_c(const double* const mass_m, const double* const mass_r, const int& n, const double& h)
{
	double* mass_c = new double[n + 1] {};
	mass_c[0] = alpha_0 / (alpha_1 * h - alpha_0);
	for (int i{ 1 }; i < n; i++)
		mass_c[i] = 1 / (mass_m[i] - mass_r[i] * mass_c[i - 1]);
	return mass_c;
}
//Получение массива mass_d со значениями di.
double* get_mass_d(const double* const mass_cp, const double* const mass_r, const double* const mass_c, const int& n, const double& h)
{
	double* mass_d = new double[n + 1] {};
	mass_d[0] = A * h / alpha_0;
	for (int i{ 1 }; i < n; i++)
		mass_d[i] = mass_cp[i] - mass_r[i] * mass_c[i - 1] * mass_d[i - 1];
	return mass_d;
}
//Получение массива mass_y со значениями yi.
double* get_mass_y(const double* const mass_c, const double* const mass_d, const int& n, const double& h)
{
	double* mass_y = new double[n + 1] {};
	mass_y[n] = (B * h + beta_0 * mass_c[n - 1] * mass_d[n - 1]) / (beta_0 * (1 + mass_c[n - 1]) + beta_1 * h);
	for (int i{ n - 1 }; i >= 0; i--)
		mass_y[i] = mass_c[i] * (mass_d[i] - mass_y[i + 1]);
	return mass_y;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Метод прогонки.
void sweep_method(const int& n)
{
	//Вычисление шага h.
	double h{ static_cast<double>((b - a)) / n };

	/*ПРЯМОЙ ХОД МЕТОДА ПРОГОНКИ*/
	//Формирование массива mass_x.
	double* mass_x = get_mass_x(n, h);
	//Получение массивов коэффициентов pi, qi, fi, mi, ri, cpi.
	double* mass_p = get_mass_p(mass_x, n, h);
	double* mass_q = get_mass_q(mass_x, n, h);
	double* mass_f = get_mass_f(mass_x, n, h);
	double* mass_m = get_mass_m(mass_q, mass_p, n, h);
	double* mass_r = get_mass_r(mass_p, n, h);
	double* mass_cp = get_mass_cp(mass_p, mass_f, n, h);
	//Получение массивов коэффициентов ci, di.
	double* mass_c = get_mass_c(mass_m, mass_r, n, h);
	double* mass_d = get_mass_d(mass_cp, mass_r, mass_c, n, h);
	
	/*ОБРАТНЫЙ ХОД МЕТОДА ПРОГОНКИ*/
	//Формирование массива mass_y.
	double* mass_y = get_mass_y(mass_c, mass_d, n, h);
	//Вычисление y0 по формуле.
	double y0 = (A * h - alpha_0 * mass_y[1]) / (alpha_1 * h - alpha_0);

	/*ВЫВОД РЕЗУЛЬТАТОВ*/
	for (int i{}; i <= n; i++)
	{
		std::cout << "|" << std::setw(2) << std::left << i <<
			"|" << std::setw(5) << "" << std::left << std::setw(5) << mass_x[i] << std::setw(5) << "" << std::right <<
			"|" << std::setw(15) << std::setprecision(10) << mass_y[i];
		if (i == 0 || i == n)
			std::cout << "|" << std::setw(15) << std::setprecision(10) << "" <<
			"|" << std::setw(15) << "" <<
			"|" << std::setw(15) << "";
		else
			std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_m[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_r[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_cp[i];
		if (i == n)
			std::cout << "|" << std::setw(15) << std::setprecision(10) << "" <<
			"|" << std::setw(15) << std::setprecision(10) << "";
		else
			std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_c[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_d[i];
		std::cout << "|" << std::endl;
		std::cout << std::string(116, '_') << std::endl;
	}
	//Сравнение y0 (по формуле) и yi[0] (по обратному ходу метода прогонки).
	std::cout << std::endl << "Сравнение значений y0 (полученное по формуле из первого краевого условия) и yi[0] (полученное по обратному ходу метода прогонки):" << std::endl;
	std::cout << "y0 = " << std::setprecision(10) << y0 << "\t" << "yi[0] = " << std::setprecision(10) << mass_y[0] << "\t" << "|y0 - yi[0]| = " << std::fixed << std::setprecision(10) << abs(y0 - mass_y[0]) << std::endl << std::endl;
	std::cout << std::defaultfloat;

	//Освобождение выделенной динамической памяти.
	delete[] mass_x;
	delete[] mass_p;
	delete[] mass_q;
	delete[] mass_f;
	delete[] mass_m;
	delete[] mass_r;
	delete[] mass_cp;
	delete[] mass_c;
	delete[] mass_d;
	delete[] mass_y;
}