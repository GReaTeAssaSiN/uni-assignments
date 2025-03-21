#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"
//Для работы с файлом.
#include <fstream>

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

//---Вывод шапки исходной таблицы для метода производной высшего порядка (до второго)---//
void printTableHeaderSecondDerivativeMethod(std::ofstream& outputFile)
{
	outputFile << "i,xi,y*_i,y_i,y'_i,y\"_i,|y*_i - y_i|,(y_i)@1,(y'_i)@1,(y\"_i)@1,(y_i)@2,(y'_i)@2,(y\"_i)@2,(y_i)@3,(y'_i)@3,(y\"_i)@3,"
		<< "| (y_i)@2 - (y_i)@3 |,| (y'_i)@2 - (y'_i)@3 |,| (y\"_i)@2 - (y\"_i)@3 |,correct,h\n";
}
void printTableStringSecondDerivativeMethod(std::ofstream& outputFile, const int& iter, const double& xi, const double& y_exactly, const double mass_y_i[], 
	const bool& correct, const double& h, const double mass_first_approx[], const double mass_second_approx[], const double mass_third_approx[])
{
	outputFile << std::setprecision(10) << iter
		<< ',' << std::setprecision(10) << xi
		<< ',' << std::setprecision(10) << y_exactly
		<< ',' << std::setprecision(10) << mass_y_i[0]
		<< ',' << std::setprecision(10) << mass_y_i[1]
		<< ',' << std::setprecision(10) << mass_y_i[2]
		<< ',' << std::setprecision(10) << abs(y_exactly - mass_y_i[0]);
	if (mass_first_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_first_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_first_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[2];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[2];
	else
		outputFile << ',' << ' ';
	
	if (mass_third_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[2];
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[0] - mass_third_approx[0]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[0] - mass_third_approx[0]);
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[1] - mass_third_approx[1]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[1] - mass_third_approx[1]);
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[2] - mass_third_approx[2]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[2] - mass_third_approx[2]);
	else
		outputFile << ',' << ' ';

	outputFile << ',' << (correct ? "true" : "false") << ',' << h << "\n";
}
//---Вывод шапки исходной таблицы для метода производной высшего порядка (до третьего)---//
void printTableHeaderThirdDerivativeMethod(std::ofstream& outputFile)
{
	outputFile << "i,xi,y*_i,y_i,y'_i,y\"_i,y\"'_i,|y*_i - y_i|,(y_i)@1,(y'_i)@1,(y\"_i)@1,(y\"'_i)@1,(y_i)@2,(y'_i)@2,(y\"_i)@2,(y\"'_i)@2,(y_i)@3,(y'_i)@3,(y\"_i)@3,(y\"'_i)@3," 
		<< "| (y_i)@2 - (y_i)@3 |,| (y'_i)@2 - (y'_i)@3 |,| (y\"_i)@2 - (y\"_i)@3 |,| (y\"'_i)@2 - (y\"'_i)@3 |,correct,h\n";
}
void printTableStringThirdDerivativeMethod(std::ofstream& outputFile, const int& iter, const double& xi, const double& y_exactly, const double mass_y_i[],
	const bool& correct, const double& h, const double mass_first_approx[], const double mass_second_approx[], const double mass_third_approx[])
{
	outputFile << std::setprecision(10) << iter
		<< ',' << std::setprecision(10) << xi
		<< ',' << std::setprecision(10) << y_exactly
		<< ',' << std::setprecision(10) << mass_y_i[0]
		<< ',' << std::setprecision(10) << mass_y_i[1]
		<< ',' << std::setprecision(10) << mass_y_i[2]
		<< ',' << std::setprecision(10) << mass_y_i[3]
		<< ',' << std::setprecision(10) << abs(y_exactly - mass_y_i[0]);
	if (mass_first_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_first_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_first_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[2];
	else
		outputFile << ',' << ' ';

	if (mass_first_approx[3] != 0)
		outputFile << ',' << std::setprecision(10) << mass_first_approx[3];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[2];
	else
		outputFile << ',' << ' ';

	if (mass_second_approx[3] != 0)
		outputFile << ',' << std::setprecision(10) << mass_second_approx[3];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[0] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[0];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[1] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[1];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[2] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[2];
	else
		outputFile << ',' << ' ';

	if (mass_third_approx[3] != 0)
		outputFile << ',' << std::setprecision(10) << mass_third_approx[3];
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[0] - mass_third_approx[0]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[0] - mass_third_approx[0]);
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[1] - mass_third_approx[1]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[1] - mass_third_approx[1]);
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[2] - mass_third_approx[2]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[2] - mass_third_approx[2]);
	else
		outputFile << ',' << ' ';

	if (abs(mass_second_approx[3] - mass_third_approx[3]) != 0)
		outputFile << ',' << std::setprecision(10) << abs(mass_second_approx[3] - mass_third_approx[3]);
	else
		outputFile << ',' << ' ';

	outputFile << ',' << (correct ? "true" : "false") << ',' << h << "\n";
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
void second_derivative_method(const int& n, const double& epsilon, std::ofstream& outputFile)
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
			double empty_mass[3]{};
			mass_y_i_2[0] = y_0;
			mass_y_i_2[1] = getFirstDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[2] = getSecondDerivative(xi, mass_y_i_2[0]);
			printTableStringSecondDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i_2, "true", h, empty_mass, empty_mass, empty_mass);
			xi += h;
			++iter;
		}
		//Значение y1 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i_1.
		else if (iter == 1)
		{
			double empty_mass[3]{};
			mass_y_i_1[0] = RKs_method_without_recalculation(xi - h, mass_y_i_2[0], h); // xi - h = x0, mass_y_i_2[0] = y0. 
			mass_y_i_1[1] = getFirstDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[2] = getSecondDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			printTableStringSecondDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i_1, "true", h, empty_mass, empty_mass, empty_mass);
			xi += h;
			++iter;
		}
		//Значение y2 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i.
		else if (iter == 2)
		{
			double empty_mass[3]{};
			mass_y_i[0] = RKs_method_without_recalculation(xi - h, mass_y_i_1[0], h); // xi - h = x1, mass_y_i_1[0] = y1.
			mass_y_i[1] = getFirstDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[2] = getSecondDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			printTableStringSecondDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i, "true", h, empty_mass, empty_mass, empty_mass);
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
				printTableStringSecondDerivativeMethod(outputFile, iter, xi, y_exactly, mass_third_approx, "true", h, mass_first_approx, mass_second_approx, mass_third_approx);
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
				printTableStringSecondDerivativeMethod(outputFile, iter, xi, y_exactly, mass_third_approx, "false", h, mass_first_approx, mass_second_approx, mass_third_approx);
				double prev_h{ h };
				h /= 2; //Уменьшаем шаг в 2 раза.
				//--(т.к. предыдущие значения вычисляются с прежним шагом)--//
				iter = 0; //Вовзращаемся к началу применения метода.
				xi = x_0; //Возвращаем xi к x0.
				outputFile << "Прежний шаг h = " << prev_h << ",Новый шаг h =" << h << "\n";
				if (h <= pow(10, -4))
				{
					outputFile << "Шаг h = " << h << " слишком мал." << "\n";
					break;
				}
				printTableHeaderSecondDerivativeMethod(outputFile);
			}
		}
	}
}
//Метод производной высшего порядка (до третьего).
void third_derivative_method(const int& n, const double& epsilon, std::ofstream& outputFile)
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
			double empty_mass[3]{};
			mass_y_i_2[0] = y_0;
			mass_y_i_2[1] = getFirstDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[2] = getSecondDerivative(xi, mass_y_i_2[0]);
			mass_y_i_2[3] = getThirdDerivative(xi, mass_y_i_2[0]);
			printTableStringThirdDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i_2, "true", h, empty_mass, empty_mass, empty_mass);
			xi += h;
			++iter;
		}
		//Значение y1 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i_1.
		else if (iter == 1)
		{
			double empty_mass[3]{};
			mass_y_i_1[0] = RKs_method_without_recalculation(xi - h, mass_y_i_2[0], h); // xi - h = x0, mass_y_i_2[0] = y0. 
			mass_y_i_1[1] = getFirstDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[2] = getSecondDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			mass_y_i_1[3] = getThirdDerivative(xi, mass_y_i_1[0]);						// xi = x1, mass_y_i_1[0] = y1.
			printTableStringThirdDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i_1, "true", h, empty_mass, empty_mass, empty_mass);
			xi += h;
			++iter;
		}
		//Значение y2 вычисляется по методу Рунге-Кутта 4-го порядка точности, затем заполняется массив mass_y_i.
		else if (iter == 2)
		{
			double empty_mass[3]{};
			mass_y_i[0] = RKs_method_without_recalculation(xi - h, mass_y_i_1[0], h); // xi - h = x1, mass_y_i_1[0] = y1.
			mass_y_i[1] = getFirstDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[2] = getSecondDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			mass_y_i[3] = getThirdDerivative(xi, mass_y_i[0]);						  // xi = x2, mass_y_i[0] = y2.
			printTableStringThirdDerivativeMethod(outputFile, iter, xi, y_exactly, mass_y_i, "true", h, empty_mass, empty_mass, empty_mass);
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
				printTableStringThirdDerivativeMethod(outputFile, iter, xi, y_exactly, mass_third_approx, "true", h, mass_first_approx, mass_second_approx, mass_third_approx);
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
				printTableStringThirdDerivativeMethod(outputFile, iter, xi, y_exactly, mass_third_approx, "true", h, mass_first_approx, mass_second_approx, mass_third_approx);
				double prev_h{ h };
				h /= 2; //Уменьшаем шаг в 2 раза.
				//--(т.к. предыдущие значения вычисляются с прежним шагом)--//
				iter = 0; //Вовзращаемся к началу применения метода.
				xi = x_0; //Возвращаем xi к x0.
				outputFile << "Прежний шаг h = " << prev_h << ",Новый шаг h =" << h << "\n";
				if (h <= pow(10, -4))
				{
					outputFile << "Шаг h = " << h << " слишком мал." << "\n";
					break;
				}
				printTableHeaderThirdDerivativeMethod(outputFile);
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