#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

bool isEmptyQueue(const Queue& f_queue);
bool isFullnessQueue(const Queue& f_queue);
void enQueue(Queue& f_queue);
void deQueue(Queue& f_queue);
void printQueue(const Queue& f_queue);

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);

#endif /* MYFUNCS_H_ */