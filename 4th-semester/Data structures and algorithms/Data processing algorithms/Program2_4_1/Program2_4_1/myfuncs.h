#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include "constants.h"
#include "mystruct.h"

void printDashes();
int hashFunctionKeyToValue(const int& sum_of_character_codes_of_the_current_key);
void auxiliaryProgram(HashTable& f_hash_table);
void printHashTable(const HashTable& f_hash_table);
void getKeyAndInformationFromUser(const HashTable& f_hash_table);

#endif /* MYFUNCS_H_ */