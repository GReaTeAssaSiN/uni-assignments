#ifndef CLASS_TTRAPEZE_H_
#define CLASS_TTRAPEZE_H_

#include "class_TQuadrilateral.h"

class TTrapeze :public TQuadrilateral
{
private:
	float m_bottom_base_length{ 200 };
	float m_top_base_length{ 100 };
	float m_height{ 80 };
	int m_degree{ 50 };

private:
	void BalanceSides();

public:
	TTrapeze();

	TTrapeze(float base_point_x1, float base_point_y1, int degree, float bottom_base_length, float top_base_lengthm, float height);

	virtual void Show(sf::RenderWindow& window);

	void Free(TFigure*& ptr_obj_trapeze);

	void changeTopBase(float d_top_base);

	void changeBottomBase(float d_bottom_base);

	void changeHeight(float d_height);

	/*~TTrapeze();*/
};

#endif /* CLASS_TTRAPEZE_H_*/