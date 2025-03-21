#include "class_TQuadrilateral.h"

TQuadrilateral::TQuadrilateral()
	:TFigure()
{
	std::cout << "Создан конструктором по умолчанию объект-четырёхугольник с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")" << std::endl;
}
TQuadrilateral::TQuadrilateral(float base_point_x1, float base_point_y1, float base_point_x2, float base_point_y2, float base_point_x3, float base_point_y3, float base_point_x4, float base_point_y4)
	: TFigure{ base_point_x1, base_point_y1 }, m_base_point_x2{ base_point_x2 }, m_base_point_y2{ base_point_y2 }, m_base_point_x3{ base_point_x3 }, m_base_point_y3{ base_point_y3 },
	m_base_point_x4{ base_point_x4 }, m_base_point_y4{ base_point_y4 }
{
	std::cout << "Создан конструктором cо случайными параметрами объект-четырёхугольник с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")" << std::endl;
}

void TQuadrilateral::Show(sf::RenderWindow& window)
{
	sf::ConvexShape quadrilateral{};
	quadrilateral.setPointCount(4);
	quadrilateral.setPoint(0, sf::Vector2f(getXPoint(), getYPoint()));
	quadrilateral.setPoint(1, sf::Vector2f(m_base_point_x2, m_base_point_y2));
	quadrilateral.setPoint(2, sf::Vector2f(m_base_point_x3, m_base_point_y3));
	quadrilateral.setPoint(3, sf::Vector2f(m_base_point_x4, m_base_point_y4));
	quadrilateral.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	quadrilateral.setOutlineThickness(m_outline_thikness);
	quadrilateral.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	window.draw(quadrilateral);
}

void TQuadrilateral::changeBasePoints234(float change_coordinate_x, float change_coordinate_y)
{
	m_base_point_x2 += change_coordinate_x;
	m_base_point_y2 += change_coordinate_y;
	m_base_point_x3 += change_coordinate_x;
	m_base_point_y3 += change_coordinate_y;
	m_base_point_x4 += change_coordinate_x;
	m_base_point_y4 += change_coordinate_y;
}

void TQuadrilateral::Free(TQuadrilateral*& ptr_obj_quadrilateral)
{
	delete ptr_obj_quadrilateral;
	ptr_obj_quadrilateral = nullptr;
}

void TQuadrilateral::changeSize(float dSize)
{
	setXPoint(getXPoint() - dSize); setYPoint(getYPoint() - dSize);
	m_base_point_x2 += dSize; m_base_point_y2 -= dSize;
	m_base_point_x3 += dSize; m_base_point_y3 += dSize;
	m_base_point_x4 -= dSize; m_base_point_y4 += dSize;
}

float TQuadrilateral::getX2Point()
{
	return m_base_point_x2;
}

float TQuadrilateral::getX3Point()
{
	return m_base_point_x3;
}

float TQuadrilateral::getX4Point()
{
	return m_base_point_x4;
}

float TQuadrilateral::getY2Point()
{
	return m_base_point_y2;
}

float TQuadrilateral::getY3Point()
{
	return m_base_point_y3;
}

float TQuadrilateral::getY4Point()
{
	return m_base_point_y4;
}

//TQuadrilateral::~TQuadrilateral()
//{
//	std::cout << "Удален объект-четырёхугольник с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
//		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4 << ")" << std::endl;
//}