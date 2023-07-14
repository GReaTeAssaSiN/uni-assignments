#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

float getRandomNumber(float min, float max);
bool isSymbolQ();
void printDashes();

bool isEmptyQueue(Queue* f_queue);
void enQueue(Queue*& f_queue, char f_symbol);
void deQueue(Queue*& f_queue);
void printQueue(Queue* f_queue);
void clearQueue(Queue*& f_queue);
#endif /* MYFUNCS_H_ */