#include "class_TLinesegment.h"

TLinesegment::TLinesegment()
	:TFigure()
{
	std::cout << "Создан конструктором по умолчанию объект-линия с координатами базовой точки (крайняя левая точка):\n(" <<
		getXPoint() << " ," << getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
		"\tDegree = " << m_degree << std::endl;
}

TLinesegment::TLinesegment(float x_point, float y_point, float length, float degree)
	: TFigure{ x_point, y_point }, m_length{ length }, m_degree{ degree }
{
	if (m_degree >= 0 && m_degree <= 90)
	{
		while ((getXPoint() + m_length * cos(m_degree * PI / 180) > 1495) ||
			(getYPoint() + m_length * sin(m_degree * PI / 180) > 895))
		{
			m_length--;
		}
	}
	else if (m_degree >= 90 && m_degree <= 180)
	{
		while ((getXPoint() + m_length * cos(m_degree * PI / 180) < 710) ||
			(getYPoint() + m_length * sin(m_degree * PI / 180) > 895))
		{
			m_length--;
		}
	}
	else if (m_degree >= 180 && m_degree <= 270)
	{
		while ((getXPoint() + m_length * cos(m_degree * PI / 180) < 710) ||
			(getYPoint() + m_length * sin(m_degree * PI / 180) < 100))
		{
			m_length--;
		}
	}
	else if (m_degree >= 270 && m_degree <= 360)
	{
		while ((getXPoint() + m_length * cos(m_degree * PI / 180) > 1495) ||
			(getYPoint() + m_length * sin(m_degree * PI / 180) < 100))
		{
			m_length--;
		}
	}

	std::cout << "Создан конструктором со случайными параметрами объект-линия с координатами базовой точки (крайняя левая точка):\n(" <<
		getXPoint() << " ," << getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
		"\tDegree = " << m_degree << std::endl;
}

void TLinesegment::Show(sf::RenderWindow& window)
{
	sf::RectangleShape m_shape_linesegment{};
	m_shape_linesegment.setSize(sf::Vector2f(m_length, m_width));
	m_shape_linesegment.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	m_shape_linesegment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	m_shape_linesegment.setPosition(getXPoint(), getYPoint());
	m_shape_linesegment.setRotation(m_degree);
	window.draw(m_shape_linesegment);
}

void TLinesegment::Free(TLinesegment*& ptr_obj_linesegment)
{
	delete ptr_obj_linesegment;
	ptr_obj_linesegment = nullptr;
}

void TLinesegment::changeLength(float dLength)
{
	m_length += dLength;
}

void TLinesegment::changeDegree(float dDegree)
{
	m_degree += dDegree;
}

float TLinesegment::getLength()
{
	return m_length;
}

float TLinesegment::getDegree()
{
	return m_degree;
}

//TLinesegment::~TLinesegment()
//{
//	std::cout << "Удален объект-линия с координатами базовой точки (крайняя левая точка):\n(" <<
//		getXPoint() << " ," << getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
//		"\tDegree = " << m_degree << std::endl;
//};