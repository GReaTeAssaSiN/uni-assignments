#ifndef USER_BUTTONS_H_
#define USER_BUTTONS_H_

class User_texts
{
private:
	const float m_x{}, m_y{};
	const int m_size{};
	int m_red{}, m_green{}, m_blue{};

	sf::Font m_font;
	sf::Text m_text;
	sf::String m_str_font{};
	const sf::String m_str_text{};

public:
	User_texts(sf::String str_font, sf::String str_text, float x, float y, int size)
		: m_x{ x }, m_y{ y }, m_size{ size }, m_str_text{ str_text }
	{
		m_str_font = str_font;
		m_font.loadFromFile("fonts/" + m_str_font);
		m_text.setFont(m_font);
		m_text.setString(m_str_text);
		m_text.setCharacterSize(m_size);
		m_text.setFillColor(sf::Color(m_red, m_green, m_blue));
		m_text.setStyle(sf::Text::Bold);
		m_text.setPosition(m_x, m_y);
	}

	void Show(sf::RenderWindow& window)
	{
		window.draw(m_text);
	}

	void m_setDefaultColor()
	{
		m_text.setFillColor(sf::Color::Black);
	}

	void m_setActiveColor()
	{
		m_red = 40;
		m_green = 50;
		m_blue = 160;
		m_text.setFillColor(sf::Color(m_red, m_green, m_blue));
	}

	void m_setFillColor(int red, int green, int blue)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;
		m_text.setFillColor(sf::Color(red, green, blue));
	}
};

class Rect_BG_buttons
{
private:
	const float m_x{}, m_y{};
	const int m_rect_width{}, m_rect_height{};
	const float m_outline_thikness{};
	int m_red{ 134 }, m_green{ 13 }, m_blue{ 52 };
	int m_rect_red{}, m_rect_green{}, m_rect_blue{};

	sf::RectangleShape m_shape_rect;

public:
	Rect_BG_buttons(float x, float y, int rect_width, int rect_height, float outline_thikness)
		: m_x{ x }, m_y{ y }, m_rect_width(rect_width), m_rect_height(rect_height), m_outline_thikness{ outline_thikness }
	{
		m_shape_rect.setSize(sf::Vector2f(m_rect_width, m_rect_height));
		m_shape_rect.setFillColor(sf::Color(m_red, m_green, m_blue));
		m_shape_rect.setOutlineThickness(m_outline_thikness);
		m_shape_rect.setOutlineColor(sf::Color::Black);
		m_shape_rect.setPosition(m_x, m_y);
	}

	void Show(sf::RenderWindow& window)
	{
		window.draw(m_shape_rect);
	}

	void m_setFillColor(int red, int green, int blue)
	{
		m_red = red, m_green = green, m_blue = blue;
		m_shape_rect.setFillColor(sf::Color(red, green, blue));
	}

	void m_setDefaultColor()
	{
		m_shape_rect.setFillColor(sf::Color(153, 217, 234));
	}

	void m_setActiveColor()
	{
		m_red = 0;
		m_green = 162;
		m_blue = 232;
		m_shape_rect.setFillColor(sf::Color(m_red, m_green, m_blue));
	}

	void m_setOutlineColor(int rect_red, int rect_green, int rect_blue)
	{
		m_rect_red = rect_red, m_rect_green = rect_green, m_rect_blue = rect_blue;
		m_shape_rect.setOutlineColor(sf::Color(rect_red, rect_green, rect_blue));
	}
};

#endif /* USER_BUTTONS_H_ */