#ifndef MYFUNCS_H_
#define MYFUNCS_H_

void printTask();
void printDash();
void printTable();

void MenuForChoices();
char getCase();

double* get_mass_x(const int& n, const double& h);
double* get_mass_p(const double* const mass_x, const int& n, const double& h);
double* get_mass_q(const double* const mass_x, const int& n, const double& h);
double* get_mass_f(const double* const mass_x, const int& n, const double& h);
double* get_mass_m(const double* const mass_q, const double* const mass_p, const int& n, const double& h);
double* get_mass_r(const double* const mass_p, const int& n, const double& h);
double* get_mass_cp(const double* const mass_p, const double* const mass_f, const int& n, const double& h);
double* get_mass_c(const double* const mass_m, const double* const mass_r, const int& n, const double& h);
double* get_mass_d(const double* const mass_cp, const double* const mass_r, const double* const mass_c, const int& n, const double& h);
double* get_mass_y(const double* const mass_c, const double* const mass_d, const int& n, const double& h);

void sweep_method(const int& n);

#endif /* MYFUNCS_H_ */