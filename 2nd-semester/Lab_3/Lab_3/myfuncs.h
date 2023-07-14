#ifndef MYFUNCS_H_
#define MYFUNCS_H_

bool init(double*** mass, unsigned& NM, unsigned &i1, unsigned &i2);
bool finit(std::istream& f, double*** mass, unsigned& NM, unsigned& i1, unsigned& i2);
void fdelpartmass(std::ostream& f, double** mass, unsigned NM, unsigned i1, unsigned i2);
unsigned getIndex();
double getValue();
bool getNext();
unsigned char get_0_1();
bool checkIndexes(unsigned i1, unsigned i2, unsigned NM);
bool makeMass(double*** mass, unsigned NM);

#endif /*MYFUNCS_H_*/