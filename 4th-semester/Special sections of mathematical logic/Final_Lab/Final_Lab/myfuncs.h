#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "constants.h"

void getAboutInformation();
void printDashes();
void getLogicOperationInformation(const int& value_logic, const int& n);
bool doItAgain();
bool exitOrContinue();

bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
int getValueOfLogic();
int getCountOfSignificantVariables();
bool checkStringFunction(const std::string& user_logic_function, const int& value_logic);
bool checkCharacterSequenceOfStrFunction(const std::string& user_logic_function);
int getOperationPriority(const char& operation);
bool strElemIsDigit(const char& str_elem);
bool reversePolishNotationForFunction(const std::string& logic_function, std::string& logic_function_by_RPN, const int& significant_variables_count);
int PostSubstraction(const int& number, const int& value_logic);
int truncatedDifference(const int& first_operand, const int& second_operand);
int compositionModuloK(const int& first_operand, const int& second_operand, const int& value_logic);
bool checkStringSetOfValues(const std::string& set_of_values, const int& value_logic, int& number_of_values);

std::string getFunctionFromUser(std::string& logic_function_by_RPN, const int& value_logic, const int& significant_variables_count);
void functionValuesInTableForm(const std::string& logic_function_by_RPN, const int& value_logic, const int& significant_variables_count, int**& function_values);
int evaluateFunction(const std::string& logic_function_by_RPN, const int& value_logic, const int& x_value, const int& y_value, int**& function_values);
void getTheSecondFormOfTheFunction(const int& significant_variables_count, const int& value_logic, int**& function_values);
std::string getSetValues(const int& value_logic, int& number_of_values);
bool getMembershipFunctionToClass(const std::string& set_of_values, int**& function_values, const int& value_logic, const int& significant_variables_count, const int& number_of_values);
void programExecution();

#endif /* MYFUNCS_H_ */