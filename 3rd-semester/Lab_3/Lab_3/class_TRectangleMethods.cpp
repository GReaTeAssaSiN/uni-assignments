#include "class_TRectangle.h"

void TRectangle::BalanceSides()
{
	m_base_point_x2 = getXPoint() + m_length; m_base_point_y2 = getYPoint();
	m_base_point_x3 = getXPoint() + m_length; m_base_point_y3 = getYPoint() + m_width;
	m_base_point_x4 = getXPoint(); m_base_point_y4 = getYPoint() + m_width;
}

TRectangle::TRectangle()
	: TQuadrilateral()
{
	BalanceSides();
	std::cout << "Создан конструктором по умолчанию объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" <<
		getXPoint() << ", " << getYPoint() << ")\n(остальные координаты основных точек прямоугольника изменены)\nи размерами: Lenght = " << m_length <<
		",\tWidth = " << m_width << std::endl;
}

TRectangle::TRectangle(float x_point, float y_point, float length, float width)
	: TQuadrilateral{ x_point, y_point, x_point + length, y_point, x_point + length, y_point + width, x_point, y_point + width }, m_length{ length }, m_width{ width }
{
	while (getXPoint() + m_length > 1495)
		m_length--;
	while (getYPoint() + m_width > 895)
		m_width--;
	
	BalanceSides();
	std::cout << "Создан конструктором со случайными параметрами объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" <<
		getXPoint() << ", " << getYPoint() << ")\nи размерами: Lenght = " << m_length <<
		",\tWidth = " << m_width << std::endl;
}

void TRectangle::Show(sf::RenderWindow& window)
{
	TQuadrilateral::Show(window);
}

void TRectangle::MoveTo(float dx_coordinate, float dy_coordinate)
{
	TQuadrilateral::MoveTo(dx_coordinate, dy_coordinate);
}

void TRectangle::Free(TRectangle*& ptr_obj_rect)
{
	delete ptr_obj_rect;
	ptr_obj_rect = nullptr;
}

void TRectangle::changeDimensions(int dLength, int dWidth)
{
	m_length += dLength;
	m_width += dWidth;
	BalanceSides();
}

void TRectangle::rotateRect()
{
	if (m_length > m_width)
	{
		setXPoint(getXPoint() + (m_length - m_width) / 2);
		setYPoint(getYPoint() - (m_length - m_width) / 2);
	}
	else
	{
		setXPoint(getXPoint() - (m_width - m_length) / 2);
		setYPoint(getYPoint() + (m_width - m_length) / 2);
	}
	float temp{ m_width };
	m_width = m_length;
	m_length = temp;
	BalanceSides();
}

float TRectangle::getLength()
{
	return m_length;
}

float TRectangle::getWidth()
{
	return m_width;
}

//TRectangle::~TRectangle()
//{
//	std::cout << "Удален объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" <<
//		getXPoint() << ", " << getYPoint() << ")\nи размерами: Lenght = " << m_length <<
//		",\tWidth = " << m_width << std::endl;
//};