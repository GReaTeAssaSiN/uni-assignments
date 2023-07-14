#ifndef class_TFIGURE_H_
#define class_TFIGURE_H_

#include "SFML/Graphics.hpp"
#include <iostream>

class TFigure
{
private:
	float m_base_point_x{ 810.f };
	float m_base_point_y{ 200.f };

protected:
	const float m_outline_thikness{ 5.0f };
	int m_red{ 126 }, m_green{ 209 }, m_blue{ 105 };
	int m_out_red{}, m_out_green{}, m_out_blue{};
	int m_visibility{ 255 };

public:
	TFigure();

	TFigure(float x_point, float y_point);

	virtual void Show(sf::RenderWindow& window) = 0;
	virtual void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point) = 0;

	float getXPoint();

	float getYPoint();

	void setXPoint(float x_point);

	void setYPoint(float y_point);

	void setFillColor(int red, int green, int blue);

	void setOutColor(int out_red, int out_green, int out_blue);

	void setVisibility(int visibility);

	/*~TFigure();*/
};

#endif /* CLASS_TFIGURE_H_ */