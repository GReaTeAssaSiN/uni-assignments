#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <sstream>
#include "mystructs.h"
#include "ArrayThreeStrings.h"

//Основные функции
bool LoadingList(const std::string fileName, Trade*& head);
bool UnloadingList(const std::string fileName, Trade* head);
unsigned ListLength(Trade* head);
void AddNewElement(Trade*& previous, Trade* ea);
void DeleteElement(Trade* search_prev_del, const Trade* ed);
void SortList(Trade* head);
void PrintList(const Trade* head);

//Всопомгательные функции
bool getListFromFile(Trade*& head, std::ifstream& fileName);
bool CheckCorrectField(std::string check_DataLine, unsigned count);
bool FastInput_TradingVolume(Trade* ea, std::string fast_AddNewElement);
void getNewTrade(Trade*& head, std::stringstream& lieStream);
void InitializationNewTrade(std::stringstream& lineStream, Trade*& init_head);
void CreateHeadOfList(Trade*& head);
std::string checkData2();
unsigned getSortChoice();
void swapData(const std::string& currentDataStr, const std::string& indexDataStr, TradeData& currentData, TradeData& indexData, unsigned choice);
void ComparisonNumber(const std::string& currentDataStr, const std::string& indexDataStr, TradeData& currentData, TradeData& indexData);
char getCase();
double GetNumber();
void SortChoice(unsigned choice, Trade* def_current, Trade* def_index);

//Пользовательские функции
void MenuForChoices();
void case1(Trade* head);
void case2(Trade* head);
void case3(Trade*& head);
void case4(Trade* head);
void case5(const Trade* head);
void case6(Trade* head);

#endif /* MYFUNCS_H_ */