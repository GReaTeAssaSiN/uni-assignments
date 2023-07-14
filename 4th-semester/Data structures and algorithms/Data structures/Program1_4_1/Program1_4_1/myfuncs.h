#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);

void MenuForChoices();
char getCase();

void printList(List* f_myList, const int& direct_or_reverse);
void searchList(List* f_myList, const int& direct_or_reverse);
void addNewElem(List*& f_myList, const int& before_after);
void clearList(List*& f_myList);
void removeElem(List*& f_myList);

bool isEmptyList(List* f_myList);
Node* searchElem(List* f_myList, const int& searching_elem);
std::string getElem();
void printDashes();

#endif /* MYFUNCS_H_ */