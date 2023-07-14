#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TLinesegment.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"

float getRandomNumber(float min, float max);

/*ÿ¿¡ÀŒÕÕ€≈ ‘”Õ ÷»»*/
template <class Shape>
void push_back_shapes(Shape**& array_shapes, int& array_shapes_size, Shape* ptr_new_obj_shape)
{
	Shape** new_array_shapes = new Shape * [array_shapes_size + 1];
	for (int i{}; i < array_shapes_size; i++)
	{
		new_array_shapes[i] = array_shapes[i];
	}

	new_array_shapes[array_shapes_size] = ptr_new_obj_shape;
	delete[] array_shapes;
	array_shapes_size += 1;
	array_shapes = new_array_shapes;
}
template <class Shape>
void pop_back_shapes(Shape**& array_shapes, int& array_shapes_size)
{
	Shape** new_array_shapes = new Shape * [array_shapes_size - 1];
	for (int i{}; i < array_shapes_size - 1; i++)
	{
		new_array_shapes[i] = array_shapes[i];
	}
	array_shapes[array_shapes_size - 1]->Free(array_shapes[array_shapes_size - 1]);
	delete[] array_shapes;
	array_shapes_size -= 1;
	array_shapes = new_array_shapes;
}

int menu_processing(sf::RenderWindow& window, TCircle*& f_ptr_obj_circle, TRectangle*& f_ptr_obj_rect, TLinesegment*& f_ptr_obj_linesegment, TEllipse*& f_ptr_obj_ellipse,
	TRhomb*& f_ptr_obj_rhomb, TTrapeze*& f_ptr_obj_trapeze, TQuadrilateral*& f_ptr_obj_quadrilateral,
	int& array_circles_size, TCircle**& array_circles,
	int& array_rectangles_size, TRectangle**& array_rectangles,
	int& array_linesegments_size, TLinesegment**& array_linesegments,
	int& array_ellipses_size, TEllipse**& array_ellipses,
	int& array_rhombs_size, TRhomb**& array_rhombs,
	int& array_trapezes_size, TTrapeze**& array_trapezes,
	int& array_quadrilaterals_size, TQuadrilateral**& array_quadrilaterals);

#endif /* MYFUNCS_H_ */