#include <SFML/Graphics.hpp>
#include "Mortar.h"
#include "myfuncs.h"
#include "constants.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МОРТИРЫ*/
//Сдвинуть мортиру случайным образом по x и по y из диапазона [-50;50]
void doOffsetMortar(Mortar* f_ptr_obj_mortar)
{
	float x_wheel{ f_ptr_obj_mortar->getCircleObj().get_x_coordinate_base_point() };
	float y_wheel { f_ptr_obj_mortar->getCircleObj().get_y_coordinate_base_point() };
	float radius_wheel{ f_ptr_obj_mortar->getCircleObj().getRadius() };
	float x_fire{ f_ptr_obj_mortar->getLineObj().get_x_coordinate_base_point() };
	float y_fire{ f_ptr_obj_mortar->getLineObj().get_y_coordinate_base_point() };
	float degree_fire{ f_ptr_obj_mortar->getLineObj().getDegree() };
	float length_fire{ f_ptr_obj_mortar->getLineObj().getLength() };
	float alpha_fire = degree_fire * PI / 180;
	while (true)
	{
		float dx_mortar{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_mortar{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_wheel - radius_wheel + dx_mortar >= 710) && (x_wheel + radius_wheel + dx_mortar <= 1495) 
			&& (y_wheel + radius_wheel +dy_mortar <= 895) && (y_fire + sin(alpha_fire) * length_fire + dy_mortar >= 105))
		{
			f_ptr_obj_mortar->getRectangleObj().MoveTo(dx_mortar, dy_mortar);
			f_ptr_obj_mortar->getCircleObj().MoveTo(dx_mortar, dy_mortar);
			f_ptr_obj_mortar->getLineObj().MoveTo(dx_mortar, dy_mortar);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА МОРТИР*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayMortars(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
	{
		float x_wheel{ array_mortars[i]->getCircleObj().get_x_coordinate_base_point()};
		float y_wheel{ array_mortars[i]->getCircleObj().get_y_coordinate_base_point() };
		float radius_wheel{ array_mortars[i]->getCircleObj().getRadius() };
		float x_fire{ array_mortars[i]->getLineObj().get_x_coordinate_base_point() };
		float y_fire{ array_mortars[i]->getLineObj().get_y_coordinate_base_point() };
		float degree_fire{ array_mortars[i]->getLineObj().getDegree() };
		float length_fire{ array_mortars[i]->getLineObj().getLength() };
		float alpha_fire = degree_fire * PI / 180;
		while (true)
		{
			float dx_mortar{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_mortar{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_wheel - radius_wheel + dx_mortar >= 710) && (x_wheel + radius_wheel + dx_mortar <= 1495)
				&& (y_wheel + radius_wheel + dy_mortar <= 895) && (y_fire + sin(alpha_fire) * length_fire + dy_mortar >= 105))
			{
				array_mortars[i]->getRectangleObj().MoveTo(dx_mortar, dy_mortar);
				array_mortars[i]->getCircleObj().MoveTo(dx_mortar, dy_mortar);
				array_mortars[i]->getLineObj().MoveTo(dx_mortar, dy_mortar);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayMortarsW(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
	{
		if (array_mortars[i]->getLineObj().get_y_coordinate_base_point() + sin(array_mortars[i]->getLineObj().getDegree() * PI / 180) * array_mortars[i]->getLineObj().getLength() >= 110)
			array_mortars[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayMortarsA(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
	{
		if (array_mortars[i]->getCircleObj().get_x_coordinate_base_point() - array_mortars[i]->getCircleObj().getRadius() >= 720)
			array_mortars[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayMortarsS(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
	{
		if (array_mortars[i]->getCircleObj().get_y_coordinate_base_point() + array_mortars[i]->getCircleObj().getRadius() <= 885)
			array_mortars[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayMortarsD(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
	{
		if (array_mortars[i]->getCircleObj().get_x_coordinate_base_point() + array_mortars[i]->getCircleObj().getRadius() <= 1485)
			array_mortars[i]->MoveTo(10, 0);
	}
}
//Увеличить размер элементов
void array_mortars_DimensionsIncrease(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
		if ((array_mortars[i]->getCircleObj().get_x_coordinate_base_point() - array_mortars[i]->getCircleObj().getRadius() - 1 >= 710)
			&& (array_mortars[i]->getCircleObj().get_x_coordinate_base_point() + array_mortars[i]->getCircleObj().getRadius() + 1 <= 1495)
			&& (array_mortars[i]->getCircleObj().get_y_coordinate_base_point() + array_mortars[i]->getCircleObj().getRadius() + 1 <= 895)
			&& (array_mortars[i]->getLineObj().get_y_coordinate_base_point() - 1 + 
				(array_mortars[i]->getLineObj().getLength() + 1) * sin(array_mortars[i]->getLineObj().getDegree() * PI / 180) >= 100))
		{
			array_mortars[i]->getRectangleObj().changeDimensions(2, 2);
			array_mortars[i]->getRectangleObj().MoveTo(-1, -1);
			array_mortars[i]->getCircleObj().changeRadius(1);
			array_mortars[i]->getCircleObj().MoveTo(0, 1);
			array_mortars[i]->getLineObj().changeLength(1.5);
			array_mortars[i]->getLineObj().MoveTo(0, -1);
		}
}
//Уменьшить размер элементов
void array_mortars_DimensionsDecrease(Mortar** array_mortars, int array_mortars_size)
{
	for (int i{}; i < array_mortars_size; i++)
		if ((array_mortars[i]->getCircleObj().getRadius() >= 25)
			&& (array_mortars[i]->getLineObj().getLength() >= 50))
		{
			array_mortars[i]->getRectangleObj().changeDimensions(-2, -2);
			array_mortars[i]->getRectangleObj().MoveTo(1, 1);
			array_mortars[i]->getCircleObj().changeRadius(-1);
			array_mortars[i]->getCircleObj().MoveTo(0, -1);
			array_mortars[i]->getLineObj().changeLength(-1.5);
			array_mortars[i]->getLineObj().MoveTo(0, 1);
		}
}