#ifndef MYFUNCS_H_
#define MYFUNCS_H_

unsigned char get_0_1();
bool getNext();
bool init(double mass[NM], unsigned &size);
bool finit(std::ifstream& f, double mass[NM], unsigned &size);
unsigned getSize();
bool checksize(unsigned &size);
double getValue();
void connection_capasitor(std::ostream& f, double mass[NM], unsigned &size);

#endif /*MYFUNCS_H_*/
