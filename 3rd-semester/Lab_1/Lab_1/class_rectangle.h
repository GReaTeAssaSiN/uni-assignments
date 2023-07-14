#ifndef CLASS_RECTANGLE_H_
#define CLASS_RECTANGLE_H_

class Rectangle
{
private:
	float m_x_coordinate_base_point{880.0f};
	float m_y_coordinate_base_point{150.0f};
	float m_length{200.0f};
	float m_width{100.0f};
	const float m_outline_thikness{ 5.0f };
	int m_red{126}, m_green{300}, m_blue{105};
	int m_out_red{}, m_out_green{}, m_out_blue{};
	int m_visibility{255};

	sf::RectangleShape m_shape_rect{};

public:
	Rectangle() = default;

	Rectangle(float x_coordinate_base_point, float y_coordinate_base_point, float length, float width)
		: m_x_coordinate_base_point{ x_coordinate_base_point }, m_y_coordinate_base_point{ y_coordinate_base_point }, m_length{ length }, m_width{ width } {}

	void Show(sf::RenderWindow& window)
	{
		m_shape_rect.setSize(sf::Vector2f(m_length, m_width));
		m_shape_rect.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
		m_shape_rect.setOutlineThickness(m_outline_thikness);
		m_shape_rect.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_rect.setPosition(m_x_coordinate_base_point, m_y_coordinate_base_point);
		window.draw(m_shape_rect);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_x_coordinate_base_point += dx_coordinate_base_point;
		m_y_coordinate_base_point += dy_coordinate_base_point;
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
		return m_x_coordinate_base_point;
	}

	float get_y_coordinate_base_point()
	{
		return m_y_coordinate_base_point;
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

	~Rectangle() {};
};

#endif /* CLASS_RECTANGLE_H_ */