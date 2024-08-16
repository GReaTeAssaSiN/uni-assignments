#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);

void printTask();
void printDash();
void printTableInterpolation();
void printTableNumericalDefferentiation();

void MenuForChoices();
char getCase();
long double getXValue(const int& number);

long double getClosestToX(const long double& x_value, const int& method);

void interpolation_formulas(const long double& x1, const long double& x2, const long double& x3);
void numerical_differentiation_formulas(const long double& x1, const long double& x2, const long double& x3);

#endif /* MYFUNCS_H_ */