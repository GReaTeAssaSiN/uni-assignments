#include "class_TTrapeze.h"
#include "constants.h"

void TTrapeze::BalanceSides()
{
	m_base_point_x2 = getXPoint() + m_height / tan(m_degree * PI / 180);
	m_base_point_y2 = getYPoint() - m_height;
	m_base_point_x3 = m_base_point_x2 + m_top_base_length;
	m_base_point_y3 = m_base_point_y2;
	m_base_point_x4 = getXPoint() + m_bottom_base_length;
	m_base_point_y4 = getYPoint();
}

TTrapeze::TTrapeze()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "Создан конструктором по умолчанию объект-трапеция с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4
		<< "),\nдлинами оснований: TopBase = " << m_top_base_length << ",\tBottomBase = " << m_bottom_base_length << "\nи углом между стороной и нижним основанием: Alpha = " << m_degree << std::endl;
}

TTrapeze::TTrapeze(float base_point_x1, float base_point_y1, int degree, float bottom_base_length, float top_base_length, float height)
	:TQuadrilateral{ base_point_x1, base_point_y1, base_point_x1 + height / tan(degree + PI / 180), base_point_y1 - height, base_point_x1 + height / tan(degree + PI / 180) + top_base_length,
		base_point_y1 - height, base_point_x1 + bottom_base_length, base_point_y1 }, m_degree{ degree }, m_bottom_base_length{ bottom_base_length }, m_top_base_length{ top_base_length }, m_height{ height }
{
	BalanceSides();
	std::cout << "Создан конструктором со случайными параметрами объект-трапеция с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4
		<< "),\nдлинами оснований: TopBase = " << m_top_base_length << ",\tBottomBase = " << m_bottom_base_length << "\nи углом между стороной и нижним основанием: Alpha = " << m_degree << std::endl;
}

void TTrapeze::Show(sf::RenderWindow& window)
{
	TQuadrilateral::Show(window);
}

void TTrapeze::Free(TFigure*& ptr_obj_trapeze)
{
	delete ptr_obj_trapeze;
	ptr_obj_trapeze = nullptr;
}

void TTrapeze::changeTopBase(float d_top_base)
{
	m_base_point_x3 += d_top_base;
}

void TTrapeze::changeBottomBase(float d_bottom_base)
{
	m_base_point_x4 += d_bottom_base;
}

void TTrapeze::changeHeight(float d_height)
{
	m_base_point_y2 += d_height;
	m_base_point_y3 = m_base_point_y2;
}

//TTrapeze::~TTrapeze()
//{
//	std::cout << "Удален объект-трапеция с координатами основных точек:\n1.(" << getXPoint() << ", " << getYPoint() << ")\n"
//		<< "2.(" << m_base_point_x2 << ", " << m_base_point_y2 << ")\n" << "3.(" << m_base_point_x3 << ", " << m_base_point_y3 << ")\n" << "4.(" << m_base_point_x4 << ", " << m_base_point_y4
//		<< "),\nдлинами оснований: TopBase = " << m_top_base_length << ",\tBottomBase = " << m_bottom_base_length << "\nи углом между стороной и нижним основанием: Alpha = " << m_degree << std::endl;
//}