#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystruct.h"

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);

void MenuForChoices();
char getCase();

void printListOfLists(ListOfLists* f_myListOfLists);
void searchListOfLists(ListOfLists* f_myListOfLists);
void addNewElemToListOfLists(ListOfLists*& f_myListOfLists, const int& before_or_after);
void addNewElemToList(ListOfLists*& f_myListOfLists, const int& before_or_after);
void removeList(ListOfLists*& f_myListOfLists);
void removeElemOfList(ListOfLists* f_myListOfLists);
void clearListOfLists(ListOfLists*& f_myListOfLists);

bool isEmptyListOfLists(ListOfLists* f_myListOfLists);
bool isEmptyList(List* f_myList);
void clearList(ListOfLists* f_myListOfLists, List* f_list);
Node* searchElem(List* specified_list, const int& searching_elem);
List* checkListExist(ListOfLists* f_myListOfLists, const int& number_list);
std::string getElem();
void printDashes();

#endif /* MYFUNCS_H_ */