#ifndef CLASS_RECTANGLE_H_
#define CLASS_RECTANGLE_H_

#include "class_point2D.h"

class Rectangle
{
private:
	Point2D m_auxiliary_base_point_of_rect{};
	float m_length{ 200.0f };
	float m_width{ 100.0f };
	const float m_outline_thikness{ 5.0f };
	int m_red{ 126 }, m_green{ 300 }, m_blue{ 105 };
	int m_out_red{}, m_out_green{}, m_out_blue{};
	int m_visibility{ 255 };

	sf::RectangleShape m_shape_rect{};

public:
	Rectangle()
	{
		std::cout << "Создан конструктором по умолчанию объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" << 
			m_auxiliary_base_point_of_rect.getXPoint() << ", " << m_auxiliary_base_point_of_rect.getYPoint() << ")\nи размерами: Lenght = " << m_length << 
			",\tWidth = " << m_width << std::endl;
	}

	Rectangle(Point2D auxiliary_base_point_of_rect, float length, float width)
		: m_auxiliary_base_point_of_rect{auxiliary_base_point_of_rect}, m_length{length}, m_width{width} 
	{
		while (m_auxiliary_base_point_of_rect.getXPoint() + m_length > 1495)
			m_length--;
		while (m_auxiliary_base_point_of_rect.getYPoint() + m_width > 895)
			m_width--;

		std::cout << "Создан конструктором со случайными параметрами объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" <<
			m_auxiliary_base_point_of_rect.getXPoint() << ", " << m_auxiliary_base_point_of_rect.getYPoint() << ")\nи размерами: Lenght = " << m_length <<
			",\tWidth = " << m_width << std::endl;
	}

	void Show(sf::RenderWindow& window)
	{
		m_shape_rect.setSize(sf::Vector2f(m_length, m_width));
		m_shape_rect.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
		m_shape_rect.setOutlineThickness(m_outline_thikness);
		m_shape_rect.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_rect.setPosition(m_auxiliary_base_point_of_rect.getXPoint(), m_auxiliary_base_point_of_rect.getYPoint());
		window.draw(m_shape_rect);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_auxiliary_base_point_of_rect.setXPoint(m_auxiliary_base_point_of_rect.getXPoint() + dx_coordinate_base_point);
		m_auxiliary_base_point_of_rect.setYPoint(m_auxiliary_base_point_of_rect.getYPoint() + dy_coordinate_base_point);
	}

	void Free(Rectangle*& ptr_obj_rect)
	{
		delete ptr_obj_rect;
		ptr_obj_rect = nullptr;
	}

	void changeDimensions(int dLength, int dWidth)
	{
		m_length += dLength;
		m_width += dWidth;
	}

	float get_x_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_rect.getXPoint();
	}

	float get_y_coordinate_base_point()
	{
		return m_auxiliary_base_point_of_rect.getYPoint();
	}

	float getLength()
	{
		return m_length;
	}

	float getWidth()
	{
		return m_width;
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

	void setOutColor(int out_red, int out_green, int out_blue)
	{
		m_out_red = out_red;
		m_out_green = out_green;
		m_out_blue = out_blue;
	}

	/*~Rectangle() 
	{
		std::cout << "Удален объект-прямоугольник с координатами базовой точки (верхний левый угол):\n(" <<
			m_auxiliary_base_point_of_rect.getXPoint() << ", " << m_auxiliary_base_point_of_rect.getYPoint() << ")\nи размерами: Lenght = " << m_length <<
			",\tWidth = " << m_width << std::endl;
	};*/
};

#endif /* CLASS_RECTANGLE_H_ */