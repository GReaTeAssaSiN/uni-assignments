#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

void MenuForChoices();
char getCase();

void printList(const List& f_list);
void searchList(List& f_list);
void addNewElem(List& f_list);
void removeElem(List& f_list);

bool isEmptyList(const List& f_list);
bool isFullnesList(const List& f_list);
std::string getElem();
void printDashes();

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);


#endif /* MYFUNCS_H_ */