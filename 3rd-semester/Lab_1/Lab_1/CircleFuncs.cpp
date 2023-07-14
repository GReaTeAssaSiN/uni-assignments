#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "myfuncs.h"
#include "constants.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ КРУГА*/
//Сдвинуть круг случайным образом по x и по y из диапазона [-50;50]
void doOffsetCircle(Circle* f_ptr_obj_circle)
{
	float x_circle{ f_ptr_obj_circle->get_x_coordinate_base_point() };
	float y_circle{ f_ptr_obj_circle->get_y_coordinate_base_point() };
	float radius_circle{ f_ptr_obj_circle->getRadius() };
	while (true)
	{
		float dx_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_circle + dx_circle + radius_circle <= 1500) && (x_circle - radius_circle + dx_circle >= 705) &&
			(y_circle + dy_circle + radius_circle <= 900) && (y_circle - radius_circle + dy_circle >= 95))
		{
			f_ptr_obj_circle->MoveTo(dx_circle, dy_circle);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА КРУГОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayCircles(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		float x_circle{ array_circles[i]->get_x_coordinate_base_point() };
		float y_circle{ array_circles[i]->get_y_coordinate_base_point() };
		float radius_circle{ array_circles[i]->getRadius() };
		while (true)
		{
			float dx_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_circle + dx_circle + radius_circle <= 1500) && (x_circle - radius_circle + dx_circle >= 705) &&
				(y_circle + dy_circle + radius_circle <= 900) && (y_circle - radius_circle + dy_circle >= 95))
			{
				array_circles[i]->MoveTo(dx_circle, dy_circle);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayCirclesW(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->get_y_coordinate_base_point() - array_circles[i]->getRadius() - 10 >= 95)
			array_circles[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayCirclesA(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->get_x_coordinate_base_point() - array_circles[i]->getRadius() - 10 >= 705)
			array_circles[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayCirclesS(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->get_y_coordinate_base_point() + array_circles[i]->getRadius() + 10 <= 900)
			array_circles[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayCirclesD(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->get_x_coordinate_base_point() + array_circles[i]->getRadius() + 10 <= 1500)
			array_circles[i]->MoveTo(10, 0);
	}
}
//Увеличить радиус элементов
void array_circles_RadiusIncrease(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
		if ((array_circles[i]->get_y_coordinate_base_point() + array_circles[i]->getRadius() + 2 <= 900) &&
			(array_circles[i]->get_x_coordinate_base_point() + array_circles[i]->getRadius() + 2 <= 1500) &&
			(array_circles[i]->get_y_coordinate_base_point() - array_circles[i]->getRadius() - 2 >= 95) &&
			(array_circles[i]->get_x_coordinate_base_point() - array_circles[i]->getRadius() - 2 >= 705))
		{
			array_circles[i]->changeRadius(2);
		}
}
//Уменьшить радиус элементов
void array_circles_RadiusDecrease(Circle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
		if (array_circles[i]->getRadius() >= 10)
		{
			array_circles[i]->changeRadius(-2);
		}
}