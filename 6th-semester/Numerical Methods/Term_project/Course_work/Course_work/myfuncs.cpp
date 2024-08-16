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
	std::cout << "КУРСОВАЯ РАБОТА" << std::endl;
	std::cout << "Вариант индивидуальной темы: Тема 10. Приближенное решение задачи Коши для обыкновенного дифференциального уравнения методами производных высших порядков." << std::endl;
	std::cout << "Заданные обыкновенное дифференциальное уравнение первого порядка и начальное условие:" << std::endl;
	std::cout << "  _\n |\n | x^2 * y^2 * y' + x * y^3 = 1;\n<\n | y(1) = 2.\n |_" << std::endl << std::endl;
	std::cout << "Задаваемый отрезок, определенный методом Рунге-Кутта 4-го порядка точности: [1, 2]." << std::endl;
	std::cout << "Общее решение ДУ: y = { [ (3*x^2 + 2C) / 2 ] ^ (1/3) } / x, C принадлежит R." << std::endl;
	std::cout << "Частное решение ДУ (задача Коши): y = { [ 1.5 * x^2 + 6.5 ] ^ (1/3) } / x." << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//---Вывод исходной таблицы для метода производной высшего порядка (до второго)---//
void printTableFirstHeaderSecondDerivativeMethod()
{
	std::cout << std::string(172, '_') << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(25, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::endl;
	std::cout << "|" << std::setw(3) << "i " <<
		"|" << std::setw(15) << "xi      " <<
		"|" << std::setw(15) << "y*_i     " <<
		"|" << std::setw(15) << "y_i       " <<
		"|" << std::setw(15) << "y'_i     " <<
		"|" << std::setw(15) << "y\"_i     " <<
		"|" << std::setw(25) << "|y*_i - y_i|      " <<
		"|" << std::setw(15) << "(y_i)@1     " <<
		"|" << std::setw(15) << "(y'_i)@1    " <<
		"|" << std::setw(15) << "(y\"_i)@1    " <<
		"|" << std::setw(12) << "h      " <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(25, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::endl;
}
void printTableFirstStringSecondDerivativeMethod(const double& xi, const double& y_exactly, const double mass_y_i[], const double mass_first_approx[], const double& step)
{
	std::cout << "|" << std::setw(3) << "   " <<
		"|" << std::setw(15) << xi <<
		"|" << std::setw(15) << std::setprecision(10) << y_exactly <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[0] <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[1] <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[2] <<
		"|" << std::setw(25) << std::setprecision(10) << abs(y_exactly - mass_y_i[0]);

	if (mass_first_approx[0] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_first_approx[0];

	if (mass_first_approx[1] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_first_approx[1];

	if (mass_first_approx[2] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_first_approx[2];

	std::cout << "|" << std::setw(12) << step <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(25, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::endl;
}
void printTableSecondHeaderSecondDerivativeMethod(const int& iter)
{
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(20, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(20, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(20, ' ')
		<< "|" << std::string(7, ' ')
		<< "|" << std::endl;
	std::cout << "|" << std::setw(3) << iter <<
		"|" << std::setw(15) << "(y_i)@2    " <<
		"|" << std::setw(15) << "(y_i)@3    " <<
		"|" << std::setw(20) << "|(y_i)@2-(y_i)@3| " <<
		"|" << std::setw(15) << "(y'_i)@2   " <<
		"|" << std::setw(15) << "(y'_i)@3   " <<
		"|" << std::setw(20) << "|(y'_i)@2-(y'_i)@3| " <<
		"|" << std::setw(15) << "(y\"_i)@2   " <<
		"|" << std::setw(15) << "(y\"_i)@3   " <<
		"|" << std::setw(20) << "|(y\"_i)@2-(y\"_i)@3| " <<
		"|" << std::setw(7) << "correct" <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(7, '_')
		<< "|" << std::endl;
}
void printTableSecondStringSecondDerivativeMethod(const double mass_second_approx[], const double mass_third_approx[], const bool& correct)
{
	std::cout << "|" << std::setw(3) << "   ";
	if (mass_second_approx[0] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_second_approx[0];

	if (mass_third_approx[0] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_third_approx[0];

	if (abs(mass_second_approx[0] - mass_third_approx[0]) == 0)
		std::cout << "|" << std::setw(20) << "";
	else
		std::cout << "|" << std::setw(20) << std::setprecision(10) << abs(mass_second_approx[0] - mass_third_approx[0]);

	if (mass_second_approx[1] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_second_approx[1];

	if (mass_third_approx[1] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_third_approx[1];

	if (abs(mass_second_approx[1] - mass_third_approx[1]) == 0)
		std::cout << "|" << std::setw(20) << "";
	else
		std::cout << "|" << std::setw(20) << std::setprecision(10) << abs(mass_second_approx[1] - mass_third_approx[1]);

	if (mass_second_approx[2] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_second_approx[2];

	if (mass_third_approx[2] == 0)
		std::cout << "|" << std::setw(15) << "";
	else
		std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_third_approx[2];

	if (abs(mass_second_approx[2] - mass_third_approx[2]) == 0)
		std::cout << "|" << std::setw(20) << "";
	else
		std::cout << "|" << std::setw(20) << std::setprecision(10) << abs(mass_second_approx[2] - mass_third_approx[2]);

	std::cout << "|" << std::setw(7) << (correct ? "true" : "false") <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(20, '_')
		<< "|" << std::string(7, '_')
		<< "|" << std::endl;
}
//---Вывод исходной таблицы для метода производной высшего порядка (до третьего)---//
void printTableFirstHeaderThirdDerivativeMethod()
{
	std::cout << std::string(208, '_') << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::string(23, ' ')
		<< "|" << std::string(18, ' ')
		<< "|" << std::string(18, ' ')
		<< "|" << std::string(18, ' ')
		<< "|" << std::string(18, ' ')
		<< "|" << std::string(15, ' ')
		<< "|" << std::endl;
	std::cout << "|" << std::setw(3) << "i " <<
		"|" << std::setw(12) << "xi      " <<
		"|" << std::setw(12) << "y*_i     " <<
		"|" << std::setw(12) << "y_i       " <<
		"|" << std::setw(15) << "y'_i     " <<
		"|" << std::setw(15) << "y\"_i     " <<
		"|" << std::setw(15) << "y\"'_i      " <<
		"|" << std::setw(23) << "|y*_i - y_i|      " <<
		"|" << std::setw(18) << "(y_i)@1     " <<
		"|" << std::setw(18) << "(y'_i)@1    " <<
		"|" << std::setw(18) << "(y\"_i)@1    " <<
		"|" << std::setw(18) << "(y\"'_i)@1     " <<
		"|" << std::setw(15) << "h      " <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(23, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::endl;
}
void printTableFirstStringThirdDerivativeMethod(const double& xi, const double& y_exactly, const double mass_y_i[], const double mass_first_approx[], const double& step)
{
	std::cout << "|" << std::setw(3) << "   " <<
		"|" << std::setw(12) << xi <<
		"|" << std::setw(12) << std::setprecision(10) << y_exactly <<
		"|" << std::setw(12) << std::setprecision(10) << mass_y_i[0] <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[1] <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[2] <<
		"|" << std::setw(15) << std::setprecision(10) << mass_y_i[3] <<
		"|" << std::setw(23) << std::setprecision(10) << abs(y_exactly - mass_y_i[0]);

	if (mass_first_approx[0] == 0)
		std::cout << "|" << std::setw(18) << "";
	else
		std::cout << "|" << std::setw(18) << std::setprecision(8) << mass_first_approx[0];

	if (mass_first_approx[1] == 0)
		std::cout << "|" << std::setw(18) << "";
	else
		std::cout << "|" << std::setw(18) << std::setprecision(8) << mass_first_approx[1];

	if (mass_first_approx[2] == 0)
		std::cout << "|" << std::setw(18) << "";
	else
		std::cout << "|" << std::setw(18) << std::setprecision(8) << mass_first_approx[2];

	if (mass_first_approx[3] == 0)
		std::cout << "|" << std::setw(18) << "";
	else
		std::cout << "|" << std::setw(18) << std::setprecision(8) << mass_first_approx[3];

	std::cout << "|" << std::setw(15) << step <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::string(23, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(18, '_')
		<< "|" << std::string(15, '_')
		<< "|" << std::endl;
}
void printTableSecondHeaderThirdDerivativeMethod(const int& iter)
{
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(17, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(19, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(12, ' ')
		<< "|" << std::string(19, ' ')
		<< "|" << std::string(16, ' ')
		<< "|" << std::string(16, ' ')
		<< "|" << std::string(24, ' ')
		<< "|" << std::string(7, ' ')
		<< "|" << std::endl;
	std::cout << "|" << std::setw(3) << iter <<
		"|" << std::setw(12) << "(y_i)@2   " <<
		"|" << std::setw(12) << "(y_i)@3   " <<
		"|" << std::setw(17) << "|(y_i)@2-(y_i)@3|" <<
		"|" << std::setw(12) << "(y'_i)@2   " <<
		"|" << std::setw(12) << "(y'_i)@3   " <<
		"|" << std::setw(19) << "|(y'_i)@2-(y'_i)@3|" <<
		"|" << std::setw(12) << "(y\"_i)@2   " <<
		"|" << std::setw(12) << "(y\"_i)@3   " <<
		"|" << std::setw(19) << "|(y\"_i)@2-(y\"_i)@3|" <<
		"|" << std::setw(16) << "(y\"'_i)@2  " <<
		"|" << std::setw(16) << "(y\"'_i)@3  " <<
		"|" << std::setw(24) << "|(y\"'_i)@2-(y\"'_i)@3|" <<
		"|" << std::setw(7) << "correct" <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, ' ')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(17, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(19, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(19, '_')
		<< "|" << std::string(16, '_')
		<< "|" << std::string(16, '_')
		<< "|" << std::string(24, '_')
		<< "|" << std::string(7, '_')
		<< "|" << std::endl;
}
void printTableSecondStringThirdDerivativeMethod(const double mass_second_approx[], const double mass_third_approx[], const bool& correct)
{
	std::cout << "|" << std::setw(3) << "   ";

	if (mass_second_approx[0] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_second_approx[0];

	if (mass_third_approx[0] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_third_approx[0];

	if (abs(mass_second_approx[0] - mass_third_approx[0]) == 0)
		std::cout << "|" << std::setw(17) << "";
	else
		std::cout << "|" << std::setw(17) << std::setprecision(8) << abs(mass_second_approx[0] - mass_third_approx[0]);

	if (mass_second_approx[1] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_second_approx[1];

	if (mass_third_approx[1] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_third_approx[1];

	if (abs(mass_second_approx[1] - mass_third_approx[1]) == 0)
		std::cout << "|" << std::setw(19) << "";
	else
		std::cout << "|" << std::setw(19) << std::setprecision(8) << abs(mass_second_approx[1] - mass_third_approx[1]);

	if (mass_second_approx[2] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_second_approx[2];

	if (mass_third_approx[2] == 0)
		std::cout << "|" << std::setw(12) << "";
	else
		std::cout << "|" << std::setw(12) << std::setprecision(8) << mass_third_approx[2];

	if (abs(mass_second_approx[2] - mass_third_approx[2]) == 0)
		std::cout << "|" << std::setw(19) << "";
	else
		std::cout << "|" << std::setw(19) << std::setprecision(8) << abs(mass_second_approx[2] - mass_third_approx[2]);

	if (mass_second_approx[3] == 0)
		std::cout << "|" << std::setw(16) << "";
	else
		std::cout << "|" << std::setw(16) << std::setprecision(8) << mass_second_approx[3];

	if (mass_third_approx[3] == 0)
		std::cout << "|" << std::setw(16) << "";
	else
		std::cout << "|" << std::setw(16) << std::setprecision(8) << mass_third_approx[3];

	if (abs(mass_second_approx[3] - mass_third_approx[3]) == 0)
		std::cout << "|" << std::setw(24) << "";
	else
		std::cout << "|" << std::setw(24) << std::setprecision(8) << abs(mass_second_approx[3] - mass_third_approx[3]);

	std::cout << "|" << std::setw(7) << (correct ? "true" : "false") <<
		"|" << std::endl;
	std::cout << "|" << std::string(3, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(17, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(19, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(12, '_')
		<< "|" << std::string(19, '_')
		<< "|" << std::string(16, '_')
		<< "|" << std::string(16, '_')
		<< "|" << std::string(24, '_')
		<< "|" << std::string(7, '_')
		<< "|" << std::endl;
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
//Метод производной высшего порядка (до второго).
void second_derivative_method(const int& n, const double& epsilon)
{
	//Вычисление шага h.
	double h{ (b - a) / n };
	//Текущее обозначение xi (при i = 0).
	double xi{ x_0 };
	//Массивы для записи искомых значения, первой производной и второй производной, т.е. y_i, y'_i, y"_i соответственно (для y_(i-2), y_(i-1), y_i).
	double mass_y_i_2[3]{}, mass_y_i_1[3]{}, mass_y_i[3]{};
	//Итератор.
	int iter{};

	//Выполнение задания.
	while (xi - b <= 0.000000000000001) // Эквивалентно xi + h <= b (необходимо, чтобы избавиться от погрешности мантиссы в представлении чисел типа double на ЭВМ).
	{
		double y_exactly{ getExactlyValue(xi) };
		//Заполняется массив mass_y_i_2.
		if (iter == 0)
		{
			double temp_mass[3]{};
			mass_y_i_2[0] = y_0;
			mass_y_i_2[1] = getFirstDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[2] = getSecondDerivative(xi, mass_y_i_2[0]);
			printTableFirstHeaderSecondDerivativeMethod();
			printTableFirstStringSecondDerivativeMethod(xi, y_exactly, mass_y_i_2, temp_mass, h);
			printTableSecondHeaderSecondDerivativeMethod(iter);
			printTableSecondStringSecondDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//Значение y1 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i_1.
		else if (iter == 1)
		{
			double temp_mass[3]{};
			mass_y_i_1[0] = RKs_method_without_recalculation(xi - h, mass_y_i_2[0], h); // xi - h = x0, mass_y_i_2[0] = y0. 
			mass_y_i_1[1] = getFirstDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[2] = getSecondDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			printTableFirstHeaderSecondDerivativeMethod();
			printTableFirstStringSecondDerivativeMethod(xi, y_exactly, mass_y_i_1, temp_mass, h);
			printTableSecondHeaderSecondDerivativeMethod(iter);
			printTableSecondStringSecondDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//Значение y2 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i.
		else if (iter == 2)
		{
			double temp_mass[3]{};
			mass_y_i[0] = RKs_method_without_recalculation(xi - h, mass_y_i_1[0], h); // xi - h = x1, mass_y_i_1[0] = y1.
			mass_y_i[1] = getFirstDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[2] = getSecondDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			printTableFirstHeaderSecondDerivativeMethod();
			printTableFirstStringSecondDerivativeMethod(xi, y_exactly, mass_y_i, temp_mass, h);
			printTableSecondHeaderSecondDerivativeMethod(iter);
			printTableSecondStringSecondDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//---На данном этапе были определены первые три строчки, необходимые для реализации метода---//

		//Остальные значения yi определяются по соответствующему методу.
		else//---На данном этапе mass_y_i содержит значения, предшествующие вычисляемым значениям yi, y'_i, y"_i, которые являются (i+1)-ми значениями по отношению к соответствующим элементам массива---//
		{
			/*РЕАЛИЗАЦИЯ МЕТОДА*/
			//Массивы для записи первого, второго и третьего приближений для yi, y'_i, y"_i.
			double mass_first_approx[3]{}, mass_second_approx[3]{}, mass_third_approx[3]{};

			//Вычисление первого приближения для yi, y'_i, y"_i.
			mass_first_approx[0] = getNextSecondFormulaSecondDerivative(mass_y_i_2, mass_y_i_1, mass_y_i, h);
			mass_first_approx[1] = getFirstDerivative(xi, mass_first_approx[0]);
			mass_first_approx[2] = getSecondDerivative(xi, mass_first_approx[0]);
			//Вычисление второго приближения для yi, y'_i, y"_i.
			mass_second_approx[0] = getNextFirstFormulaSecondDerivative(mass_y_i, mass_first_approx, h);
			mass_second_approx[1] = getFirstDerivative(xi, mass_second_approx[0]);
			mass_second_approx[2] = getSecondDerivative(xi, mass_second_approx[0]);
			//Вычислениие третьего приближения для yi, y'_i, y"_i.
			mass_third_approx[0] = getNextFirstFormulaSecondDerivative(mass_y_i, mass_second_approx, h);
			mass_third_approx[1] = getFirstDerivative(xi, mass_third_approx[0]);
			mass_third_approx[2] = getSecondDerivative(xi, mass_third_approx[0]);

			//Проверка корректности выбора шага h за счет сравнения второго и третьего приближений.
			if (checkStepSecondDerivative(mass_second_approx, mass_third_approx, epsilon))
			{
				printTableFirstHeaderSecondDerivativeMethod();
				printTableFirstStringSecondDerivativeMethod(xi, y_exactly, mass_third_approx, mass_first_approx, h);
				printTableSecondHeaderSecondDerivativeMethod(iter);
				printTableSecondStringSecondDerivativeMethod(mass_second_approx, mass_third_approx, true);
				//Переформирование массивов.
				for (int i{}; i <= 2; i++)
				{
					mass_y_i_2[i] = mass_y_i_1[i];
					mass_y_i_1[i] = mass_y_i[i];
					mass_y_i[i] = mass_third_approx[i];
				}
				xi += h;
				++iter;
			}
			else //Необходимо уменьшить шаг h.
			{
				printTableFirstHeaderSecondDerivativeMethod();
				printTableFirstStringSecondDerivativeMethod(xi, y_exactly, mass_third_approx, mass_first_approx, h);
				printTableSecondHeaderSecondDerivativeMethod(iter);
				printTableSecondStringSecondDerivativeMethod(mass_second_approx, mass_third_approx, false);
				double prev_h{ h };
				h /= 2; //Уменьшаем шаг в 2 раза.
				//--(т.к. предыдущие значения вычисляются с прежним шагом)--//
				iter = 0; //Вовзращаемся к началу применения метода.
				xi = x_0; //Возвращаем xi к x0.
				std::cout << std::endl << "Необходимо уменьшить шаг h из-за достаточного расхождения второго и третьего приближений." <<
					std::endl << "Epsilon = " << epsilon << "\t\tПрежний шаг h = " << prev_h << "\tНовый шаг h = " << h << std::endl;
				if (h <= pow(10, -4))
				{
					std::cout << std::endl << "Шаг h = " << h << " слишком мал. Лучше выберите другой метод или epsilon, больший чем " << epsilon << "." << std::endl;
					break;
				}
			}
		}
	}
}
//Метод производной высшего порядка (до третьего).
void third_derivative_method(const int& n, const double& epsilon)
{
	//Вычисление шага h.
	double h{ (b - a) / n };
	//Текущее обозначение xi (при i = 0).
	double xi{ x_0 };
	//Массивы для записи искомых значения, первой производной, второй производной и третьей производной, т.е. y_i, y'_i, y"_i, y"'_i соответственно (для y_(i-2), y_(i-1), y_i).
	double mass_y_i_2[4]{}, mass_y_i_1[4]{}, mass_y_i[4]{};
	//Итератор.
	int iter{};

	//Выполнение задания.
	while (xi - b <= 0.000000000000001) // Эквивалентно xi + h <= b (необходимо, чтобы избавиться от погрешности мантиссы в представлении чисел типа double на ЭВМ).
	{
		double y_exactly{ getExactlyValue(xi) };
		//Заполняется массив mass_y_i_2.
		if (iter == 0)
		{
			double temp_mass[3]{};
			mass_y_i_2[0] = y_0;
			mass_y_i_2[1] = getFirstDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[2] = getSecondDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[3] = getThirdDerivative(xi, mass_y_i_2[0]);
			printTableFirstHeaderThirdDerivativeMethod();
			printTableFirstStringThirdDerivativeMethod(xi, y_exactly, mass_y_i_2, temp_mass, h);
			printTableSecondHeaderThirdDerivativeMethod(iter);
			printTableSecondStringThirdDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//Значение y1 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i_1.
		else if (iter == 1)
		{
			double temp_mass[3]{};
			mass_y_i_1[0] = RKs_method_without_recalculation(xi - h, mass_y_i_2[0], h); // xi - h = x0, mass_y_i_2[0] = y0. 
			mass_y_i_1[1] = getFirstDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[2] = getSecondDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[3] = getThirdDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			printTableFirstHeaderThirdDerivativeMethod();
			printTableFirstStringThirdDerivativeMethod(xi, y_exactly, mass_y_i_1, temp_mass, h);
			printTableSecondHeaderThirdDerivativeMethod(iter);
			printTableSecondStringThirdDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//Значение y2 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i.
		else if (iter == 2)
		{
			double temp_mass[3]{};
			mass_y_i[0] = RKs_method_without_recalculation(xi - h, mass_y_i_1[0], h); // xi - h = x1, mass_y_i_1[0] = y1.
			mass_y_i[1] = getFirstDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[2] = getSecondDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[3] = getThirdDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			printTableFirstHeaderThirdDerivativeMethod();
			printTableFirstStringThirdDerivativeMethod(xi, y_exactly, mass_y_i, temp_mass, h);
			printTableSecondHeaderThirdDerivativeMethod(iter);
			printTableSecondStringThirdDerivativeMethod(temp_mass, temp_mass, true);
			xi += h;
			++iter;
		}
		//---На данном этапе были определены первые три строчки, необходимые для реализации метода---//

		//Остальные значения yi определяются по соответствующему методу.
		else//---На данном этапе mass_y_i содержит значения, предшествующие вычисляемым значениям yi, y'_i, y"_i, y"'_i, которые являются (i+1)-ми значениями по отношению к соответствующим элементам массива---//
		{
			/*РЕАЛИЗАЦИЯ МЕТОДА*/
			//Массивы для записи первого, второго и третьего приближений для yi, y'_i, y"_i, y"'_i.
			double mass_first_approx[4]{}, mass_second_approx[4]{}, mass_third_approx[4]{};

			//Вычисление первого приближения для yi, y'_i, y"_i, y"'_i.
			mass_first_approx[0] = getNextSecondFormulaThirdDerivative(mass_y_i_2, mass_y_i_1, mass_y_i, h);
			mass_first_approx[1] = getFirstDerivative(xi, mass_first_approx[0]);
			mass_first_approx[2] = getSecondDerivative(xi, mass_first_approx[0]);
			mass_first_approx[3] = getThirdDerivative(xi, mass_first_approx[0]);
			//Вычисление второго приближения для yi, y'_i, y"_i, y"'_i.
			mass_second_approx[0] = getNextFirstFormulaThirdDerivative(mass_y_i, mass_first_approx, h);
			mass_second_approx[1] = getFirstDerivative(xi, mass_second_approx[0]);
			mass_second_approx[2] = getSecondDerivative(xi, mass_second_approx[0]);
			mass_second_approx[3] = getThirdDerivative(xi, mass_second_approx[0]);
			//Вычислениие третьего приближения для yi, y'_i, y"_i, y"'_i.
			mass_third_approx[0] = getNextFirstFormulaThirdDerivative(mass_y_i, mass_second_approx, h);
			mass_third_approx[1] = getFirstDerivative(xi, mass_third_approx[0]);
			mass_third_approx[2] = getSecondDerivative(xi, mass_third_approx[0]);
			mass_third_approx[3] = getThirdDerivative(xi, mass_third_approx[0]);

			//Проверка корректности выбора шага h за счет сравнения второго и третьего приближений.
			if (checkStepThirdDerivative(mass_second_approx, mass_third_approx, epsilon))
			{
				printTableFirstHeaderThirdDerivativeMethod();
				printTableFirstStringThirdDerivativeMethod(xi, y_exactly, mass_third_approx, mass_first_approx, h);
				printTableSecondHeaderThirdDerivativeMethod(iter);
				printTableSecondStringThirdDerivativeMethod(mass_second_approx, mass_third_approx, true);
				//Переформирование массивов.
				for (int i{}; i <= 3; i++)
				{
					mass_y_i_2[i] = mass_y_i_1[i];
					mass_y_i_1[i] = mass_y_i[i];
					mass_y_i[i] = mass_third_approx[i];
				}
				xi += h;
				++iter;
			}
			else //Необходимо уменьшить шаг h.
			{
				printTableFirstHeaderThirdDerivativeMethod();
				printTableFirstStringThirdDerivativeMethod(xi, y_exactly, mass_third_approx, mass_first_approx, h);
				printTableSecondHeaderThirdDerivativeMethod(iter);
				printTableSecondStringThirdDerivativeMethod(mass_second_approx, mass_third_approx, false);
				double prev_h{ h };
				h /= 2; //Уменьшаем шаг в 2 раза.
				//--(т.к. предыдущие значения вычисляются с прежним шагом)--//
				iter = 0; //Вовзращаемся к началу применения метода.
				xi = x_0; //Возвращаем xi к x0.
				std::cout << std::endl << "Необходимо уменьшить шаг h из-за достаточного расхождения второго и третьего приближений." <<
					std::endl << "Epsilon = " << epsilon << "\t\tПрежний шаг h = " << prev_h << "\tНовый шаг h = " << h << std::endl;
				if (h <= pow(10, -4))
				{
					std::cout << std::endl << "Шаг h = " << h << " слишком мал. Лучше выберите другой метод или epsilon, больший чем " << epsilon << "." << std::endl;
					break;
				}
			}
		}
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//---Вспомогательный метод---//
//Метод Рунге-Кутта 4-го порядка точности без пересчета.
double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h)
{
	//Вычисление постоянных K1i, K2i, K3i и K4i.
	double K1i{ h * (1.0 - xi * pow(yi, 3)) / (pow(xi, 2) * pow(yi, 2)) };
	double K2i{ h * (1.0 - (xi + h / 2) * pow(yi + K1i / 2, 3)) / (pow(xi + h / 2, 2) * pow(yi + K1i / 2, 2)) };
	double K3i{ h * (1.0 - (xi + h / 2) * pow(yi + K2i / 2, 3)) / (pow(xi + h / 2, 2) * pow(yi + K2i / 2, 2)) };
	double K4i{ h * (1.0 - (xi + h) * pow(yi + K3i, 3)) / (pow(xi + h, 2) * pow(yi + K3i, 2)) };
	//Вычисление y_(i+1).
	return (yi + 1.0 / 6.0 * (K1i + 2 * K2i + 2 * K3i + K4i));
}

//---Вычисление производных первого, второго и третьего порядка для исходной функции---//
//Вычисление первой производной.
double getFirstDerivative(const double& xi, const double& yi)
{
	return (1 - xi * pow(yi, 3)) / (pow(xi, 2) * pow(yi, 2));
}
//Вычисление второй производной.
double getSecondDerivative(const double& xi, const double& yi)
{
	return (2 * pow(xi, 2) * pow(yi, 6) - xi * pow(yi, 3) - 2) / (pow(xi, 4) * pow(yi, 5));
}
//Вычисление третьей производной.
double getThirdDerivative(const double& xi, const double& yi)
{
	return (-6 * pow(xi, 3) * pow(yi, 9) + 3 * pow(xi, 2) * pow(yi, 6) + 10) / (pow(xi, 6) * pow(yi, 8));
}

//---Вычисление значения y_(i+1) по различным формулам рассматриваемого метода---// 
//Вычисление y_(i+1) по первой формуле метода производной высшего порядка (до второго).
double getNextFirstFormulaSecondDerivative(const double mass_y_i[], const double mass_prev_approx[], const double& h)
{
	return (mass_y_i[0] + h / 2 * (mass_y_i[1] + mass_prev_approx[1]) + pow(h, 2) / 12 * (mass_y_i[2] - mass_prev_approx[2]));
}
//Вычисление y_(i+1) по второй формуле метода производной высшего порядка (до второго).
double getNextSecondFormulaSecondDerivative(const double mass_y_i_2[], const double mass_y_i_1[], const double mass_y_i[], const double& h)
{
	return (mass_y_i_2[0] + 3 * (mass_y_i[0] - mass_y_i_1[0]) + pow(h, 2) * (mass_y_i[2] - mass_y_i_1[2]));
}
//Вычисление y_(i+1) по первой формуле метода производной высшего порядка (до третьего).
double getNextFirstFormulaThirdDerivative(const double mass_y_i[], const double mass_prev_approx[], const double& h)
{
	return (mass_y_i[0] + h / 2 * (mass_prev_approx[1] + mass_y_i[1]) - pow(h, 2) / 10 * (mass_prev_approx[2] - mass_y_i[2]) + pow(h, 3) / 120 * (mass_prev_approx[3] + mass_y_i[3]));
}
//Вычисление y_(i+1) по второй формуле метода производной высшего порядка (до третьего).
double getNextSecondFormulaThirdDerivative(const double mass_y_i_2[], const double mass_y_i_1[], const double mass_y_i[], const double& h)
{
	return (mass_y_i_2[0] + 3 * (mass_y_i[0] - mass_y_i_1[0]) + pow(h, 3) / 2 * (mass_y_i[3] + mass_y_i_1[3]));
}

//---Вычисление точного значения y_i---//
double getExactlyValue(const double& xi)
{
	return cbrt(1.5 * pow(xi, 2) + 6.5) / xi;
}

//---Проверка корректности шага h---//
bool checkStepSecondDerivative(const double mass_second_approx[], const double mass_third_approx[], const double& epsilon)
{
	return ((mass_second_approx[0] - mass_third_approx[0] <= epsilon) && (mass_second_approx[1] - mass_third_approx[1] <= epsilon) &&
		(mass_second_approx[2] - mass_third_approx[2] <= epsilon)) ? true : false;
}
bool checkStepThirdDerivative(const double mass_second_approx[], const double mass_third_approx[], const double& epsilon)
{
	return ((mass_second_approx[0] - mass_third_approx[0] <= epsilon) && (mass_second_approx[1] - mass_third_approx[1] <= epsilon) &&
		(mass_second_approx[2] - mass_third_approx[2] <= epsilon) && (mass_second_approx[3] - mass_third_approx[3] <= epsilon)) ? true : false;
}