#include <SFML/Graphics.hpp>
#include "Ring.h"
#include "myfuncs.h"
#include "constants.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ КОЛЬЦА*/
//Сдвинуть кольцо случайным образом по x и по y из диапазона [-50;50]
void doOffsetRing(Ring* f_ptr_obj_ring)
{
	float x_ring{ f_ptr_obj_ring->getCircleOuter().get_x_coordinate_base_point()};
	float y_ring{ f_ptr_obj_ring->getCircleOuter().get_y_coordinate_base_point()};
	float radius_outer_circle{ f_ptr_obj_ring->getCircleOuter().getRadius()};
	while (true)
	{
		float dx_ring{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_ring{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_ring + dx_ring + radius_outer_circle <= 1495) && (x_ring - radius_outer_circle + dx_ring >= 710) &&
			(y_ring + dy_ring + radius_outer_circle <= 895) && (y_ring - radius_outer_circle + dy_ring >= 100))
		{
			f_ptr_obj_ring->MoveTo(dx_ring, dy_ring);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА КОЛЕЦ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayRings(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
	{
		float x_ring{ array_rings[i]->getCircleOuter().get_x_coordinate_base_point() };
		float y_ring{ array_rings[i]->getCircleOuter().get_y_coordinate_base_point() };
		float radius_outer_circle{ array_rings[i]->getCircleOuter().getRadius() };
		while (true)
		{
			float dx_ring{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_ring{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_ring + dx_ring + radius_outer_circle <= 1495) && (x_ring - radius_outer_circle + dx_ring >= 710) &&
				(y_ring + dy_ring + radius_outer_circle <= 900) && (y_ring - radius_outer_circle + dy_ring >= 95))
			{
				array_rings[i]->MoveTo(dx_ring, dy_ring);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayRingsW(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
	{
		if (array_rings[i]->getCircleOuter().get_y_coordinate_base_point() - array_rings[i]->getCircleOuter().getRadius() >= 105)
			array_rings[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayRingsA(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
	{
		if (array_rings[i]->getCircleOuter().get_x_coordinate_base_point() - array_rings[i]->getCircleOuter().getRadius() >= 715)
			array_rings[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayRingsS(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
	{
		if (array_rings[i]->getCircleOuter().get_y_coordinate_base_point() + array_rings[i]->getCircleOuter().getRadius() <= 890)
			array_rings[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayRingsD(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
	{
		if (array_rings[i]->getCircleOuter().get_x_coordinate_base_point() + array_rings[i]->getCircleOuter().getRadius() <= 1490)
			array_rings[i]->MoveTo(10, 0);
	}
}
//Увеличить размер элементов
void array_rings_DimensionsIncrease(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
		if ((array_rings[i]->getCircleOuter().get_y_coordinate_base_point() + array_rings[i]->getCircleOuter().getRadius() + 2 <= 895)
			&& (array_rings[i]->getCircleOuter().get_x_coordinate_base_point() + array_rings[i]->getCircleOuter().getRadius() + 2 <= 1495)
			&& (array_rings[i]->getCircleOuter().get_y_coordinate_base_point() - array_rings[i]->getCircleOuter().getRadius() - 2 >= 100)
			&& (array_rings[i]->getCircleOuter().get_x_coordinate_base_point() - array_rings[i]->getCircleOuter().getRadius() - 2 >= 710))
		{
			array_rings[i]->getCircleOuter().changeRadius(2);
			array_rings[i]->getCircleInner().changeRadius(2);
		}
}
//Уменьшить размер элементов
void array_rings_DimensionsDecrease(Ring** array_rings, int array_rings_size)
{
	for (int i{}; i < array_rings_size; i++)
		if (array_rings[i]->getCircleInner().getRadius() >= 10)
		{
			array_rings[i]->getCircleOuter().changeRadius(-2);
			array_rings[i]->getCircleInner().changeRadius(-2);
		}
}