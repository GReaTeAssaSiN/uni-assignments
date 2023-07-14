#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <SFML/Graphics.hpp>
#include "class_circle.h"
#include "class_rectangle.h"
#include "class_linesegment.h"

float getRandomNumber(float min, float max);

/*ØÀÁËÎÍÍÛÅ ÔÓÍÊÖÈÈ*/
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

int menu_processing(sf::RenderWindow& window, Circle*& f_ptr_obj_circle, Rectangle*& f_ptr_obj_rect, Linesegment*& f_ptr_obj_linesegment,
	int& array_circles_size, Circle**& array_circles,
	int& array_rectangles_size, Rectangle**& array_rectangles,
	int& array_linesegments_size, Linesegment**& array_linesegments);

#endif /* MYFUNCS_H_ */

