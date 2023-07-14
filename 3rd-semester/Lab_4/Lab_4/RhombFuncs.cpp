#include "class_TRhomb.h"
#include "myfuncs.h"

void doOffsetRhomb(TRhomb* f_ptr_obj_rhomb)
{
	while (true)
	{
		float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((f_ptr_obj_rhomb->getXPoint() + dx) >= 710 &&
			(f_ptr_obj_rhomb->getY2Point() + dy) >= 100 &&
			(f_ptr_obj_rhomb->getX3Point() + dx) <= 1495 &&
			(f_ptr_obj_rhomb->getY4Point() + dy) <= 895)
		{
			f_ptr_obj_rhomb->MoveTo(dx, dy);
			f_ptr_obj_rhomb->changeBasePoints234(dx, dy);
			break;
		}
	}
}

void doOffsetArrayRhombs(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		while (true)
		{
			float dx{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((array_rhombs[i]->getXPoint() + dx) >= 710 &&
				(array_rhombs[i]->getY2Point() + dy) >= 100 &&
				(array_rhombs[i]->getX3Point() + dx) <= 1495 &&
				(array_rhombs[i]->getY4Point() + dy) <= 895)
			{
				array_rhombs[i]->MoveTo(dx, dy);
				array_rhombs[i]->MoveTo(dx, dy);
				break;
			}
		}
	}
}
void doUserMoveArrayRhombsW(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if (array_rhombs[i]->getY2Point() - 10 >= 100)
		{
			array_rhombs[i]->MoveTo(0, -10);
			array_rhombs[i]->changeBasePoints234(0, -10);
		}
	}
}
void doUserMoveArrayRhombsA(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if (array_rhombs[i]->getXPoint() - 10 >= 710)
		{
			array_rhombs[i]->MoveTo(-10, 0);;
			array_rhombs[i]->changeBasePoints234(-10, 0);
		}
	}
}
void doUserMoveArrayRhombsS(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if (array_rhombs[i]->getY4Point() + 10 <= 895)
		{
			array_rhombs[i]->MoveTo(0, 10);
			array_rhombs[i]->changeBasePoints234(0, 10);
		}
	}
}
void doUserMoveArrayRhombsD(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if (array_rhombs[i]->getX3Point() + 10 <= 1495)
		{
			array_rhombs[i]->MoveTo(10, 0);
			array_rhombs[i]->changeBasePoints234(10, 0);
		}
	}
}
void array_rhombs_IncreaseLength(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if ((array_rhombs[i]->getY2Point() >= 100)
			&& (array_rhombs[i]->getY4Point() <= 900)
			&& (array_rhombs[i]->getX3Point() <= 1495))
		{
			array_rhombs[i]->changeLength(1);
		}
	}
}
void array_rhombs_DecreaseLength(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if (array_rhombs[i]->getLength() - 1 >= 30)
		{
			array_rhombs[i]->changeLength(-1);
		}
	}
}
void array_rhombs_IncreaseDegree(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if ((array_rhombs[i]->getDegree() + 1 <= 60)
			&& (array_rhombs[i]->getY2Point() >= 100)
			&& (array_rhombs[i]->getY4Point() <= 895))
		{
			array_rhombs[i]->changeDegree(1);
		}
	}
}
void array_rhombs_DecreaseDegree(TRhomb** array_rhombs, int array_rhombs_size)
{
	for (int i{}; i < array_rhombs_size; i++)
	{
		if ((array_rhombs[i]->getDegree() - 1 >= 15)
			&& (array_rhombs[i]->getX3Point() <= 1495))
		{
			array_rhombs[i]->changeDegree(-1);
		}
	}
}