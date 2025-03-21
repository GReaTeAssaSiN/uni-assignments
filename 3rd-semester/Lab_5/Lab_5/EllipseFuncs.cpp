#include "Ellipse.h"
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ЭЛЛИПСА*/
//Сдвинуть эллипс случайным образом по x и по y из диапазона [-50;50]
void doOffsetEllipse(TEllipse* f_ptr_obj_ellipse)
{
	float x_ellipse{ f_ptr_obj_ellipse->getXPoint() };
	float y_ellipse{ f_ptr_obj_ellipse->getYPoint() };
	float ellipse_semi_major_axis{ f_ptr_obj_ellipse->getRadius() };
	float ellipse_semi_minor_axis{ f_ptr_obj_ellipse->getSemiMinorAxis() };
	while (true)
	{
		float dx_ellipse{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_ellipse{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_ellipse + dx_ellipse + ellipse_semi_major_axis <= 1500) && (x_ellipse - ellipse_semi_major_axis + dx_ellipse >= 705) &&
			(y_ellipse + dy_ellipse + ellipse_semi_minor_axis <= 900) && (y_ellipse - ellipse_semi_minor_axis + dy_ellipse >= 95))
		{
			f_ptr_obj_ellipse->MoveTo(dx_ellipse, dy_ellipse);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА ЭЛЛИПСОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayEllipses(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
	{
		float x_ellipse{ array_ellipses[i]->getXPoint() };
		float y_ellipse{ array_ellipses[i]->getYPoint() };
		float ellipse_semi_major_axis{ array_ellipses[i]->getRadius() };
		float ellipse_semi_minor_axis{ array_ellipses[i]->getSemiMinorAxis() };
		while (true)
		{
			float dx_ellipse{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_ellipse{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_ellipse + dx_ellipse + ellipse_semi_major_axis <= 1495) && (x_ellipse - ellipse_semi_major_axis + dx_ellipse >= 710) &&
				(y_ellipse + dy_ellipse + ellipse_semi_minor_axis <= 895) && (y_ellipse - ellipse_semi_minor_axis + dy_ellipse >= 100))
			{
				array_ellipses[i]->MoveTo(dx_ellipse, dy_ellipse);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayEllipsesW(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
	{
		if (array_ellipses[i]->getYPoint() - array_ellipses[i]->getSemiMinorAxis() - 10 >= 100)
			array_ellipses[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayEllipsesA(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
	{
		if (array_ellipses[i]->getXPoint() - array_ellipses[i]->getRadius() - 10 >= 710)
			array_ellipses[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayEllipsesS(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
	{
		if (array_ellipses[i]->getYPoint() + array_ellipses[i]->getSemiMinorAxis() + 10 <= 895)
			array_ellipses[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayEllipsesD(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
	{
		if (array_ellipses[i]->getXPoint() + array_ellipses[i]->getRadius() + 10 <= 1495)
			array_ellipses[i]->MoveTo(10, 0);
	}
}
//Увеличить большую полуось
void array_ellipses_SemiMajorAxisIncrease(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
		if ((array_ellipses[i]->getXPoint() + array_ellipses[i]->getRadius() + 2 <= 1495)
			&& (array_ellipses[i]->getXPoint() - array_ellipses[i]->getRadius() - 2 >= 710))
		{
			array_ellipses[i]->changeRadius(2);
		}
}
//Уменьшите большую полуось
void array_ellipses_SemiMajorAxisDecrease(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
		if (array_ellipses[i]->getRadius() - 2 >= 50)
		{
			array_ellipses[i]->changeRadius(-2);
		}
}
//Увеличить малую полуось
void array_ellipses_SemiMinorAxisIncrease(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
		if ((array_ellipses[i]->getYPoint() + array_ellipses[i]->getSemiMinorAxis() + 2 <= 895)
			&& (array_ellipses[i]->getYPoint() - array_ellipses[i]->getSemiMinorAxis() - 2 >= 100))
		{
			array_ellipses[i]->changeSemiMinorAxis(2);
		}
}
//Уменьшите малую полуось
void array_ellipses_SemiMinorAxisDecrease(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
		if (array_ellipses[i]->getSemiMinorAxis() - 2 >= 25)
		{
			array_ellipses[i]->changeSemiMinorAxis(-2);
		}
}
//Повернуть на 90 градусов
void array_ellipses_Rotate(TEllipse** array_ellipses, int array_ellipses_size)
{
	for (int i{}; i < array_ellipses_size; i++)
		if ((array_ellipses[i]->getXPoint() - array_ellipses[i]->getSemiMinorAxis() >= 710)
			&& (array_ellipses[i]->getXPoint() + array_ellipses[i]->getSemiMinorAxis() <= 1495)
			&& (array_ellipses[i]->getYPoint() - array_ellipses[i]->getRadius() >= 100)
			&& (array_ellipses[i]->getYPoint() + array_ellipses[i]->getRadius() <= 895))
		{
			array_ellipses[i]->rotateEllipse();
		}
}