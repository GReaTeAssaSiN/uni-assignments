#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include "mystructs.h"
#include "constants.h"

void printDashes();
void MenuForChoices();
char getCase();

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);

int hashFunctionKeyToValue(const int& sum_of_character_codes_of_the_current_key, const int& number_m);
int getNumberM();
std::string getKeyFromUser();
void addNewKeyToHashTable(HashTable* f_hash_table);
void searchKeyInHashTable(const HashTable* f_hash_table);
void deleteKeyFromHashTable(HashTable* f_hash_table);
void deleteKeyFromHashTable(HashTable* f_hash_table);
void printHashTable(const HashTable* f_hash_table);

#endif /* MYFUNCS_H_ */