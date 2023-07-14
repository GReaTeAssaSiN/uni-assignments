#ifndef MYFUNCS_H_
#define MYFUNCS_H_

unsigned char get_0_1();
bool getNext();
bool init(double mass[NM]);
bool finit(std::ifstream& f, double mass[NM]);
double getValue();
bool check_FirstCondition(double mass[NM]);
bool check_SecondCondition(double mass[NM], double &t1, double &t2);
void conditions_answer(std::ostream& f, double mass[NM], double t1, double t2);

#endif /*MYFUNCS_H_*/