#ifndef MYFUNCS_H_
#define MYFUNCS_H_

/*œŒÀ‹«Œ¬¿“≈À‹— »≈ ‘”Õ ÷»»*/
void WelcomeUser();
void MenuForChoices();
char GetCase();

/*ƒŒœŒÀÕ»“≈À‹Õ€≈ ‘”Õ ÷»»*/
void DrawLine();
void HorizontalLineForTable(const int& col_width);
void HorizontalDoubleLineForTable(const int& col_width);
std::string CenterText(const std::string& text, const int& width);
bool CheckStrIsNumeric(std::string const& tempStr);
int ConvertStrToInt(std::string convertStr);
const std::string CheckMixedAlphabet(const std::string& text);
int gcd(int a, int b);
int modInverse(int a, int M);
char UpperToLower(const char& c, const std::string& type_alphabet);
char LowerToUpper(const char& c, const std::string& type_alphabet);

/*Œ—ÕŒ¬Õ€≈ ‘”Õ ÷»»*/
std::string SimpleSubstitutionEncryption(const std::string& text, const int& a, const int& shift, const std::string& type_alphabet);
std::string SimpleSubstitutionDecryption(const std::string& text, const int& a_inv, const int& shift, const std::string& type_alphabet);
void SimpleSubstitutionProcess();
void DisplaySimpleSubstitutionTable(const std::string& type_alphabet, const int& a, const int& shift);
//
bool CheckKeyViginer(const std::string& key_word, const std::string& type_alphabet);
std::string ViginerEncryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet);
std::string ViginerDecryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet);
void ViginerProcess();
void DisplayViginerTable(const std::string& type_alphabet, const std::string& open_text, const std::string& key_word, const std::string& encrypt_word);


#endif /* MYFUNCS_H_ */