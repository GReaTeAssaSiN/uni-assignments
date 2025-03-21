#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "myfuncs.h"
#include "constants.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ПРЯМОУГОЛЬНИКА*/
//Сдвинуть прямоугольник случайным образом по x и по y из диапазона [-50;50]
void doOffsetRect(Rectangle* f_ptr_obj_rect)
{
	float x_rect{ f_ptr_obj_rect->get_x_coordinate_base_point() };
	float y_rect{ f_ptr_obj_rect->get_y_coordinate_base_point() };
	float length_rect{ f_ptr_obj_rect->getLength() };
	float width_rect{ f_ptr_obj_rect->getWidth() };
	while (true)
	{
		float dx_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_rect + dx_rect + length_rect <= 1500) && (x_rect + dx_rect >= 705) && (y_rect + dy_rect + width_rect <= 900) && (y_rect + dy_rect >= 95))
		{
			f_ptr_obj_rect->MoveTo(dx_rect, dy_rect);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА ПРЯМОУГОЛЬНИКОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayRectangles(Rectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		float x_rect{ array_rectangles[i]->get_x_coordinate_base_point() };
		float y_rect{ array_rectangles[i]->get_y_coordinate_base_point() };
		float width_rect{ array_rectangles[i]->getWidth() };
		float length_rect{ array_rectangles[i]->getLength() };
		while (true)
		{
			float dx_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_rect + dx_rect + length_rect <= 1500) && (x_rect + dx_rect >= 705) && (y_rect + dy_rect + width_rect <= 900) && (y_rect + dy_rect >= 95))
			{
				array_rectangles[i]->MoveTo(dx_rect, dy_rect);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayRectanglesW(Rectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->get_y_coordinate_base_point() - 10 >= 95)
			array_rectangles[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayRectanglesA(Rectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->get_x_coordinate_base_point() - 10 >= 705)
			array_rectangles[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayRectanglesS(Rectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->get_y_coordinate_base_point() + array_rectangles[i]->getWidth() + 10 <= 900)
			array_rectangles[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayRectanglesD(Rectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->get_x_coordinate_base_point() + array_rectangles[i]->getLength() + 10 <= 1500)
			array_rectangles[i]->MoveTo(10, 0);
	}
}
//Изменение размеров элементов
void array_rectangles_ChangeDimensions(Rectangle** array_rectangles, int array_rectangles_size, int dLength, int dWidth)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if ((array_rectangles[i]->get_x_coordinate_base_point() + array_rectangles[i]->getLength() + dLength <= 1500) && dLength > 0 && dWidth == 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		else if ((array_rectangles[i]->getLength() >= 50) && dLength < 0 && dWidth == 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		if ((array_rectangles[i]->get_y_coordinate_base_point() + array_rectangles[i]->getWidth() + dWidth <= 900) && dLength == 0 && dWidth > 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		else if (array_rectangles[i]->getWidth() >= 25 && dLength == 0 && dWidth < 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}
	}
}