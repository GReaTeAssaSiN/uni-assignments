#ifndef CLASS_CIRCLE_H_
#define CLASS_CIRCLE_H_

class Circle
{
private:
	float m_x_coordinate_base_point{810.0f};
	float m_y_coordinate_base_point{200.0f};
	float m_radius{50.0f};
	const float m_outline_thikness{ 5.0f };
	int m_red{126}, m_green{209}, m_blue{105};
	int m_out_red{}, m_out_green{}, m_out_blue{};
	int m_visibility{255};

	sf::CircleShape m_shape_circle{};

public:
	Circle() = default;

	Circle(float x_coordinate_base_point, float y_coordinate_base_point, float radius) 
		: m_x_coordinate_base_point{ x_coordinate_base_point }, m_y_coordinate_base_point{ y_coordinate_base_point }, m_radius{ radius } {}

	void Show(sf::RenderWindow& window)
	{
		m_shape_circle.setRadius(m_radius);
		m_shape_circle.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
		m_shape_circle.setOutlineThickness(m_outline_thikness);
		m_shape_circle.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_circle.setPosition(m_x_coordinate_base_point - m_radius, m_y_coordinate_base_point - m_radius);
		window.draw(m_shape_circle);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_x_coordinate_base_point += dx_coordinate_base_point;
		m_y_coordinate_base_point += dy_coordinate_base_point;
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
		return m_x_coordinate_base_point;
	}

	float get_y_coordinate_base_point()
	{
		return m_y_coordinate_base_point;
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


	~Circle() {};
};

#endif /* CLASS_CIRCLE_H_ */