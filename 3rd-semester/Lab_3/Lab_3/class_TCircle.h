#ifndef CLASS_TCIRCLE_H_
#define CLASS_TCIRCLE_H_

#include "class_TFigure.h"

class TCircle : public TFigure
{
private:
	float m_radius{ 50.0f };

public:
	TCircle();

	TCircle(float x_point, float y_point, float radius);

	void Show(sf::RenderWindow& window) override;

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point) override;

	void Free(TCircle*& ptr_obj_circle);

	void changeRadius(float dx_radius);

	float getRadius();

	/*~TCircle();*/
};

#endif /* CLASS_TCIRCLE_H_ */