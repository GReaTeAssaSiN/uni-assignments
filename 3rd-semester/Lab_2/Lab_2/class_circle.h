#ifndef CLASS_CIRCLE_H_
#define CLASS_CIRCLE_H_

#include "class_point2D.h"

class Circle
{
private:
	Point2D m_auxiliary_base_point_of_circle{};
	float m_radius{ 50.0f };
	const float m_outline_thikness{ 5.0f };
	int m_red{ 126 }, m_green{ 209 }, m_blue{ 105 };
	int m_out_red{}, m_out_green{}, m_out_blue{};
	int m_visibility{ 255 };

	sf::CircleShape m_shape_circle{};

public:
	Circle()
	{
		std::cout << "Создан конструктором по умолчанию объект-окружность с координатами центра:\n(" << m_auxiliary_base_point_of_circle.getXPoint() << ", " <<
			m_auxiliary_base_point_of_circle.getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
	}

	Circle(Point2D auxiliary_base_point_of_circle, float radius)
		: m_auxiliary_base_point_of_circle{auxiliary_base_point_of_circle}, m_radius{radius}
	{
		while ((m_auxiliary_base_point_of_circle.getXPoint() + m_radius > 1495) || (m_auxiliary_base_point_of_circle.getXPoint() - m_radius < 710)
			|| (m_auxiliary_base_point_of_circle.getYPoint() + m_radius > 895) || (m_auxiliary_base_point_of_circle.getYPoint() - m_radius < 100))
		{
			m_radius--;
		}

		std::cout << "Создан конструктором со случайными параметрами объект-окружность с координатами центра:\n(" << 
			m_auxiliary_base_point_of_circle.getXPoint() << ", " << m_auxiliary_base_point_of_circle.getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
	}

	void Show(sf::RenderWindow& window)
	{
		m_shape_circle.setRadius(m_radius);
		m_shape_circle.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
		m_shape_circle.setOutlineThickness(m_outline_thikness);
		m_shape_circle.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_circle.setPosition(m_auxiliary_base_point_of_circle.getXPoint() - m_radius, m_auxiliary_base_point_of_circle.getYPoint() - m_radius);
		window.draw(m_shape_circle);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_auxiliary_base_point_of_circle.setXPoint(m_auxiliary_base_point_of_circle.getXPoint() + dx_coordinate_base_point);
		m_auxiliary_base_point_of_circle.setYPoint(m_auxiliary_base_point_of_circle.getYPoint() + dy_coordinate_base_point);
	}

	void Free(Circle*& ptr_obj_circle)
	{
		delete ptr_obj_circle;
		ptr_obj_circle = nullptr;
	}

	void changeRadius(int dx_radius)
	{
		m_radius += dx_radius;
	}

	float get_x_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_circle.getXPoint();
	}

	float get_y_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_circle.getYPoint();
	}

	float getRadius()
	{
		return m_radius;
	}

	void setOutColor(int out_red, int out_green, int out_blue)
	{
		m_out_red = out_red;
		m_out_green = out_green;
		m_out_blue = out_blue;
	}

	void setFillColor(int red, int green, int blue)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;
	}

	void setVisibility(int visibility)
	{
		m_visibility = visibility;
	}


	/*~Circle() 
	{
		std::cout << "Удален объект-окружность с координатами центра:\n(" << m_auxiliary_base_point_of_circle.getXPoint() << ", " <<
			m_auxiliary_base_point_of_circle.getYPoint() << ")\nи радиусом: Radius = " << m_radius << std::endl;
	};*/
};

#endif /* CLASS_CIRCLE_H_ */