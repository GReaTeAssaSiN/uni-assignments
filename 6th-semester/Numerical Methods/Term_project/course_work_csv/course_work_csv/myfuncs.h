#ifndef MYFUNCS_H_
#define MYFUNCS_H_

void printTask();
void printDash();

void printTableHeaderSecondDerivativeMethod(std::ofstream& outputFile);
void printTableStringSecondDerivativeMethod(std::ofstream& outputFile, const int& iter, const double& xi, const double& y_exactly, const double mass_y_i[],
	const bool& correct, const double& h, const double mass_first_approx[], const double mass_second_approx[], const double mass_third_approx[]);
void printTableHeaderThirdDerivativeMethod(std::ofstream& outputFile);
void printTableStringThirdDerivativeMethod(std::ofstream& outputFile, const int& iter, const double& xi, const double& y_exactly, const double mass_y_i[],
	const bool& correct, const double& h, const double mass_first_approx[], const double mass_second_approx[], const double mass_third_approx[]);

void MenuForChoices();
char getCase();

void second_derivative_method(const int& n, const double& epsiilon, std::ofstream& outputFile);
void third_derivative_method(const int& n, const double& epsilon, std::ofstream& outputFile);

double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h);

double getFirstDerivative(const double& xi, const double& yi);
double getSecondDerivative(const double& xi, const double& yi);
double getThirdDerivative(const double& xi, const double& yi);

double getNextFirstFormulaSecondDerivative(const double mass_y_i[], const double mass_prev_approx[], const double& h);
double getNextSecondFormulaSecondDerivative(const double mass_y_i_2[], const double mass_y_i_1[], const double mass_y_i[], const double& h);
double getNextFirstFormulaThirdDerivative(const double mass_y_i[], const double mass_prev_approx[], const double& h);
double getNextSecondFormulaThirdDerivative(const double mass_y_i_2[], const double mass_y_i_1[], const double mass_y_i[], const double& h);

double getExactlyValue(const double& xi);

bool checkStepSecondDerivative(const double mass_second_approx[], const double mass_third_approx[], const double& epsilon);
bool checkStepThirdDerivative(const double mass_second_approx[], const double mass_third_approx[], const double& epsilon);

#endif /* MYFUNCS_H_ */