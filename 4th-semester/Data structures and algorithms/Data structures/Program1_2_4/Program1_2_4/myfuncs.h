#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

//�������������� �������.
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
float getRandomNumber(float min, float max);
unsigned char get_0_1();

//���������������� ����.
void MenuForChoices();
char getCase();

//������� ������ �� ������.
bool isEmpty(Stack* stack);
void push(Stack* stack, const int& x);
bool pass(Stack* from_stack, Stack* to_stack);
void pop(Stack* stack);
void print(Stack* stack);
void clear(Stack*& stack);

//������� ������ �� ������ � ���������� �������� ������������ � ������� ���������� ��� ����. 
void user_push(Stack* baseStack, Stack* auxiliaryStack);
void user_push_random(Stack* baseStack);
void user_pop(Stack* baseStack, Stack* auxiliaryStack);
void user_printBaseStack(Stack* baseStack);
void user_printAuxiliaryStack(Stack* auxiliaryStack);
void user_clear(Stack*& baseStack, Stack*& auxiliaryStack);

#endif /* MYFUNCS_H_ */