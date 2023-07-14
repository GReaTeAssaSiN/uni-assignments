#ifndef CLASS_TLINESEGMENT_H_
#define CLASS_TLINESEGMENT_H_

#include "class_TFigure.h"
#include "constants.h"

class TLinesegment : public TFigure
{
private:
	float m_length{ 200.0f };
	const float m_width{ 2.0f };
	float m_degree{};

public:
	TLinesegment();

	TLinesegment(float x_point, float y_point, float length, float degree);

	void Show(sf::RenderWindow& window) override;

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point) override;

	void Free(TLinesegment*& ptr_obj_linesegment);

	void changeLength(float dLength);

	void changeDegree(float dDegree);

	float getLength();

	float getDegree();

	/*~TLinesegment();*/
};

#endif /* CLASS_TLINESEGMENT_H_ */