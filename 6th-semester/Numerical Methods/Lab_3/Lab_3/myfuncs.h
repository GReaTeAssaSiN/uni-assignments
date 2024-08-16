#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);

void printTask();
void printDash();

void MenuForChoices();
char getCase();

long double getSvalue();
void printTable(const double* const& x, const double* const& t, const double* const* const& u);

void explicit_schema();
void implicit_schema(const double& S);

#endif /* MYFUNCS_H_ */