#ifndef CLASS_LINESEGMENT_H_
#define CLASS_LINESEGMENT_H_

#include "class_point2D.h"
#include "constants.h"

class Linesegment
{
private:
	Point2D m_auxiliary_base_point_of_line{};
	float m_length{ 200.0f };
	const float m_width{ 2.0f };
	int m_red{}, m_green{}, m_blue{};
	float m_degree{};
	int m_visibility{ 255 };

	sf::RectangleShape m_shape_linesegment{};

public:
	Linesegment()
	{
		std::cout << "—оздан конструктором по умолчанию объект-лини€ с координатами базовой точки (крайн€€ лева€ точка):\n(" <<
			m_auxiliary_base_point_of_line.getXPoint() << " ," << m_auxiliary_base_point_of_line.getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
			"\tDegree = " << m_degree << std::endl;
	}

	Linesegment(Point2D auxiliary_base_point_of_line, float length, float degree)
		: m_auxiliary_base_point_of_line{auxiliary_base_point_of_line}, m_length{length}, m_degree{degree} 
	{
		if (m_degree >= 0 && m_degree <= 90)
		{
			while ((m_auxiliary_base_point_of_line.getXPoint() + m_length * cos(m_degree * PI / 180) > 1500) ||
				(m_auxiliary_base_point_of_line.getYPoint() + m_length * sin(m_degree * PI / 180) > 900))
			{
				m_length--;
			}
		}
		else if (m_degree >= 90 && m_degree <= 180)
		{
			while ((m_auxiliary_base_point_of_line.getXPoint() + m_length * cos(m_degree * PI / 180) < 705) ||
				(m_auxiliary_base_point_of_line.getYPoint() + m_length * sin(m_degree * PI / 180) > 900))
			{
				m_length--;
			}
		}
		else if (m_degree >= 180 && m_degree <= 270)
		{
			while ((m_auxiliary_base_point_of_line.getXPoint() + m_length * cos(m_degree * PI / 180) < 705) ||
				(m_auxiliary_base_point_of_line.getYPoint() + m_length * sin(m_degree * PI / 180) < 95))
			{
				m_length--;
			}
		}
		else if (m_degree >= 270 && m_degree <= 360)
		{
			while ((m_auxiliary_base_point_of_line.getXPoint() + m_length * cos(m_degree * PI / 180) > 1500) ||
				(m_auxiliary_base_point_of_line.getYPoint() + m_length * sin(m_degree * PI / 180) < 95))
			{
				m_length--;
			}
		}

		std::cout << "—оздан конструктором со случайными параметрами объект-лини€ с координатами базовой точки (крайн€€ лева€ точка):\n(" <<
			m_auxiliary_base_point_of_line.getXPoint() << " ," << m_auxiliary_base_point_of_line.getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
			"\tDegree = " << m_degree << std::endl;
	}

	void Show(sf::RenderWindow& window)
	{
		m_shape_linesegment.setSize(sf::Vector2f(m_length, m_width));
		m_shape_linesegment.setOutlineColor(sf::Color::Black);
		m_shape_linesegment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_linesegment.setPosition(m_auxiliary_base_point_of_line.getXPoint(), m_auxiliary_base_point_of_line.getYPoint());
		m_shape_linesegment.setRotation(m_degree);
		window.draw(m_shape_linesegment);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_auxiliary_base_point_of_line.setXPoint(m_auxiliary_base_point_of_line.getXPoint() + dx_coordinate_base_point);
		m_auxiliary_base_point_of_line.setYPoint(m_auxiliary_base_point_of_line.getYPoint() + dy_coordinate_base_point);
	}

	void Free(Linesegment*& ptr_obj_linesegment)
	{
		delete ptr_obj_linesegment;
		ptr_obj_linesegment = nullptr;
	}

	void changeLength(float dLength)
	{
		m_length += dLength;
	}

	void changeDegree(float dDegree)
	{
		m_degree += dDegree;
	}

	float get_x_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_line.getXPoint();
	}

	float get_y_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_line.getYPoint();
	}

	float getLength()
	{
		return m_length;
	}

	float getDegree()
	{
		return m_degree;
	}

	void setVisibility(int visibility)
	{
		m_visibility = visibility;
	}

	void setColor(int red, int green, int blue)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;
	}

	/*~Linesegment() 
	{
		std::cout << "”дален объект-лини€ с координатами базовой точки (крайн€€ лева€ точка):\n(" <<
			m_auxiliary_base_point_of_line.getXPoint() << " ," << m_auxiliary_base_point_of_line.getYPoint() << " )\nи параметрами: Lenght = " << m_length <<
			"\tDegree = " << m_degree << std::endl;
	};*/
};

#endif /* CLASS_LINESEGMENT_H_ */
