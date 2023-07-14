#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "class_linesegment.h"

void doOffsetlinesegment(Linesegment* f_ptr_obj_linesegment);
void getRandomX_Y(float& x_linesegment, float& y_linesegment, float length_linesegment, float degree_linesegment);

void push_back_linesegments(Linesegment**& array_linesegments, int& array_linesegments_size, Linesegment* ptr_new_obj_linesegment);
void pop_back_linesegments(Linesegment**& array_linesegments, int& array_linesegments_size);
void doOffsetArrayLinesegments(Linesegment** array_linesegments, int num_element);
void doUserMoveArrayLinesegmentsW(Linesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsA(Linesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsS(Linesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsD(Linesegment** array_linesegments, int array_linesegments_size);
void array_linesegments_changeDimensions(Linesegment** array_linesegments, int array_linesegments_size, int dLength);
void array_linesegments_changeRotate(Linesegment** array_linesegments, int array_linesegments_size, int dDegree);

#endif /* LINESEGMENT_H_ */