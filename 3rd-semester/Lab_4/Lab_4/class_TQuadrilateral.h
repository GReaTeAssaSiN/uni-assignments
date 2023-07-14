#ifndef CLASS_TQUANDRILATERAL_H_
#define CLASS_TQUANDRILATERAL_H_

#include "class_TFigure.h"

class TQuadrilateral :public TFigure
{
protected:
	float m_base_point_x2{ 840 }, m_base_point_x3{ 880 }, m_base_point_x4{ 800 },
		m_base_point_y2{ 220 }, m_base_point_y3{ 320 }, m_base_point_y4{ 360 };

public:
	TQuadrilateral();

	TQuadrilateral(float base_point_x1, float base_point_y1, float base_point_x2, float base_point_y2, float base_point_x3, float base_point_y3, float base_point_x4, float base_point_y4);

	virtual void Show(sf::RenderWindow& window);

	void changeBasePoints234(float change_coordinate_x, float change_coordinate_y);

	void Free(TQuadrilateral*& ptr_obj_quadrilateral);

	void changeSize(float dSize);

	float getX2Point();
	float getX3Point();
	float getX4Point();
	float getY2Point();
	float getY3Point();
	float getY4Point();

	/*~TQuadrilateral();*/
};

#endif /* CLASS_TQUANDRILATERAL_H_*/