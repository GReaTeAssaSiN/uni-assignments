#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool checkStrIsNumeric(std::string const& tempStr);
long double convertStrToNumber(std::string convertStr);

void printTask();
void printDash();

void MenuForChoices();
char getCase();

//long double getAvalue();
void printTable(const double* const& x, const double* const& t, const double* const& u_virtual, const double* const* const& u);

void grid_method(const double& a);

#endif /* MYFUNCS_H_ */