#include "class_TCircle.h"

TCircle::TCircle()
	:TFigure{}
{
	std::cout << "Создан конструктором по умолчанию объект-круг с координатами центра:\n(" << getXPoint() << ", " <<
		getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
}

TCircle::TCircle(float x_point, float y_point, float radius)
	: TFigure{ x_point, y_point }, m_radius{ radius }
{
	while ((getXPoint() + m_radius > 1495) || (getXPoint() - m_radius < 710) || (getYPoint() + m_radius > 895) || (getYPoint() - m_radius < 100))
	{
		m_radius--;
	}

	std::cout << "Создан конструктором со случайными параметрами объект-круг с координатами центра:\n(" <<
		getXPoint() << ", " << getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
}

void TCircle::Show(sf::RenderWindow& window)
{
	sf::CircleShape m_shape_circle{};
	m_shape_circle.setRadius(m_radius);
	m_shape_circle.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	m_shape_circle.setOutlineThickness(m_outline_thikness);
	m_shape_circle.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	m_shape_circle.setPosition(getXPoint() - m_radius, getYPoint() - m_radius);
	window.draw(m_shape_circle);
}

void TCircle::Free(TFigure*& ptr_obj_circle)
{
	delete ptr_obj_circle;
	ptr_obj_circle = nullptr;
}

void TCircle::changeRadius(float dx_radius)
{
	m_radius += dx_radius;
}

float TCircle::getRadius()
{
	return m_radius;
}

//TCircle::~TCircle()
//{
//	std::cout << "Удален объект-круг с координатами центра:\n(" <<getXPoint() << ", " <<
//		getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
//};