#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "class_circle.h"

void doOffsetCircle(Circle* f_ptr_obj_circle);

void push_back_circles(Circle**& array_circles, int& array_circles_size, Circle* ptr_new_obj_circle);
void pop_back_circles(Circle**& array_circles, int& array_circles_size);
void doOffsetArrayCircles(Circle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesW(Circle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesA(Circle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesS(Circle** array_circles, int array_circles_size);
void doUserMoveArrayCirclesD(Circle** array_circles, int array_circles_size);
void array_circles_RadiusIncrease(Circle** array_circles, int array_circles_size);
void array_circles_RadiusDecrease(Circle** array_circles, int array_circles_size);

#endif /* CIRCLE_H_ */
