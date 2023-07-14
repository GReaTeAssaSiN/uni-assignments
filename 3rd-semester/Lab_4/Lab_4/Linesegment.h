#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "class_TLinesegment.h"

void doOffsetlinesegment(TLinesegment* f_ptr_obj_linesegment);

void doOffsetArrayLinesegments(TLinesegment** array_linesegments, int num_element);
void doUserMoveArrayLinesegmentsW(TLinesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsA(TLinesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsS(TLinesegment** array_linesegments, int array_linesegments_size);
void doUserMoveArrayLinesegmentsD(TLinesegment** array_linesegments, int array_linesegments_size);
void array_linesegments_changeDimensions(TLinesegment** array_linesegments, int array_linesegments_size, int dLength);
void array_linesegments_changeRotate(TLinesegment** array_linesegments, int array_linesegments_size, int dDegree);

#endif /* LINESEGMENT_H_ */