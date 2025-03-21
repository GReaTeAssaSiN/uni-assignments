#include "Linesegment.h"
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ОТРЕЗКА*/
//Сдвинуть отрезок случайным образом по x и по y из диапазона [-50;50]
void doOffsetlinesegment(TLinesegment* f_ptr_obj_linesegment)
{
	while (true)
	{
		float x_linesegment{ f_ptr_obj_linesegment->getXPoint() };
		float y_linesegment{ f_ptr_obj_linesegment->getYPoint() };
		float length_linesegment{ f_ptr_obj_linesegment->getLength() };
		int degree_linesegment{ static_cast<int>(f_ptr_obj_linesegment->getDegree()) };
		const float pi{ acos(-1.0f) }; float alpha_linesegment{ degree_linesegment * pi / 180 };
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 90 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -270)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1495 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 895)

			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -180)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 710 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 1495)
			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 710 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 100)
			{
				f_ptr_obj_linesegment->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 270 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -90 && degree_linesegment % 360 <= 0)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1495 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 100)
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
void doOffsetArrayLinesegments(TLinesegment** array_linesegments, int num_element)
{
	while (true)
	{
		float x_linesegment{ array_linesegments[num_element]->getXPoint() };
		float y_linesegment{ array_linesegments[num_element]->getYPoint() };
		float length_linesegment{ array_linesegments[num_element]->getLength() };
		int degree_linesegment{ static_cast<int>(array_linesegments[num_element]->getDegree()) };
		const float pi{ acos(-1.0f) }; float alpha_linesegment{ degree_linesegment * pi / 180 };
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 90 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -270)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1495 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 895)

			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -180)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy >= 95 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 710 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy <= 1495)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + dx <= 1500 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx >= 710 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 100)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 270 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -90 && degree_linesegment % 360 <= 0)
		{
			if (x_linesegment + dx >= 705 && y_linesegment + dy <= 900 && x_linesegment + length_linesegment * cos(alpha_linesegment) + dx <= 1495 &&
				y_linesegment + length_linesegment * sin(alpha_linesegment) + dy >= 100)
			{
				array_linesegments[num_element]->MoveTo(dx, dy);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayLinesegmentsW(TLinesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint()};
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
		{
			if (y_linesegment + length_linesegment * sin(alpha_linesegment) - 10 >= 100)
				array_linesegments[i]->MoveTo(0, -10);
		}
		else if (y_linesegment - 10 >= 100)
		{
			array_linesegments[i]->MoveTo(0, -10);
		}
	}
}
void doUserMoveArrayLinesegmentsA(TLinesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint()};
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + length_linesegment * cos(alpha_linesegment) - 10 >= 710)
				array_linesegments[i]->MoveTo(-10, 0);
		}
		else if (x_linesegment - 10 >= 710)
		{
			array_linesegments[i]->MoveTo(-10, 0);
		}
	}
}
void doUserMoveArrayLinesegmentsS(TLinesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint()};
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
		{
			if (y_linesegment + length_linesegment * sin(alpha_linesegment) + 10 <= 895)
				array_linesegments[i]->MoveTo(0, 10);
		}
		else if (y_linesegment + 10 <= 895)
		{
			array_linesegments[i]->MoveTo(0, 10);
		}
	}
}
void doUserMoveArrayLinesegmentsD(TLinesegment** array_linesegments, int array_linesegments_size)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint() };
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
		{
			if (x_linesegment + 10 <= 1495)
				array_linesegments[i]->MoveTo(10, 0);
		}
		else if (x_linesegment + length_linesegment * cos(alpha_linesegment) + 10 <= 1495)
		{
			array_linesegments[i]->MoveTo(10, 0);
		}
	}
}
//Изменение размеров элементов
void array_linesegments_changeDimensions(TLinesegment** array_linesegments, int array_linesegments_size, int dLength)
{

	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint() };
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (dLength > 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) <= 1495 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment) + 1) >= 710 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) <= 895 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment) + 1) >= 100)
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
void array_linesegments_changeRotate(TLinesegment** array_linesegments, int array_linesegments_size, int dDegree)
{
	for (int i{}; i < array_linesegments_size; i++)
	{
		int degree_linesegment{ static_cast<int>(array_linesegments[i]->getDegree()) };
		float x_linesegment{ array_linesegments[i]->getXPoint() };
		float y_linesegment{ array_linesegments[i]->getYPoint() };
		float length_linesegment{ array_linesegments[i]->getLength() };
		float alpha_linesegment{ degree_linesegment * PI / 180 };
		if (dDegree > 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) <= 1495 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment + PI / 180)) >= 710 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) <= 895 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment + PI / 180)) >= 100)
			{
				array_linesegments[i]->changeDegree(1);
			}
		}
		else if (dDegree < 0)
		{
			if ((x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) <= 1495 &&
				(x_linesegment + length_linesegment * cos(alpha_linesegment - PI / 180)) >= 710 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) <= 895 &&
				(y_linesegment + length_linesegment * sin(alpha_linesegment - PI / 180)) >= 100)
			{
				array_linesegments[i]->changeDegree(-1);
			}
		}
	}
}