#ifndef MYFUNCS_H_
#define MEFUNCS_H_

std::string selectFile(Blank blank, const std::string defaultPath);
bool initStr(Select select, std::istream& f, std::string &subsequence, unsigned& NM);
void result(std::ostream& f, unsigned NM, std::string strOut);
bool getNext();
unsigned char get_0_1();
double getLength();

#endif /*MYFUNCS_H_*/
