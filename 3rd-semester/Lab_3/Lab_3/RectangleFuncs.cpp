#include "Rectangle.h"
#include "myfuncs.h"

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ ПРЯМОУГОЛЬНИКА*/
//Сдвинуть прямоугольник случайным образом по x и по y из диапазона [-50;50]
void doOffsetRect(TRectangle* f_ptr_obj_rect)
{
	float x_rect{ f_ptr_obj_rect->getXPoint() };
	float y_rect{ f_ptr_obj_rect->getYPoint() };
	float length_rect{ f_ptr_obj_rect->getLength() };
	float width_rect{ f_ptr_obj_rect->getWidth() };
	while (true)
	{
		float dx_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		float dy_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
		if ((x_rect + dx_rect + length_rect <= 1495) && (x_rect + dx_rect >= 710) && (y_rect + dy_rect + width_rect <= 895) && (y_rect + dy_rect >= 100))
		{
			f_ptr_obj_rect->MoveTo(dx_rect, dy_rect);
			break;
		}
	}
}

/*ФУНКЦИИ ДЛЯ ОБРАБОТКИ МАССИВА ПРЯМОУГОЛЬНИКОВ*/
//Добавить элемент в конец и удалить последний элемент - шаблонные функции
//Сдвинуть элементы случайным образом по x и по y из диапазона [-50;50]
void doOffsetArrayRectangles(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		float x_rect{ array_rectangles[i]->getXPoint() };
		float y_rect{ array_rectangles[i]->getYPoint() };
		float width_rect{ array_rectangles[i]->getWidth() };
		float length_rect{ array_rectangles[i]->getLength() };
		while (true)
		{
			float dx_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			float dy_rect{ getRandomNumber(OFFSET_NEGATIVE, OFFCET_POSITIVE) };
			if ((x_rect + dx_rect + length_rect <= 1495) && (x_rect + dx_rect >= 710) && (y_rect + dy_rect + width_rect <= 895) && (y_rect + dy_rect >= 100))
			{
				array_rectangles[i]->MoveTo(dx_rect, dy_rect);
				break;
			}
		}
	}
}
//Движение по клавишам WASD элементов
void doUserMoveArrayRectanglesW(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->getYPoint() - 10 >= 100)
			array_rectangles[i]->MoveTo(0, -10);
	}
}
void doUserMoveArrayRectanglesA(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->getXPoint() - 10 >= 710)
			array_rectangles[i]->MoveTo(-10, 0);
	}
}
void doUserMoveArrayRectanglesS(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->getYPoint() + array_rectangles[i]->getWidth() + 10 <= 895)
			array_rectangles[i]->MoveTo(0, 10);
	}
}
void doUserMoveArrayRectanglesD(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->getXPoint() + array_rectangles[i]->getLength() + 10 <= 1495)
			array_rectangles[i]->MoveTo(10, 0);
	}
}
//Изменение размеров элементов
void array_rectangles_ChangeDimensions(TRectangle** array_rectangles, int array_rectangles_size, int dLength, int dWidth)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if ((array_rectangles[i]->getXPoint() + array_rectangles[i]->getLength() + dLength <= 1495) && dLength > 0 && dWidth == 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		else if ((array_rectangles[i]->getLength() >= 50) && dLength < 0 && dWidth == 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		if ((array_rectangles[i]->getYPoint() + array_rectangles[i]->getWidth() + dWidth <= 895) && dLength == 0 && dWidth > 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}

		else if (array_rectangles[i]->getWidth() >= 25 && dLength == 0 && dWidth < 0)
		{
			array_rectangles[i]->changeDimensions(dLength, dWidth);
		}
	}
}
//Поворт элементов 
void doRotateArrayRects(TRectangle** array_rectangles, int array_rectangles_size)
{
	for (int i{}; i < array_rectangles_size; i++)
	{
		if (array_rectangles[i]->getLength() > array_rectangles[i]->getWidth())
		{
			if ((array_rectangles[i]->getYPoint() - (array_rectangles[i]->getLength() - array_rectangles[i]->getWidth()) / 2 >= 100)
				&& (array_rectangles[i]->getYPoint() - (array_rectangles[i]->getLength() - array_rectangles[i]->getWidth()) / 2 + array_rectangles[i]->getLength() <= 895))
				array_rectangles[i]->rotateRect();
		}
		else
		{
			if ((array_rectangles[i]->getXPoint() - (array_rectangles[i]->getWidth() - array_rectangles[i]->getLength()) / 2 >= 710)
				&& (array_rectangles[i]->getXPoint() - (array_rectangles[i]->getWidth() - array_rectangles[i]->getLength()) / 2 + array_rectangles[i]->getWidth() <= 1495))
				array_rectangles[i]->rotateRect();
		}
	}
}