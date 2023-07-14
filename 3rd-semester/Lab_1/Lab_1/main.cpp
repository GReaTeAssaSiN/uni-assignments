#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lab_1", sf::Style::Close);
	window.setPosition(sf::Vector2i(X_BASE_POINT, Y_BASE_POINT));

	Circle* ptr_obj_circle{ nullptr };
	Rectangle* ptr_obj_rect{ nullptr };
	Linesegment* ptr_obj_linesegment{ nullptr };

	int array_circles_size{}, array_rectangles_size{}, array_linesegments_size{};

	Circle** array_circles = new Circle * [array_circles_size];
	Rectangle** array_rectangles = new Rectangle * [array_rectangles_size];
	Linesegment** array_linesegments = new Linesegment* [array_linesegments_size];

	menu_processing(window, ptr_obj_circle, ptr_obj_rect, ptr_obj_linesegment, 
		array_circles_size, array_circles,
		array_rectangles_size, array_rectangles,
		array_linesegments_size, array_linesegments);

	//Очистка занятой динамической памяти перед выходом из программы
	//Circle
	delete ptr_obj_circle;
	ptr_obj_circle = nullptr;
	//Rectangle
	delete ptr_obj_rect;
	ptr_obj_rect = nullptr;
	//Linesegment
	delete ptr_obj_linesegment;
	ptr_obj_rect = nullptr;
	//Массивы кружков, прямоугольников и отрезков
	for (int i{}; i < array_circles_size; i++)
		array_circles[i]->Free(array_circles[i]);
	delete[] array_circles;

	for (int i{}; i < array_rectangles_size; i++)
		array_rectangles[i]->Free(array_rectangles[i]);
	delete[] array_rectangles;

	for (int i{}; i < array_linesegments_size; i++)
		array_linesegments[i]->Free(array_linesegments[i]);
	delete[] array_linesegments;

	return 0;
}