#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "class_House.h"
#include "class_Street.h"
#include "class_City.h"

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
bool checkLatinSymbol(const char& specific_symbol);
bool checkRussianSymbol(const char& specific_symbol);
void userMenu(const std::string& city_name);
void userSubmenu(const std::string& specific_city_street_name);
char getUserChoice(const int& flag);
void printDashes();
bool checkCityOrStreetName(const std::string& check_str);
bool checkTypeBuildingFromUser(const std::string& check_str);
std::string getCityNameFromUser();
std::string getStreetNameFromUser(City* current_city_ptr);
int getHouseNumberForAddingFromUser(Street* current_street_ptr);
std::string getHouseTypeBuildingFromUser();
int getHouseNumberForRemovingOrSearchingFromUser();
bool protectInputFile(std::ifstream& f, const std::string& input_file_name);
bool getUserWishesAboutCityName(City* current_city_ptr, const std::string& new_city_name);

void showTheCity(City* current_city_ptr);
void addNewStreetInTheCity(City* current_city_ptr);
void removeThFirsteStreetFromTheCity(City* current_city_ptr);
void selectionOfASpecificCityStreet(City* current_city_ptr);
void exportTheCityToFile(City* current_city_ptr);
void importTheCityFromFile(City* current_city_ptr);

void checkTheStreet(Street* current_street_ptr);
void addTheHouse(Street* current_street_ptr);
void removeTheHouse(Street* current_street_ptr);
void searchTheHouse(Street* current_street_ptr);
void showTheStreet(Street* current_street_ptr);

#endif /* MYFUNCS_H_ */