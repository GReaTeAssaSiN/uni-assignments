#ifndef CLASS_RHOMB_H_
#define CLASS_RHOMB_H_

#include "class_TQuadrilateral.h"

class TRhomb :public TQuadrilateral
{
private:
	float m_length{100};
	int m_degree{60};

private:
	void BalanceSides();

public:
	TRhomb();

	TRhomb(float base_point_x1, float base_point_y1, float length, int degree);

	void Show(sf::RenderWindow& window) override;

	void MoveTo(float dx_coordinate_base_point, float dy_coordinate_base_point) override;

	void Free(TRhomb*& ptr_obj_rhomb);

	float getLength();

	int getDegree();

	void changeLength(int dLength);

	void changeDegree(int dDegree);

	/*~TRhomb();*/
};

#endif /* CLASS_RHOMB_H_ */