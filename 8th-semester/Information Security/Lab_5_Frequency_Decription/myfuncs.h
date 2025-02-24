#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>   //std::setprecision();
#include <sstream>   //std::stringstream;
#include <algorithm> //std::sort();
#include <cctype>	 //std::isprint();

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
void WelcomeUser();
void MenuForChoices();
char GetCase();

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
void DrawLine(const char& del);
std::string CenterText(const std::string& text, const int& width);

/*ОСНОВНЫЕ ФУНКЦИИ*/
void AnalyzeFrequencyProcess();
void DecryptFileProcess();
bool compare(const std::pair<unsigned char, CharInfo>& a, const std::pair<unsigned char, CharInfo>& b);
bool analyzeFile(const std::string& inputFilename, std::map<unsigned char, CharInfo>& freq, int& total_chars);
void computePercentages(std::map<unsigned char, CharInfo>& freq, int total_chars);
bool writeResults(const std::string& outputFilename, const std::map<unsigned char, CharInfo>& freq);
bool decryptFile(const std::string& freqFile1, const std::string& freqFile2,
	const std::string& inputFilename, const std::string& outputFilename, const std::string& file_table);
bool saveSubstitutionTable(const std::vector<std::pair<unsigned char, unsigned char>>& substitution, const std::string& filename);

#endif /*MYFUNCS_H_*/