#include "class_TEllipse.h"

TEllipse::TEllipse()
	:TCircle{}
{
	std::cout << "Создан конструктором по умолчанию объект-эллипс (сплющенная окружность) с координатами центра:\n(" << getXPoint() << ", " <<
		getYPoint() << ")\nбольшой полуосью: semi_major_axis = " << getRadius() << ",\tи меньшей полуосью: semi_minor_axis = " << m_semi_minor_axis << std::endl;
}

TEllipse::TEllipse(float x_point, float y_point, float semi_major_axis, float semi_minor_axis)
	:TCircle(x_point, y_point, semi_major_axis), m_semi_minor_axis{ semi_minor_axis }
{
	if (m_semi_minor_axis > getRadius())
		while (m_semi_minor_axis >= getRadius())
		{
			m_semi_minor_axis--;
		}
	std::cout << "Создан конструктором со случайными параметрами объект-эллипс (сплющенная окружность) с координатами центра:\n(" << getXPoint() << ", " <<
		getYPoint() << ")\nбольшой полуосью: semi_major_axis = " << getRadius() << ",\tи меньшей полуосью: semi_minor_axis = " << m_semi_minor_axis << std::endl;
}

void TEllipse::Show(sf::RenderWindow& window)
{
	EllipseShape m_shape_ellipse{ {getRadius(), m_semi_minor_axis} };
	m_shape_ellipse.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	m_shape_ellipse.setOutlineThickness(m_outline_thikness);
	m_shape_ellipse.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	m_shape_ellipse.setPosition(getXPoint() - getRadius(), getYPoint() - m_semi_minor_axis);
	window.draw(m_shape_ellipse);
}

void TEllipse::changeSemiMinorAxis(float d_semi_minor_axis)
{
	m_semi_minor_axis += d_semi_minor_axis;
}

void TEllipse::rotateEllipse()
{
	float temp{ getRadius() };
	changeRadius(-getRadius() + m_semi_minor_axis);
	m_semi_minor_axis = temp;
}

void TEllipse::Free(TEllipse*& ptr_obj_ellipse)
{
	delete ptr_obj_ellipse;
	ptr_obj_ellipse = nullptr;
}

float TEllipse::getSemiMinorAxis()
{
	return m_semi_minor_axis;
}

/*TEllipse::~TEllipse()
{
	std::cout << "Удален объект-эллипс с координатами центра:\n(" << getXPoint() << ", " <<
		getYPoint() << ")\nбольшой полуосью: semi_major_axis = " << getRadius() << ",\tи меньшей полуосью: semi_minor_axis = " << m_semi_minor_axis << std::endl;
}*/