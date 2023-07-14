#include "class_TTrapeze.h"
#include "myfuncs.h"

void doOffsetTrapeze(TTrapeze* f_ptr_obj_trapeze)
{
	while (true)
	{
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((f_ptr_obj_trapeze->getXPoint() + dx) >= 710 &&
			(f_ptr_obj_trapeze->getYPoint() + dy) <= 895 &&
			(f_ptr_obj_trapeze->getY2Point() + dy) >= 100 &&
			(f_ptr_obj_trapeze->getX4Point() + dx) <= 1495 &&
			(f_ptr_obj_trapeze->getY4Point() + dy) <= 895)
		{
			f_ptr_obj_trapeze->MoveTo(dx, dy);
			f_ptr_obj_trapeze->changeBasePoints234(dx, dy);
			break;
		}
	}
}

void doOffsetArrayTrapezes(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		while (true)
		{
			float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) }, dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((array_trapezes[i]->getXPoint() + dx) >= 710 &&
				(array_trapezes[i]->getYPoint() + dy) <= 895 &&
				(array_trapezes[i]->getY2Point() + dy) >= 100 &&
				(array_trapezes[i]->getX4Point() + dx) <= 1495 &&
				(array_trapezes[i]->getY4Point() + dy) <= 895)
			{
				array_trapezes[i]->MoveTo(dx, dy);
				array_trapezes[i]->MoveTo(dx, dy);
				break;
			}
		}
	}
}
void doUserMoveArrayTrapezesW(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if ((array_trapezes[i]->getY2Point() - 10 >= 100)
			&& (array_trapezes[i]->getY3Point() - 10 >= 100))
		{
			array_trapezes[i]->MoveTo(0, -10);
			array_trapezes[i]->changeBasePoints234(0, -10);
		}
	}
}
void doUserMoveArrayTrapezesA(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if (array_trapezes[i]->getXPoint() - 10 >= 710)
		{
			array_trapezes[i]->MoveTo(-10, 0);
			array_trapezes[i]->changeBasePoints234(-10, 0);
		}
	}
}
void doUserMoveArrayTrapezesS(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if ((array_trapezes[i]->getYPoint() + 10 <= 895)
			&& (array_trapezes[i]->getY4Point() + 10 <= 895))
		{
			array_trapezes[i]->MoveTo(0, 10);
			array_trapezes[i]->changeBasePoints234(0, 10);
		}
	}
}
void doUserMoveArrayTrapezesD(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if ((array_trapezes[i]->getX4Point() + 10 <= 1495)
			&& (array_trapezes[i]->getX3Point() + 10 <= 1495))
		{
			array_trapezes[i]->MoveTo(10, 0);
			array_trapezes[i]->changeBasePoints234(10, 0);
		}
	}
}
void array_trapezes_IncreaseTopBase(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if (array_trapezes[i]->getX3Point() <= array_trapezes[i]->getX4Point())
			array_trapezes[i]->changeTopBase(1);
	}
}
void array_trapezes_DecreaseTopBase(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if (array_trapezes[i]->getX4Point() - array_trapezes[i]->getX3Point() - 1 <= 50)
			array_trapezes[i]->changeTopBase(-1);
	}
}
void array_trapezes_IncreaseHeight(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if ((array_trapezes[i]->getY2Point() - 1 >= 100) && (array_trapezes[i]->getYPoint() - array_trapezes[i]->getY2Point() + 1 <= 100))
			array_trapezes[i]->changeHeight(-1);
	}
}
void array_trapezes_DecreaseHeight(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if (array_trapezes[i]->getYPoint() - array_trapezes[i]->getY2Point() - 1 >= 30)
			array_trapezes[i]->changeHeight(1);
	}
}
void array_trapezes_IncreaseBottomBase(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if ((array_trapezes[i]->getX4Point() + 1 <= 1495) && ((array_trapezes[i]->getX4Point() + 1) <= (array_trapezes[i]->getX3Point() + 60)))
			array_trapezes[i]->changeBottomBase(1);
	}
}
void array_trapezes_DecreaseBottomBase(TTrapeze** array_trapezes, int array_trapezes_size)
{
	for (int i{}; i < array_trapezes_size; i++)
	{
		if (array_trapezes[i]->getX4Point() - 1 >= array_trapezes[i]->getX3Point())
			array_trapezes[i]->changeBottomBase(-1);
	}
}