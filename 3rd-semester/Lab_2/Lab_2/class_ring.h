#ifndef CLASS_RING
#define CLASS_RING

#include "class_circle.h"

class Ring
{
private:
	Circle circle_outer{};
	Circle circle_inner{};

public:
	Ring()
	{
		while (circle_outer.getRadius() - circle_inner.getRadius() <= 10)
			circle_inner.changeRadius(-1);
		
		circle_inner.setFillColor(67, 136, 169);

		std::cout << "Создан конструктором по умолчанию объект-кольцо с координатами центра:\n(" << circle_inner.get_x_coordinate_base_point() << ", " <<
			circle_inner.get_y_coordinate_base_point() << ")\nи радиусами внутрн. и внешнего кругов: RadiusInner = " << circle_inner.getRadius() << 
			"\t" << "RadiusOuter = " << circle_outer.getRadius() << std::endl;
	}

	Ring(const Circle& user_circle_outer, const Circle& user_circle_inner)
		: circle_outer{ user_circle_outer }, circle_inner{user_circle_inner}
	{
		if (circle_outer.getRadius() - circle_inner.getRadius() <= 1)
			circle_inner.changeRadius(-20);

		std::cout << "Создан конструктором со случайными параметрами объект-кольцо с координатами центра:\n(" << circle_inner.get_x_coordinate_base_point() << ", " <<
			circle_inner.get_y_coordinate_base_point() << ")\nи радиусами внутрн. и внешнего кругов: RadiusInner = " << circle_inner.getRadius() <<
			"\t" << "RadiusOuter = " << circle_outer.getRadius() << std::endl;
	}

	void Show(sf::RenderWindow& window)
	{
		circle_outer.Show(window);
		circle_inner.Show(window);
	}

	void MoveTo(float dx, float dy)
	{
		circle_outer.MoveTo(dx, dy);
		circle_inner.MoveTo(dx, dy);
	}

	Circle& getCircleInner()
	{
		return circle_inner;
	}

	Circle& getCircleOuter()
	{
		return circle_outer;
	}

	/*~Ring()
	{
		std::cout << "Удален объект-кольцо с координатами центра:\n(" << circle_inner.get_x_coordinate_base_point() << ", " <<
			circle_inner.get_y_coordinate_base_point() << ")\nи радиусами внутрн. и внешнего кругов: RadiusInner = " << circle_inner.getRadius() << 
			"\t" << "RadiusOuter = " << circle_outer.getRadius() << std::endl;
	};*/
};

#endif /* CLASS_RING */