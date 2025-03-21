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
	std::cout << "Вариант индивидуального задания: 9." << std::endl;
	std::cout << "Задача Коши (заданные обыкновенное дифференциальное уравнение и начальное условие):" << std::endl;
	std::cout << "  _\n |\n | dy/dx = (x - 1) * y;\n<\n | y(-2) = -2.\n |_" << std::endl << std::endl;
	std::cout << "Заданный отрезок: [-2, -1]." << std::endl;
	std::cout << "Общее решение ДУ: y = Ce^(x^2/2 - x), C принадлежит R." << std::endl;
	std::cout << "Частное решение ДУ (задача Коши): y = -2e^(x^2/2 - x - 4)." << std::endl;
}
//Вывод разделительной черты.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//Вывод шапки исходной таблицы для метода Эйлера, метода Рунге-Кутта без пересчета и метода Адамса.
void printTableOne()
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^Э     " <<
		"|" << std::setw(20) << "     |yi - yi^Э|    " <<
		"|" << std::setw(15) << "yi^(Р-К)  " <<
		"|" << std::setw(20) << "   |yi - yi^(Р-К)|  " <<
		"|" << std::setw(15) << "yi^А     " <<
		"|" << std::setw(20) << "     |yi - yi^А|    " <<
		"|" << std::endl;
	std::cout << std::string(144, '_') << std::endl;
}
//Вывод шапки исходной таблицы для метода Рунге-Кутта с пересчетом.
void printTableTwo()
{
	std::cout << std::string(134, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^(Р-К)  " <<
		"|" << std::setw(20) << "   |yi - yi^(Р-К)|  " <<
		"|" << std::setw(15) << "step" <<
		"|" << std::setw(15) << "y_H      " <<
		"|" << std::setw(20) << "|yi^(Р-К) - y_H|  " <<
		"|" << std::setw(10) << " correct  " <<
		"|" << std::endl;
	std::cout << std::string(134, '_') << std::endl;
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
//Метод Эйлера, метод Рунге-Кутта без пересчета и метод Адамса при n = 10;20.
void FirstTable_methods(const int& n)
{
	//Вычисление шага h.
	double h{ (b - a) / n };
	//Текущее значение xi и yi (при i = 0, начальное условие).
	double xi{ x_0 }, yi{ y_0 };

	//Переменные для значений yi^Э, yi^(Р-К), yi^А.
	double yi_E{ y_0 }, yi_RK{ y_0 }, yi_A{ y_0 };
	//Массивы из 4-х последних вычисленных значений xi, xi_1, xi_2, xi_3 и yi, yi_1, yi_2, yi_3 для метода Адамса.
	double Adams_xi_mass[4]{}, Adams_yi_mass[4]{};

	//Заполнение таблицы.
	for (int i{}; i <= n; i++)
	{
		//Начальное условие y(x0) = y0.
		if (i == 0)
		{
			//Формирование значений в массивах для метода Адамса.
			Adams_xi_mass[3] = xi;
			Adams_yi_mass[3] = yi;
		}
		//Вычисление xi и yi по соответствующим формулам методов.
		else
		{
			//Вычисление точного значения.
			yi = -2 * exp(pow(xi, 2) / 2 - xi - 4);
			//Значения, вычисленные по формулам методов.
			//Метод Эйлера.
			yi_E = Eulers_method(xi - h, yi_E, h);
			//Метод Рунге-Кутта без пересчета.
			yi_RK = RKs_method_without_recalculation(xi - h, yi_RK, h);
			//Метод Адамса.
			//При i < 4 yi считаются по формуле метода Рунге-Кутта 4-го порядка точности без пересчета.
			if (i < 4)
			{
				yi_A = yi_RK;
				//Формирование значений в массивах для метода Адамса.
				Adams_xi_mass[3 - i] = xi;
				Adams_yi_mass[3 - i] = yi_A;
			}
			//Иначе по формуле метода Адамса.
			else
			{
				yi_A = Adams_method(h, Adams_xi_mass, Adams_yi_mass);

				//Переформирование массивов для метода Адамса (все элементы сдвигаются на 1 вправо, первым элементом заносится текущий).
				for (int i{ 3 }; i > 0; i--)
				{
					Adams_xi_mass[i] = Adams_xi_mass[i - 1];
					Adams_yi_mass[i] = Adams_yi_mass[i - 1];
				}
				Adams_xi_mass[0] = xi;
				Adams_yi_mass[0] = yi_A;
			}
		}

		//Заполнение таблицы при текущем i.
		std::cout << "|" << std::setw(15) << std::setprecision(10) << xi <<
			"|" << std::setw(15) << std::setprecision(10) << yi <<
			"|" << std::setw(15) << std::setprecision(10) << yi_E <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_E) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_RK <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_RK) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_A <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_A) <<
			"|" << std::endl;
		std::cout << std::string(144, '_') << std::endl;

		//Вычисление x_(i+1) для следующей итерации.
		xi += h;
	}
}
//Метод Рунге-Кутта с пересчетом при n = 10;20.
void SecondTable_methods(const int& n, const double& epsilon)
{
	//Вычисление шага h и H.
	double h{ (b - a) / n }, H{ 2 * h };
	//Текущее значение xi и yi (при i = 0, начальное условие), yi^(Р-К) (при i = 0 yi^(Р-К) = y_0).
	double xi{ x_0 }, yi{ y_0 }, yi_RK{ y_0 };
	//Переменные для хранения значений y_h и y_H (для проверки правильности выбора шага h).
	double y_h{}, y_H{};
	//Массив, хранящий значения xi с шагом h на протяжении 2-х шагов.
	double RK_xi_mass[3]{};
	//Массив, хранящий значения yi^(Р-К) с шагом h на протяжении 2-х шагов.
	double RK_yi_mass[3]{};
	//Флаг для учета вывода в таблицу значений, связанных с первыми элементами массивов.
	bool correct_ouput{};

	//Метод Рунге-Кутта 4-го порядка точности с пересчетом.
	//Пока рассматриваемые значения xi, x_(i+1), x_(i+2) находится на отрезке [a, b] = [-2, -1].
	while ((xi + 2 * h) - b <= 0.000000000000001) // Эквивалентно xi + 2h <= b (необходимо, чтобы избавиться от погрешности мантиссы в представлении чисел типа double на ЭВМ).
	{
		//Первые элементы массивов значений xi и yi^(Р-К) равны текущим xi и yi^(Р-К).
		RK_xi_mass[0] = xi; RK_yi_mass[0] = yi_RK;
		//Вычесление y_(i+1) по методу Рунге-Кутта 4-го порядка точности.
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);
		//Занесение вычисленного y_(i+1) в массив значений yi^(Р-К).
		RK_yi_mass[1] = yi_RK;
		//Вычисление x_(i+1).
		xi += h;
		//Занесение вычисленного x_(i+1) в массив значений xi.
		RK_xi_mass[1] = xi;
		//Вычисление y_(i+2) по методу Рунге-Кутта 4-го порядка точности.
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);
		//Занесение вычисленного y_(i+2) в массив значений yi^(Р-К).
		RK_yi_mass[2] = yi_RK;
		//Вычисление x_(i+2).
		xi += h;
		//Занесение вычисленного x_(i+2) в массив значений xi.
		RK_xi_mass[2] = xi;

		//Вычисление y_h (последний элемент массива значений yi^(Р-К)) и y_H с двойным шагом H (используются первые элементы массивов значений xi и yi^(Р-К)).
		y_h = RK_yi_mass[2];
		y_H = RKs_method_without_recalculation(RK_xi_mass[0], RK_yi_mass[0], H);

		//Заполнение таблицы при текущем i (на протяжении 2-х шагов).
		for (int i{}; i <= 2; i++) /* Первые элементы массивов RK_xi_mass и RK_yi_mass используются для "отката" в случае неверного выбора шага и "старта" при рассмотрении 2-х шагов на данной итерации.
									* В каждой последующей итерации после первой первым элементом каждого массива является последний элемент на предыдущей итерации.
									*/
		{
			if (i == 0 && correct_ouput)
				continue;
			//Вычисление точного значения yi.
			yi = -2 * exp(pow(RK_xi_mass[i], 2) / 2 - RK_xi_mass[i] - 4);
			std::cout << "|" << std::setw(15) << std::setprecision(10) << RK_xi_mass[i] <<
				"|" << std::setw(15) << std::setprecision(10) << yi <<
				"|" << std::setw(15) << std::setprecision(10) << RK_yi_mass[i] <<
				"|" << std::setw(20) << std::setprecision(10) << abs(yi - RK_yi_mass[i]) <<
				"|" << std::setw(15) << std::setprecision(10) << h << "|";
			if (i != 2)
				std::cout << std::setw(15) << std::setprecision(10) << "" <<
				"|" << std::setw(20) << std::setprecision(10) << "" <<
				"|" << std::setw(10) << "" <<
				"|" << std::endl;
			else
			{
				std::cout << std::setw(15) << std::setprecision(10) << y_H <<
					"|" << std::setw(20) << std::setprecision(10) << abs(y_h - y_H) << "|";
				if (abs(y_h - y_H) <= epsilon)
					std::cout << std::setw(10) << "true";
				else
					std::cout << std::setw(10) << "false";
					std::cout << "|" << std::endl;
			}
			if (!correct_ouput)
				correct_ouput = true;
			std::cout << std::string(134, '_') << std::endl;
		}

		//Проверка правильности выбора шага h.
		if (abs(y_h - y_H) > epsilon)
		{
			//Отходим на два шага назад.
			xi = RK_xi_mass[0];
			yi = RK_yi_mass[0];
			//Уменьшаем текущий шаг h вдвое.
			h /= 2;
			//Заново вычисляем шаг H = 2 * h.
			H = 2 * h;
		}
	}
}
//Метод Эйлера.
double Eulers_method(const double& xi, const double& yi, const double& h)
{
	//Вычисление y_(i+1).
	return (yi + h * (xi - 1) * yi);
}
//Метод Рунге-Кутта 4-го порядка точности без пересчета.
double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h)
{
	//Вычисление постоянных K1i, K2i, K3i и K4i.
	double K1i{ h * (xi - 1) * yi };
	double K2i{ h * (xi + h / 2 - 1) * (yi + K1i / 2) };
	double K3i{ h * (xi + h / 2 - 1) * (yi + K2i / 2) };
	double K4i{ h * (xi + h - 1) * (yi + K3i) };
	//Вычисление y_(i+1).
	return (yi + 1.0 / 6.0 * (K1i + 2 * K2i + 2 * K3i + K4i));
}
//Метод Адамса.
double Adams_method(const double& h, const double Adams_xi_mass[], const double Adams_yi_mass[])
{	
	//Вычисление y'i, y'i_1, y'i_2, y'i_3.
	double yi{ Adams_yi_mass[0] }, dyi{ (Adams_xi_mass[0] - 1) * Adams_yi_mass[0] }, dyi_1{ (Adams_xi_mass[1] - 1) * Adams_yi_mass[1] },
		dyi_2{ (Adams_xi_mass[2] - 1) * Adams_yi_mass[2] }, dyi_3{ (Adams_xi_mass[3] - 1) * Adams_yi_mass[3] };
	//Вычисление y_(i+1).
	return (yi + h / 24.0 * (55 * dyi - 59 * dyi_1 + 37 * dyi_2 - 9 * dyi_3));
}