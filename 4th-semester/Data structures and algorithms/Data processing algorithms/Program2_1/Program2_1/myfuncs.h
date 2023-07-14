#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

float getRandomNumber(float min, float max);
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
void printDashes();
int*& copyMyArray(const DynamicArray& numbers);
void clear_copy(DynamicArray& numbers);

bool isEmpty(DynamicArray& numbers);
void generateArray(DynamicArray& numbers);
void regenerateArray(DynamicArray& myArray);
void bubbleSorting(DynamicArray numbers);
void selectionSorting(DynamicArray numbers);
void insertionSorting(DynamicArray numbers);
void printArray(const DynamicArray& numbers);
void clear(DynamicArray& myArray);

#endif /* MYFUNCS_H_ */