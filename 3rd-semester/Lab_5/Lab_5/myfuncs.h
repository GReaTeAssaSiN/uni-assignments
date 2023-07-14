#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "constants.h"
#include "class_TCircle.h"
#include "class_TRectangle.h"
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

int menu_processing(sf::RenderWindow& window, TFigure**& figures_array, int& size_figures_array);

#endif /* MYFUNCS_H_ */