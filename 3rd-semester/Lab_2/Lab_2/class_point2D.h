#ifndef CLASS_POINT2D_H_
#define CLASS_POINT2D_H_

#include <iostream>

class Point2D
{
private:
	float m_x_point{};
	float m_y_point{};
public:
	Point2D()
		:m_x_point{810.f}, m_y_point{200.f}
	{
		std::cout << "Создан конструктором по умолчанию объект-точка с координатами:\n(" << m_x_point << ", " << m_y_point << ")" << std::endl;
	}

	Point2D(float x_point, float y_point)
		: m_x_point{x_point}, m_y_point{y_point}
	{
		std::cout << "Создан конструктором со случайными параметрами объект-точка с координатами:\n(" << m_x_point << ", " << m_y_point << ")" << std::endl;
	}

	float getXPoint()
	{
		return m_x_point;
	}

	float getYPoint()
	{
		return m_y_point;
	}

	void setXPoint(float x_point)
	{
		m_x_point = x_point;
	}

	void setYPoint(float y_point)
	{
		m_y_point = y_point;
	}

	/*~Point2D()
	{
		std::cout << "Удален объект-точка с координатами:\n(" << m_x_point << ", " << m_y_point << ")" << std::endl << std::endl;
	}*/
};

#endif /* CLASS_POINT2D_H_ */