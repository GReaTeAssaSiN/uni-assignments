#include "Circle.h"
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ КРУГА*/
//Сдвинуть круг случайным образом по x и по y из диапазона [-50;50]
void doOffsetCircle(TCircle* f_ptr_obj_circle)
{
	float x_circle{ f_ptr_obj_circle->getXPoint() };
	float y_circle{ f_ptr_obj_circle->getYPoint() };
	float radius_circle{ f_ptr_obj_circle->getRadius() };
	while (true)
	{
		float dx_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_circle + dx_circle + radius_circle <= 1495) && (x_circle - radius_circle + dx_circle >= 710) &&
			(y_circle + dy_circle + radius_circle <= 895) && (y_circle - radius_circle + dy_circle >= 100))
		{
			f_ptr_obj_circle->MoveTo(dx_circle, dy_circle);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА КРУГОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayCircles(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		float x_circle{ array_circles[i]->getXPoint() };
		float y_circle{ array_circles[i]->getYPoint() };
		float radius_circle{ array_circles[i]->getRadius() };
		while (true)
		{
			float dx_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_circle{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_circle + dx_circle + radius_circle <= 1495) && (x_circle - radius_circle + dx_circle >= 710) &&
				(y_circle + dy_circle + radius_circle <= 895) && (y_circle - radius_circle + dy_circle >= 100))
			{
				array_circles[i]->MoveTo(dx_circle, dy_circle);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayCirclesW(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->getYPoint() - array_circles[i]->getRadius() - 10 >= 100)
			array_circles[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayCirclesA(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->getXPoint() - array_circles[i]->getRadius() - 10 >= 710)
			array_circles[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayCirclesS(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->getYPoint() + array_circles[i]->getRadius() + 10 <= 895)
			array_circles[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayCirclesD(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
	{
		if (array_circles[i]->getXPoint() + array_circles[i]->getRadius() + 10 <= 1495)
			array_circles[i]->MoveTo(10, 0);
	}
}
//Увеличить радиус элементов
void array_circles_RadiusIncrease(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
		if ((array_circles[i]->getYPoint() + array_circles[i]->getRadius() + 2 <= 895) &&
			(array_circles[i]->getXPoint() + array_circles[i]->getRadius() + 2 <= 1495) &&
			(array_circles[i]->getYPoint() - array_circles[i]->getRadius() - 2 >= 100) &&
			(array_circles[i]->getXPoint() - array_circles[i]->getRadius() - 2 >= 710))
		{
			array_circles[i]->changeRadius(2);
		}
}
//Уменьшить радиус элементов
void array_circles_RadiusDecrease(TCircle** array_circles, int array_circles_size)
{
	for (int i{}; i < array_circles_size; i++)
		if (array_circles[i]->getRadius() >= 10)
		{
			array_circles[i]->changeRadius(-2);
		}
}