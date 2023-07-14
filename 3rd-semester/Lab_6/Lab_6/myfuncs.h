#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "constants.h"
#include "class_TCircle.h"
#include "class_TRectangle.h"
#include "class_TEllipse.h"
#include "class_TRhomb.h"
#include "class_TTrapeze.h"
#include "class_TQuadrilateral.h"
#include "class_Container_DynamicArray.h"
#include "class_Container_LynearDynamicList.h"

float getRandomNumber(float min, float max);

int menu_processing(sf::RenderWindow& window, DynamicArray*& ptr_container_figures_dynamic_array, LynearDynamicList*& ptr_container_figures_lynear_dynamic_list, 
	TFigure*& ptr_graphic_primitive, int& size_container_figures_dynamic_array, int& size_container_figures_lynear_dynamic_list);

#endif /* MYFUNCS_H_ */