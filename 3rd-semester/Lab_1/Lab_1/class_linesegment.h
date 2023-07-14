#ifndef CLASS_LINESEGMENT_H_
#define CLASS_LINESEGMENT_H_

class Linesegment
{
private:
	float m_x_coordinate_base_point{ 1200.0f };
	float m_y_coordinate_base_point{ 170.0f };
	float m_length{ 200.0f };
	const float m_width{ 2.0f };
	int m_red{}, m_green{}, m_blue{};
	float m_degree{};
	int m_visibility{ 255 };

	sf::RectangleShape m_shape_linesegment{};

public:
	Linesegment() = default;

	Linesegment(float x_coordinate_base_point, float y_coordinate_base_point, float length, float degree)
		: m_x_coordinate_base_point{ x_coordinate_base_point }, m_y_coordinate_base_point{ y_coordinate_base_point }, m_length{ length }, m_degree{ degree } {}

	void Show(sf::RenderWindow& window)
	{
		m_shape_linesegment.setSize(sf::Vector2f(m_length, m_width));
		m_shape_linesegment.setOutlineColor(sf::Color::Black);
		m_shape_linesegment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
		m_shape_linesegment.setPosition(m_x_coordinate_base_point, m_y_coordinate_base_point);
		m_shape_linesegment.setRotation(m_degree);
		window.draw(m_shape_linesegment);
	}

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point)
	{
		m_x_coordinate_base_point += dx_coordinate_base_point;
		m_y_coordinate_base_point += dy_coordinate_base_point;
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


	~Linesegment() {};
};

#endif /* CLASS_LINESEGMENT_H_ */
