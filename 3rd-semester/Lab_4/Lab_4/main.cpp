#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lab_4", sf::Style::Close);
	window.setPosition(sf::Vector2i(X_BASE_POINT, Y_BASE_POINT));

	TCircle* ptr_obj_circle{ nullptr };
	TRectangle* ptr_obj_rect{ nullptr };
	TLinesegment* ptr_obj_linesegment{ nullptr };
	TEllipse* ptr_obj_ellipse{ nullptr };
	TRhomb* ptr_obj_rhomb{ nullptr };
	TTrapeze* ptr_obj_trapeze{ nullptr };
	TQuadrilateral* ptr_obj_quadrilateral{ nullptr };

	int array_circles_size{}, array_rectangles_size{}, array_linesegments_size{}, array_ellipses_size{}, array_rhombs_size{}, array_trapezes_size{}, array_quadrilaterals_size{};

	TCircle** array_circles = new TCircle * [array_circles_size];
	TRectangle** array_rectangles = new TRectangle * [array_rectangles_size];
	TLinesegment** array_linesegments = new TLinesegment * [array_linesegments_size];
	TEllipse** array_ellipses = new TEllipse * [array_ellipses_size];
	TRhomb** array_rhombs = new TRhomb * [array_rhombs_size];
	TTrapeze** array_trapezes = new TTrapeze * [array_trapezes_size];
	TQuadrilateral** array_quadrilaterals = new TQuadrilateral * [array_quadrilaterals_size];

	menu_processing(window, ptr_obj_circle, ptr_obj_rect, ptr_obj_linesegment, ptr_obj_ellipse, ptr_obj_rhomb, ptr_obj_trapeze, ptr_obj_quadrilateral,
		array_circles_size, array_circles,
		array_rectangles_size, array_rectangles,
		array_linesegments_size, array_linesegments,
		array_ellipses_size, array_ellipses,
		array_rhombs_size, array_rhombs,
		array_trapezes_size, array_trapezes,
		array_quadrilaterals_size, array_quadrilaterals);

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
	//Ellipse
	delete ptr_obj_ellipse;
	ptr_obj_ellipse = nullptr;
	//Rhomb
	delete ptr_obj_rhomb;
	ptr_obj_rhomb = nullptr;
	//Trapeze
	delete ptr_obj_trapeze;
	ptr_obj_trapeze = nullptr;
	//Quadrilateral
	delete ptr_obj_quadrilateral;
	ptr_obj_quadrilateral = nullptr;

	//Массивы
	for (int i{}; i < array_circles_size; i++)
		array_circles[i]->Free(array_circles[i]);
	delete[] array_circles;

	for (int i{}; i < array_rectangles_size; i++)
		array_rectangles[i]->Free(array_rectangles[i]);
	delete[] array_rectangles;

	for (int i{}; i < array_linesegments_size; i++)
		array_linesegments[i]->Free(array_linesegments[i]);
	delete[] array_linesegments;

	for (int i{}; i < array_ellipses_size; i++)
		array_ellipses[i]->Free(array_ellipses[i]);
	delete[] array_ellipses;

	for (int i{}; i < array_rhombs_size; i++)
		array_rhombs[i]->Free(array_rhombs[i]);
	delete[] array_rhombs;

	for (int i{}; i < array_quadrilaterals_size; i++)
		array_quadrilaterals[i]->Free(array_quadrilaterals[i]);
	delete[] array_quadrilaterals;

	for (int i{}; i < array_trapezes_size; i++)
		array_trapezes[i]->Free(array_trapezes[i]);
	delete[] array_trapezes;

	return 0;
}