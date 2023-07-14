#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "class_TCircle.h"

void doOffsetCircle(TCircle* f_ptr_obj_circle);

void doOffsetArrayCircles(TCircle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesW(TCircle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesA(TCircle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesS(TCircle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesD(TCircle** array_circles, int array_circles_size);
void array_circles_RadiusIncrease(TCircle** array_circles, int array_circles_size);
void array_circles_RadiusDecrease(TCircle** array_circles, int array_circles_size);

#endif /* CIRCLE_H_ */
