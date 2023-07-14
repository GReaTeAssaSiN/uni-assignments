#ifndef class_TELLIPSE_H_
#define class_TELLIPSE_H_

#include "class_TCircle.h"
#include "SFML_EllipseShape.h"

class TEllipse : public TCircle
{
private:
	float m_semi_minor_axis{25};

public:
	TEllipse();

	TEllipse(float x_point, float y_point, float semi_major_axis, float semi_minor_axis);

	void Show(sf::RenderWindow& window) override;

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point) override;

	void changeSemiMinorAxis(float d_semi_minor_axis);

	void rotateEllipse();

	void Free(TEllipse*& ptr_obj_ellipse);

	float getSemiMinorAxis();

	/*~TEllipse();*/
};

#endif /* class_TELLIPSE_H_*/