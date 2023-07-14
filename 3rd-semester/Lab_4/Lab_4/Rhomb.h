#ifndef RHOMB_H_
#define RHOMB_H_

#include "class_TRhomb.h"

void doOffsetRhomb(TRhomb* f_ptr_obj_rhomb);

void doOffsetArrayRhombs(TRhomb** array_rhombs, int array_rhombs_size);
void doUserMoveArrayRhombsW(TRhomb** array_rhombs, int array_rhombs_size);
void doUserMoveArrayRhombsA(TRhomb** array_rhombs, int array_rhombs_size);
void doUserMoveArrayRhombsS(TRhomb** array_rhombs, int array_rhombs_size);
void doUserMoveArrayRhombsD(TRhomb** array_rhombs, int array_rhombs_size);
void array_rhombs_IncreaseLength(TRhomb** array_rhombs, int array_rhombs_size);
void array_rhombs_DecreaseLength(TRhomb** array_rhombs, int array_rhombs_size);
void array_rhombs_IncreaseDegree(TRhomb** array_rhombs, int array_rhombs_size);
void array_rhombs_DecreaseDegree(TRhomb** array_rhombs, int array_rhombs_size);

#endif /* RHOMB_H_ */