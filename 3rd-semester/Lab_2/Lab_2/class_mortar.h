#ifndef CLASS_MORTAR_H_
#define CLASS_MORTAR_H_

#include "class_circle.h"
#include "class_rectangle.h"
#include "class_linesegment.h"

class Mortar
{
private:
	Rectangle rect_obj{};
	Circle circle_obj{};
	Linesegment line_obj{};
public:
	Mortar()
	{
		rect_obj.changeDimensions(-150, 50);
		circle_obj.changeRadius(-25);
		line_obj.changeDegree(270);
		line_obj.changeLength(-100);
		circle_obj.MoveTo(rect_obj.getLength() / 2, rect_obj.getWidth());
		line_obj.MoveTo(rect_obj.getLength() / 2, 0);
		std::cout << "Создан конструктором по умолчанию объект-мортира (исходные вышеописанные параметры изменены,\n"
			<< "так как по умолчанию созданные объекты не расположены корректно):\n" << "circle: (" << circle_obj.get_x_coordinate_base_point()
			<< ", " << circle_obj.get_y_coordinate_base_point() << ")\t\tradius = " << circle_obj.getRadius() 
			<< "\nrectangle: (" << rect_obj.get_x_coordinate_base_point() << ", " << rect_obj.get_y_coordinate_base_point() << ")\t\t" 
			<< "length = " << rect_obj.getLength() << ", width = " << rect_obj.getWidth() 
			<< "\nlinesegment: (" << line_obj.get_x_coordinate_base_point() << ", " << line_obj.get_y_coordinate_base_point() << ")\t\t" 
			<< "length = " << line_obj.getLength() << ", degree = " << line_obj.getDegree() << std::endl;
	}

	Mortar(const Rectangle& user_rect, const Circle& user_circle, const Linesegment& user_line)
		: rect_obj{user_rect}, circle_obj{ user_circle }, line_obj{user_line}
	{
		std::cout << "Создан конструктором со случайными параметрами объект-мортира." << std::endl;
	}

	void Show(sf::RenderWindow& window)
	{
		rect_obj.Show(window);
		circle_obj.Show(window);
		line_obj.Show(window);
	}

	void MoveTo(float dx, float dy)
	{
		rect_obj.MoveTo(dx, dy);
		circle_obj.MoveTo(dx, dy);
		line_obj.MoveTo(dx, dy);
	}

	Rectangle& getRectangleObj()
	{
		return rect_obj;
	}

	Circle& getCircleObj()
	{
		return circle_obj;
	}

	Linesegment& getLineObj()
	{
		return line_obj;
	}

	/*~Mortar()
	{
		std::cout << "Удален объект-мортира." << std::endl;
	}*/
};

#endif /* CLASS_MORTAR_H_ */