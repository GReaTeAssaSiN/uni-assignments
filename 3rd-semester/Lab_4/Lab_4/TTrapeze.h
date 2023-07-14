#ifndef TRAPEZE_H_
#define TRAPEZE_H_

#include "class_TTrapeze.h"

void doOffsetTrapeze(TTrapeze* f_ptr_obj_trapeze);

void doOffsetArrayTrapezes(TTrapeze** array_trapezes, int array_trapezes_size);
void doUserMoveArrayTrapezesW(TTrapeze** array_trapezes, int array_trapezes_size);
void doUserMoveArrayTrapezesA(TTrapeze** array_trapezes, int array_trapezes_size);
void doUserMoveArrayTrapezesS(TTrapeze** array_trapezes, int array_trapezes_size);
void doUserMoveArrayTrapezesD(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_IncreaseTopBase(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_DecreaseTopBase(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_IncreaseHeight(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_DecreaseHeight(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_IncreaseBottomBase(TTrapeze** array_trapezes, int array_trapezes_size);
void array_trapezes_DecreaseBottomBase(TTrapeze** array_trapezes, int array_trapezes_size);

#endif /*TRAPEZE_H_*/