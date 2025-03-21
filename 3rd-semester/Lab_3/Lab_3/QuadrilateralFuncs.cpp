#include "Quadrilateral.h"
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ЧЕТЫРЕХУГОЛЬНИКА*/
//Сдвинуть четырехугольник случайным образом по x и по y из диапазона [-50;50]
void doOffsetQuadrilateral(TQuadrilateral* f_ptr_obj_quadrilateral)
{
	while (true)
	{
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((f_ptr_obj_quadrilateral->getXPoint() + dx) >= 710 && 
			(f_ptr_obj_quadrilateral->getYPoint() + dy) >= 100 && 
			(f_ptr_obj_quadrilateral->getX2Point() + dx) <= 1495 &&
			(f_ptr_obj_quadrilateral->getY2Point() + dy) >= 100 &&
			(f_ptr_obj_quadrilateral->getX3Point() + dx) <= 1495 &&
			(f_ptr_obj_quadrilateral->getY3Point() + dy) <= 895 &&
			(f_ptr_obj_quadrilateral->getX4Point() + dx) >= 710 &&
			(f_ptr_obj_quadrilateral->getY4Point() + dy) <= 895)
		{
			f_ptr_obj_quadrilateral->MoveTo(dx, dy);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА КРУГОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayQuadrilaterals(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
	{
		while (true)
		{
			float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((array_quadrilaterals[i]->getXPoint() + dx) >= 710 &&
				(array_quadrilaterals[i]->getYPoint() + dy) >= 100 &&
				(array_quadrilaterals[i]->getX2Point() + dx) <= 1495 &&
				(array_quadrilaterals[i]->getY2Point() + dy) >= 100 &&
				(array_quadrilaterals[i]->getX3Point() + dx) <= 1495 &&
				(array_quadrilaterals[i]->getY3Point() + dy) <= 895 &&
				(array_quadrilaterals[i]->getX4Point() + dx) >= 710 &&
				(array_quadrilaterals[i]->getY4Point() + dy) <= 895)
			{
				array_quadrilaterals[i]->MoveTo(dx, dy);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayQuadrilateralsW(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
	{
		if ((array_quadrilaterals[i]->getYPoint() - 10 >= 100) && (array_quadrilaterals[i]->getY2Point() - 10 >= 100))
			array_quadrilaterals[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayQuadrilateralsA(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
	{
		if ((array_quadrilaterals[i]->getXPoint() - 10 >= 710) && (array_quadrilaterals[i]->getX4Point() - 10 >= 710))
			array_quadrilaterals[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayQuadrilateralsS(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
	{
		if ((array_quadrilaterals[i]->getY3Point() + 10 <= 895) && (array_quadrilaterals[i]->getY4Point() + 10 <= 895))
			array_quadrilaterals[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayQuadrilateralsD(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
	{
		if ((array_quadrilaterals[i]->getX2Point() + 10 <= 1495) && (array_quadrilaterals[i]->getX3Point() + 10 <= 1495))
			array_quadrilaterals[i]->MoveTo(10, 0);
	}
}
//Увеличить размер элементов
void array_quadrilaterals_DimensionsIncrease(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
		if ((array_quadrilaterals[i]->getXPoint() - 1) >= 710 &&
			(array_quadrilaterals[i]->getYPoint() - 1) >= 100 &&
			(array_quadrilaterals[i]->getX2Point() + 1) <= 1495 &&
			(array_quadrilaterals[i]->getY2Point() - 1) >= 100 &&
			(array_quadrilaterals[i]->getX3Point() + 1) <= 1495 &&
			(array_quadrilaterals[i]->getY3Point() + 1) <= 895 &&
			(array_quadrilaterals[i]->getX4Point() - 1) >= 710 &&
			(array_quadrilaterals[i]->getY4Point() + 1) <= 895)
		{
			array_quadrilaterals[i]->changeSize(1);
		}
}
//Уменьшить размер элементов
void array_quadrilaterals_DimensionsDecrease(TQuadrilateral** array_quadrilaterals, int array_quadrilaterals_size)
{
	for (int i{}; i < array_quadrilaterals_size; i++)
		if ((array_quadrilaterals[i]->getX2Point() - array_quadrilaterals[i]->getXPoint() - 2 >= 50)
			&& (array_quadrilaterals[i]->getY3Point() - array_quadrilaterals[i]->getY2Point() - 2 >= 50))
			array_quadrilaterals[i]->changeSize(-1);
}