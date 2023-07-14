#include <SFML/Graphics.hpp>
#include "Linesegment.h"
#include "myfuncs.h"
#include "constants.h"


/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ОТРЕЗКА*/
//Функция подбора X и Y координаты относительно длины и угла поворота отрезка
void getRandomX_Y(float& x_linesegment, float& y_linesegment, float length_linesegment, float degree_linesegment)
{
	float pi{ acos(-1.0f) }; float alpha_linesegment{ degree_linesegment * pi / 180 };
	if (degree_linesegment >= 0 && degree_linesegment <= 90)
	{
		x_linesegment = getRandomNumber(705, 1500 - length_linesegment * cos(alpha_linesegment));
		y_linesegment = getRandomNumber(95, 900 - length_linesegment * sin(alpha_linesegment));
	}
	else if (degree_linesegment >= 90 && degree_linesegment <= 180)
	{
		x_linesegment = getRandomNumber(705 - length_linesegment * cos(alpha_linesegment), 1500);
		y_linesegment = getRandomNumber(95, 900 - length_linesegment * sin(alpha_linesegment));
	}
	else if (degree_linesegment >= 180 && degree_linesegment <= 270)
	{
		x_linesegment = getRandomNumber(705 - length_linesegment * cos(alpha_linesegment), 1500);
		y_linesegment = getRandomNumber(95 - length_linesegment * sin(alpha_linesegment), 900);
	}
	else if (degree_linesegment >= 270 && degree_linesegment <= 360)
	{
		x_linesegment = getRandomNumber(705, 1500 - length_linesegment * cos(alpha_linesegment));
		y_linesegment = getRandomNumber(95 - length_linesegment * sin(alpha_linesegment), 900);
	}
}
//Сдвинуть отрезок случайным образом по x и по y из диапазона [-50;50]
void doOffsetlinesegment(Linesegment* f_ptr_obj_linesegment)
{
	while (true)
	{
		float x_linesegment{ f_ptr_obj_linesegment->get_x_coordinate_base_point() };
		float y_linesegment{ f_ptr_obj_linesegment->get_y_coordinate_base_point() };
		float length_linesegment{ f_ptr_obj_linesegment->getLength() };
		int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
		const float pi{ acos(-1.0f) }; float alpha_linesegment{ degree_linesegment * pi / 180 };
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 90 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -270)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1500 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 900)

			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -180)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 705 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 1500)
			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 705 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 95)
			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 270 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -90 && degree_linesegment % 360 <= 0)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1500 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 95)
			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА ОТРЕЗКОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayLinesegments(Linesegment** array_linesegments, int num_element)
{
	while (true)
	{
		float x_linesegment{ array_linesegments[num_element]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[num_element]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[num_element]->getLength() };
		int degree_linesegment{ static_cast<int>(array_linesegments[num_element]->getDegree()) };
		const float pi{ acos(-1.0f) }; float alpha_linesegment{ degree_linesegment * pi / 180 };
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 90 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -270)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1500 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 900)

			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -180)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 705 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 1500)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 705 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 95)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 270 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -90 && degree_linesegment % 360 <= 0)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1500 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 95)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayLinesegmentsW(Linesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
		{
			if (y_linesegment + length_linesegment * sin(alpha_linesegment) - 10 >= 95)
				array_linesegments[i]->MoveTo(0, -10);
		}
		else if (y_linesegment - 10 >= 95)
		{
			array_linesegments[i]->MoveTo(0, -10);
		}
	}
}
void doUserMoveArrayLinesegmentsA(Linesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + length_linesegment * cos(alpha_linesegment) - 10 >= 705)
				array_linesegments[i]->MoveTo(-10, 0);
		}
		else if (x_linesegment - 10 >= 705)
		{
			array_linesegments[i]->MoveTo(-10, 0);
		}
	}
}
void doUserMoveArrayLinesegmentsS(Linesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
		{
			if (y_linesegment + length_linesegment * sin(alpha_linesegment) + 10 <= 900)
				array_linesegments[i]->MoveTo(0, 10);
		}
		else if (y_linesegment + 10 <= 900)
		{
			array_linesegments[i]->MoveTo(0, 10);
		}
	}
}
void doUserMoveArrayLinesegmentsD(Linesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + 10 <= 1500)
				array_linesegments[i]->MoveTo(10, 0);
		}
		else if (x_linesegment + length_linesegment * cos(alpha_linesegment) + 10 <= 1500)
		{
			array_linesegments[i]->MoveTo(10, 0);
		}
	}
}
//Изменение размеров элементов
void array_linesegments_changeDimensions(Linesegment** array_linesegments, int array_linesegments_size, int dLength)
{

	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (dLength > 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) <= 1500 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) >= 705 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) <= 900 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) >= 95)
			{
				array_linesegments[i]->changeLength(1);
			}
		}
		else if (dLength < 0)
		{
			if (length_linesegment - 1 >= 50)
			{
				array_linesegments[i]->changeLength(-1);
			}
		}
	}
}
//Поворот элементов
void array_linesegments_changeRotate(Linesegment** array_linesegments, int array_linesegments_size, int dDegree)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->get_x_coordinate_base_point() };
		float y_linesegment{ array_linesegments[i]->get_y_coordinate_base_point() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (dDegree > 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) <= 1500 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) >= 705 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) <= 900 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) >= 95)
			{
				array_linesegments[i]->changeDegree(1);
			}
		}
		else if (dDegree < 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) <= 1500 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) >= 705 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) <= 900 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) >= 95)
			{
				array_linesegments[i]->changeDegree(-1);
			}
		}
	}
}