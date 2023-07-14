#ifndef CLASS_TRECTANGLE_H_
#define CLASS_TRECTANGLE_H_

#include "class_TQuadrilateral.h"

class TRectangle : public TQuadrilateral
{
private:
	float m_length{ 200.0f };
	float m_width{ 100.0f };

private:
	void BalanceSides();

public:
	TRectangle();

	TRectangle(float x_point, float y_point, float length, float width);

	virtual void Show(sf::RenderWindow& window);

	void Free(TFigure*& ptr_obj_rect);

	void changeDimensions(int dLength, int dWidth);

	void rotateRect();

	float getLength();

	float getWidth();

	/*~TRectangle();*/
};

#endif /* CLASS_TRECTANGLE_H_ */