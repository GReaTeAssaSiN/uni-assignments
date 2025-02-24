#include <iostream>
#include <string>
#include <iomanip>
#include "myfuncs.h"

/*���������������� �������*/
//����� ����������.
void WelcomeUser() {
	std::cout << std::endl << "|" << std::string(200, '-') << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << CenterText("��������� ������������, ����� ���������� � ���������!", 200) << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << std::string(200, '-') << "|" << std::endl << std::endl;
}
//���������������� ����.
void MenuForChoices()
{
	std::cout << "�������� ����� ���������� �� ������ ����:" << std::endl <<
		"1 - ������� �������������� ������ (���������� ����� ������)" << std::endl <<
		"2 - ������� ���������� ��������" << std::endl <<
		"0 - ����� �� ���������" << std::endl;
}
//������ �������� � ������������.
char GetCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice.size() == 1 && choice[0] >= '0' && choice[0] <= '3')
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 0 �� 2). " <<
				"��������� ����." << std::endl;
		}
	}
}

/*�������������� �������*/
//������� ��������� �������������� �����.
void DrawLine() {
	std::cout << std::endl << "|" << std::string(200, '=') << "|" << std::endl;
}
//������� ��������� �������������� ����� �������.
void HorizontalLineForTable(const int& col_width)
{
	std::cout << std::string(col_width + 2, '-') << std::endl;
}
//������� ��������� �������������� ������� ����� �������.
void HorizontalDoubleLineForTable(const int& col_width)
{
	std::cout << std::string(col_width + 2, '=') << std::endl;
}
//������� ��� ������������� ������.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // ��������� ������������.
	int left_padding = padding / 2;  // ����� �����.
	int right_padding = padding - left_padding; // ������ �����.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//�������� �������� ������������� ������ �� ����������� �������������� � ����� �����.
bool CheckStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
			continue;
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � �����.
int ConvertStrToInt(std::string convertStr)
{
	double number{};
	bool negative_number{ false };
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && (convertStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
	}
	return negative_number ? static_cast<int>(-number) : static_cast<int>(number);
}
//�������� ������ �� ������� ("RUS") ��� ��������� ("LATIN") �������, ��������� = "MIXED", ��� ���� = "NONE".
const std::string CheckMixedAlphabet(const std::string& text)
{
	bool hasLatin{};
	bool hasRussian{};

	for (const char& c : text) {
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			hasLatin = true;
		}
		else if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�') || c == '�' || c == '�') {
			hasRussian = true;
		}
		if (hasLatin && hasRussian) {
			return "MIXED";
		}
	}

	if (hasLatin) {
		return "LATIN";
	}
	else if (hasRussian) {
		return "RUS";
	}

	return "NONE";
}
//������� ��� ���������� ��� (gcd) ���� �����.
int gcd(int a, int b) {
	//�������� �������.
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
//������� ��� ���������� ��������� ����� � a �� ������ M.
int modInverse(int a, int M) {
	//����������� �������� �������.
	int m0{ M }, t{}, q{};
	int x0{ 0 }, x1{ 1 }; //������������: a * x0 + M * x1 = gcd(a,M) - ���������.

	//��������, ��� a � M ������� ������.
	if (M == 1)
		return 0;

	while (a > 1) {
		q = a / M;			// ��� 1: ������������� ������� (���������� ������������ q).
		t = M;				// ��� 2: ���������� ������� M ����� �����������.
		M = a % M;			// ��� 3: ������� �� ������� (���������� M).
		a = t;				// ��� 4: ���������� a (a ������ ���������� M).
		// ���� 1 - 4: ����� ��� �� ��������� �������.
		t = x0;				// ��� 5: ���������� ����������� x0. 
		x0 = x1 - q * x0;	// ��� 6: ���������� x0 �� ������� x0 = x1 - q * x0. 
		x1 = t;				// ��� 7: ���������� x1 (x1 ������ ������ x0).
	}

	// ���� x1 �������������, ��������� M, ����� �������� ������������� �����.
	if (x1 < 0)
		x1 += m0;

	return x1;
}
//������� -> ������ ������� ������� � ��������� ��������.
char UpperToLower(const char& c, const std::string& type_alphabet)
{
	if (type_alphabet == "RUS") {
		if (c >= '�' && c <= '�')
			return c + ('�' - '�');
		if (c == '�')
			return '�';
	}
	else if (type_alphabet == "LATIN") {
		if (c >= 'A' && c <= 'Z') {
			return c + ('a' - 'A');
		}
	}
	return c;
}
//������ -> ������� ������� ������� � ��������� ��������.
char LowerToUpper(const char& c, const std::string& type_alphabet)
{
	if (type_alphabet == "RUS") {
		if (c >= '�' && c <= '�')
			return c - ('�' - '�');
		if (c == '�')
			return '�';
	}
	else if (type_alphabet == "LATIN") {
		if (c >= 'a' && c <= 'z') {
			return c - ('a' - 'A');
		}
		return c;
	}
	return c;
}

/*�������� �������*/
//���������� ������� ������� �������������� ������.
std::string SimpleSubstitutionEncryption(const std::string& text, const int& a, const int& shift, const std::string& type_alphabet)
{
	//����������.
	std::string result{};

	//���������.
	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; //����������� �������� ��������.
		//�������� � ��������� ����� �������� ��������.
		const std::string russian_upper = "�����Ũ��������������������������";
		const std::string russian_lower = "��������������������������������";

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				int mod_shift = (shift % RUSSIAN_M + RUSSIAN_M) % RUSSIAN_M; //������������.
				char encrypted = russian_upper[(a * russian_upper.find(c) + mod_shift) % RUSSIAN_M];
				result += encrypted;
			}
			else if (russian_lower.find(c) != std::string::npos) {
				int mod_shift = (shift % RUSSIAN_M + RUSSIAN_M) % RUSSIAN_M; //������������.
				char encrypted = russian_lower[(a * russian_lower.find(c) + mod_shift) % RUSSIAN_M];
				result += encrypted;
			}
			else {
				result += c;
			}
		}
	}
	else if (type_alphabet == "LATIN") {
		const int LATIN_M = 26; //����������� ���������� ��������.
		//�������� � ��������� ����� ���������� ��������.
		const std::string latin_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string latin_lower = "abcdefghijklmnopqrstuvwxyz";

		for (const char& c : text) {
			if (latin_upper.find(c) != std::string::npos) {
				int mod_shift = (shift % LATIN_M + LATIN_M) % LATIN_M; //������������.
				char encrypted = latin_upper[(a * latin_upper.find(c) + mod_shift) % LATIN_M];
				result += encrypted;
			}
			else if (latin_lower.find(c) != std::string::npos) {
				int mod_shift = (shift % LATIN_M + LATIN_M) % LATIN_M; //������������.
				char encrypted = latin_lower[(a * latin_lower.find(c) + mod_shift) % LATIN_M];
				result += encrypted;
			}
			else {
				result += c;
			}
		}
	}
	else {
		result += text;
	}

	return result;
}
//������������ ������� ������� �������������� ������.
std::string SimpleSubstitutionDecryption(const std::string& text, const int& a_inv, const int& shift, const std::string& type_alphabet) {
	//������������.
	std::string result{};

	//���������.
	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; //����������� �������� ��������.
		//�������� � ��������� ����� �������� ��������.
		const std::string russian_upper = "�����Ũ��������������������������";
		const std::string russian_lower = "��������������������������������";

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				char decrypted = russian_upper[(a_inv * ((russian_upper.find(c) - shift + RUSSIAN_M) % RUSSIAN_M)) % RUSSIAN_M];
				result += decrypted;
			}
			else if (russian_lower.find(c) != std::string::npos) {
				char decrypted = russian_lower[(a_inv * ((russian_lower.find(c) - shift + RUSSIAN_M) % RUSSIAN_M)) % RUSSIAN_M];
				result += decrypted;
			}
			else {
				result += c;
			}
		}
	}
	else if (type_alphabet == "LATIN") {
		const int LATIN_M = 26; //����������� ���������� ��������.
		//�������� � ��������� ����� ���������� ��������.
		const std::string latin_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string latin_lower = "abcdefghijklmnopqrstuvwxyz";

		for (const char& c : text) {
			if (latin_upper.find(c) != std::string::npos) {
				char decrypted = latin_upper[(a_inv * ((latin_upper.find(c) - shift + LATIN_M) % LATIN_M)) % LATIN_M];
				result += decrypted;
			}
			else if (latin_lower.find(c) != std::string::npos) {
				char decrypted = latin_lower[(a_inv * ((latin_lower.find(c) - shift + LATIN_M) % LATIN_M)) % LATIN_M];
				result += decrypted;
			}
			else {
				result += c;
			}
		}
	}
	else {
		result += text;
	}

	return result;
}
//���������� ������� ������� �������������� ������ - ���������.
void SimpleSubstitutionProcess()
{
	//���������.
	std::cout << "���������� ������� ������� �������������� ������. �������������� ���������� ������� �������� -> ������� �������, "
		"��������� �������� -> ��������� �������." << std::endl;
	DrawLine();
	std::cout << std::endl;
	while (true) {
		//������.
		std::cout << "������� ������ ��� ���������� (quit - �����): ";
		std::string open_text{};
		std::getline(std::cin, open_text);
		if (open_text == "quit") break;
		//�������� ������ �� �����������.
		const std::string type_alphabet{ CheckMixedAlphabet(open_text) };
		if (type_alphabet == "MIXED") {
			std::cout << "������! ������ ��� ���������� ������ ��������� ������� �� ������ ��������. ���������� �����." << std::endl << std::endl;
			continue;
		}

		//�������� ������������� ���������.
		if (type_alphabet == "NONE") {
			std::cout << "***���������/����������� ������!***" << std::endl;
			std::cout << "������������� ������: " << open_text << std::endl;
			std::cout << "������������� ������: " << open_text << std::endl;
			DrawLine();
			std::cout << std::endl;
			continue;
		}
		else
			std::cout << "����������� �������� M = " << ((type_alphabet == "RUS") ? 33 : 26) << ". ������ ��� ������ 'a' (���(a,M) = 1)." << std::endl << std::endl;

		//�������� a.
		std::cout << "������� �������� a (quit - �����): ";
		std::string a_value{};
		std::getline(std::cin, a_value);
		if (a_value == "quit") break;
		//�������� �������� a.
		if (!(CheckStrIsNumeric(a_value) && ConvertStrToInt(a_value) >= 0)) {
			std::cout << "������! �������� 'a' ������ ���� ����� ��������������� ������. ���������� �����." << std::endl << std::endl;
			continue;
		}
		//�������� ���(a,M)=1.
		const int a{ ConvertStrToInt(a_value) };
		int M{};
		if (type_alphabet == "RUS")
			M = 33; //����������� �������� ��������.
		else if (type_alphabet == "LATIN")
			M = 26; //����������� ���������� ��������.
		else
			M = 1; //mod M ������ �� ������.
		const int gcd_value{ gcd(a,M) };//���(a,M).
		if (gcd_value != 1) {
			std::cout << "������! ���(a,M) = ���(" << a << "," << M << ") = " << gcd_value << ", � ������ ���� ����� 1! (����� ������� �������������� ������ " <<
				"�� ����� ������� ����������� ����������� � ����� �����). ���������� �����." << std::endl << std::endl;
			continue;
		}

		//����.
		std::cout << "������� �������� ����� K (quit - �����): ";
		std::string key_crypt{};
		std::getline(std::cin, key_crypt);
		if (key_crypt == "quit") break;
		//�������� �������� ����� K.
		if (!(CheckStrIsNumeric(key_crypt) && ConvertStrToInt(key_crypt) >= 0 && ConvertStrToInt(key_crypt) < M)) {
			std::cout << "������! �������� ����� K ������ ���� ����� ��������������� ������, 0 <= K < M = " << M << ". ���������� �����." << std::endl << std::endl;
			continue;
		}

		//���������.
		const int shift{ ConvertStrToInt(key_crypt) };//����.
		const int a_inv{ modInverse(a, M) };//�������� �������� � 'a' �� ������ M.
		std::string encrypt_str{ SimpleSubstitutionEncryption(open_text, a, shift, type_alphabet) };
		std::string	decrypt_str{ SimpleSubstitutionDecryption(encrypt_str, a_inv, shift, type_alphabet) };

		//�����.
		DisplaySimpleSubstitutionTable(type_alphabet, a, shift);
		std::cout << "������������� ������: " << encrypt_str << std::endl;
		std::cout << "������������� ������: " << decrypt_str << std::endl;
		DrawLine();
		std::cout << std::endl;
	}
}
//����� ����������� ���������� ������� ������� �������������� ������.
void DisplaySimpleSubstitutionTable(const std::string& type_alphabet, const int& a, const int& shift)
{
	//����������� ��������.
	std::string alphabet{};
	if (type_alphabet == "RUS") alphabet = "�����Ũ��������������������������";
	else if (type_alphabet == "LATIN") alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else return;

	const int col_width{ 3 }; //������ �������.

	//���������.
	std::cout << std::endl;
	HorizontalLineForTable(col_width * 15 + 14);
	std::cout << "|" << CenterText("������� ����������� ����������� ������ ������", col_width * 15 + 14) << "|" << std::endl;
	HorizontalLineForTable(col_width * 15 + 14);

	//����� ������� �����������.
	int columns{ 4 };
	int rows{ static_cast<int>(alphabet.size() / columns + ((alphabet.size() % columns) == 0 ? 0 : 1)) };
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t col = 0; col < columns; ++col)
		{
			size_t index{ row + col * rows };
			if (index < alphabet.size())
			{
				std::cout << "|" << std::right << std::setw(col_width) << alphabet[index] << "|" <<
					std::right << std::setw(col_width) << "->" << "|" <<
					std::right << std::setw(col_width) << alphabet[(a * index + shift) % alphabet.size()] << "|" <<
					std::right << std::setw(col_width) << " ";
			}
			else
			{
				std::cout << "|" << std::right << std::setw(col_width) << " " << "|" <<
					std::right << std::setw(col_width) << " " << "|" <<
					std::right << std::setw(col_width) << " " << "|";
			}
		}
		std::cout << std::endl;
	}
	HorizontalLineForTable(col_width * 15 + 14);
}
//
// 
// 
//�������� ����� �������� �� ������������.
bool CheckKeyViginer(const std::string& key_word, const std::string& type_alphabet)
{
	//��������.
	const std::string RUS_alphabet = "�����������娸����������������������������������������������������";
	const std::string LATIN_alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	const std::string digits = "0123456789";
	//��������.
	for (const auto& ch : key_word) {
		if (type_alphabet == "RUS") {
			if (RUS_alphabet.find(ch) != std::string::npos || digits.find(ch) != std::string::npos)
				continue;
			else
				return false;
		}
		else { //type_alphabet == "LATIN"
			if (LATIN_alphabet.find(ch) != std::string::npos || digits.find(ch) != std::string::npos)
				continue;
			else
				return false;
		}
	}
	return true;
}
//���������� ������� ��������.
std::string ViginerEncryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet)
{
	std::string result{};

	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33;
		const std::string russian_upper = "�����Ũ��������������������������";
		const std::string russian_lower = "��������������������������������";
		const std::string digits = "0123456789";

		// ��������� ������� ��� ��������, ������� ��������� (� ��������)
		size_t cipher_count{};

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				size_t pos_open_symbol = russian_upper.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char encrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = russian_upper.find(key_symbol);
					else
						pos_key_symbol = russian_lower.find(key_symbol);
					encrypted = russian_upper[(pos_open_symbol + pos_key_symbol) % RUSSIAN_M];
				}
				else {
					encrypted = russian_upper[(pos_open_symbol + digits.find(key_symbol)) % RUSSIAN_M];
				}
				result += encrypted;
				++cipher_count; // ����������� ������� ������ ��� ��������� ��������
			}
			else if (russian_lower.find(c) != std::string::npos) {
				size_t pos_open_symbol = russian_lower.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char encrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = russian_upper.find(key_symbol);
					else
						pos_key_symbol = russian_lower.find(key_symbol);
					encrypted = russian_lower[(pos_open_symbol + pos_key_symbol) % RUSSIAN_M];
				}
				else {
					encrypted = russian_lower[(pos_open_symbol + digits.find(key_symbol)) % RUSSIAN_M];
				}
				result += encrypted;
				++cipher_count;
			}
			else {
				result += c; // ��� ����������� �������� ���� �� ������������
			}
		}
	}
	else if (type_alphabet == "LATIN") {
		const int LATIN_M = 26;
		const std::string latin_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string latin_lower = "abcdefghijklmnopqrstuvwxyz";
		const std::string digits = "0123456789";

		size_t cipher_count{};

		for (const char& c : text) {
			if (latin_upper.find(c) != std::string::npos) {
				size_t pos_open_symbol = latin_upper.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char encrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = latin_upper.find(key_symbol);
					else
						pos_key_symbol = latin_lower.find(key_symbol);
					encrypted = latin_upper[(pos_open_symbol + pos_key_symbol) % LATIN_M];
				}
				else {
					encrypted = latin_upper[(pos_open_symbol + digits.find(key_symbol)) % LATIN_M];
				}
				result += encrypted;
				++cipher_count;
			}
			else if (latin_lower.find(c) != std::string::npos) {
				size_t pos_open_symbol = latin_lower.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char encrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = latin_upper.find(key_symbol);
					else
						pos_key_symbol = latin_lower.find(key_symbol);
					encrypted = latin_lower[(pos_open_symbol + pos_key_symbol) % LATIN_M];
				}
				else {
					encrypted = latin_lower[(pos_open_symbol + digits.find(key_symbol)) % LATIN_M];
				}
				result += encrypted;
				++cipher_count;
			}
			else {
				result += c;
			}
		}
	}
	else {
		result += text;
	}

	return result;
}
//������������ ������� ��������.
std::string ViginerDecryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet)
{
	std::string result{};

	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; // ����������� �������� ��������.
		const std::string russian_upper = "�����Ũ��������������������������";
		const std::string russian_lower = "��������������������������������";
		const std::string digits = "0123456789";

		size_t cipher_count{}; // ������� ��� ����������� ��������.

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				size_t pos_encr_symbol = russian_upper.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char decrypted{};
				if (!isdigit(key_symbol)) { // �� �����.
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = russian_upper.find(key_symbol);
					else
						pos_key_symbol = russian_lower.find(key_symbol);
					decrypted = russian_upper[(pos_encr_symbol + RUSSIAN_M - pos_key_symbol) % RUSSIAN_M];
				}
				else { // �����.
					decrypted = russian_upper[(pos_encr_symbol + RUSSIAN_M - digits.find(key_symbol)) % RUSSIAN_M];
				}
				result += decrypted;
				++cipher_count; // ����������� ������ ���� ������ ���������
			}
			else if (russian_lower.find(c) != std::string::npos) {
				size_t pos_encr_symbol = russian_lower.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char decrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = russian_upper.find(key_symbol);
					else
						pos_key_symbol = russian_lower.find(key_symbol);
					decrypted = russian_lower[(pos_encr_symbol + RUSSIAN_M - pos_key_symbol) % RUSSIAN_M];
				}
				else {
					decrypted = russian_lower[(pos_encr_symbol + RUSSIAN_M - digits.find(key_symbol)) % RUSSIAN_M];
				}
				result += decrypted;
				++cipher_count;
			}
			else {
				result += c;
			}
		}
	}
	else if (type_alphabet == "LATIN") {
		const int LATIN_M = 26; // ����������� ���������� ��������.
		const std::string latin_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string latin_lower = "abcdefghijklmnopqrstuvwxyz";
		const std::string digits = "0123456789";

		size_t cipher_count{};

		for (const char& c : text) {
			if (latin_upper.find(c) != std::string::npos) {
				size_t pos_encr_symbol = latin_upper.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char decrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = latin_upper.find(key_symbol);
					else
						pos_key_symbol = latin_lower.find(key_symbol);
					decrypted = latin_upper[(pos_encr_symbol + LATIN_M - pos_key_symbol) % LATIN_M];
				}
				else {
					decrypted = latin_upper[(pos_encr_symbol + LATIN_M - digits.find(key_symbol)) % LATIN_M];
				}
				result += decrypted;
				++cipher_count;
			}
			else if (latin_lower.find(c) != std::string::npos) {
				size_t pos_encr_symbol = latin_lower.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char decrypted{};
				if (!isdigit(key_symbol)) {
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = latin_upper.find(key_symbol);
					else
						pos_key_symbol = latin_lower.find(key_symbol);
					decrypted = latin_lower[(pos_encr_symbol + LATIN_M - pos_key_symbol) % LATIN_M];
				}
				else {
					decrypted = latin_lower[(pos_encr_symbol + LATIN_M - digits.find(key_symbol)) % LATIN_M];
				}
				result += decrypted;
				++cipher_count;
			}
			else {
				result += c;
			}
		}
	}
	else {
		result += text;
	}

	return result;
}

//���������� ������� �������� - ���������.
void ViginerProcess() {
	//���������.
	std::cout << "���������� ������� ��������.  �������������� ���������� ������� �������� -> ������� �������, "
		"��������� �������� -> ��������� �������." << std::endl;
	DrawLine();
	std::cout << std::endl;
	while (true) {
		//������.
		std::cout << "������� ������ ��� ���������� (quit - �����): ";
		std::string open_text{};
		std::getline(std::cin, open_text);
		if (open_text == "quit") break;
		//�������� ������ �� �����������.
		const std::string type_alphabet{ CheckMixedAlphabet(open_text) };
		if (type_alphabet == "MIXED") {
			std::cout << "������! ������ ��� ���������� ������ ��������� ������� �� �������� ���������. ���������� �����." << std::endl << std::endl;
			continue;
		}

		//�������� ������������� ���������.
		if (type_alphabet == "NONE") {
			std::cout << "***���������/����������� ������!***" << std::endl;
			std::cout << "������������� ������: " << open_text << std::endl;
			std::cout << "������������� ������: " << open_text << std::endl;
			DrawLine();
			std::cout << std::endl;
			continue;
		}

		//����.
		std::cout << "������� �������� ����� (������� " << ((type_alphabet == "RUS") ? "�������� " : "���������� ") << "�������� � ����� (0-9) (quit - �����)." << std::endl;
		std::cout << "����: ";
		std::string key_word{};
		std::getline(std::cin, key_word);
		if (key_word == "quit") break;
		//�������� ����� �� ������������.
		if (!CheckKeyViginer(key_word, type_alphabet)) {
			std::cout << "������ ��� ����� �����! ���������� �����." << std::endl << std::endl;
			continue;
		}

		//���������.
		std::string encrypt_str{ ViginerEncryption(open_text, key_word, type_alphabet)};
		std::string	decrypt_str{ ViginerDecryption(encrypt_str, key_word, type_alphabet)};

		//�����.
		DisplayViginerTable(type_alphabet, open_text, key_word, encrypt_str);
		std::cout << "������������� ������: " << encrypt_str << std::endl;
		std::cout << "������������� ������: " << decrypt_str << std::endl;
		DrawLine();
		std::cout << std::endl;
	}
}
//����� ������� ��������.
void DisplayViginerTable(const std::string& type_alphabet, const std::string& open_text, const std::string& key_word, const std::string& encrypt_word) {
	//����������� ��������.
	std::string alphabet{};
	if (type_alphabet == "RUS") alphabet = "�����������娸����������������������������������������������������";
	else if (type_alphabet == "LATIN") alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	else return;

	const int col_width{ 3 }; //������ �������.

	//���������.
	std::cout << std::endl;
	HorizontalDoubleLineForTable(col_width * 14 + col_width * 4 + 14);
	std::cout << "|" << CenterText("���������� ������� ���������� �� ������ ��������", col_width * 14 + col_width * 4 + 14) << "|" << std::endl;
	HorizontalDoubleLineForTable(col_width * 14 + col_width * 4 + 14);

	//����� ������� �����������.
	int columns{ 14 };
	int steps = static_cast<int>(open_text.size()) / columns + ((static_cast<int>(open_text.size()) % columns) == 0 ? 0 : 1);
	int shift{};
	//�����.
	for (size_t iter = 0; iter < steps; ++iter) {
		//��������.
		for (size_t row = 0; row < 3; ++row) {
			switch (row) {
			case 0:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("���������", col_width * 4) << "|";
				//�������.
				for (size_t col = 0; col < columns; ++col) {
					if (iter * columns + col < open_text.size())
						std::cout << std::right << std::setw(col_width) << open_text[iter * columns + col] << "|";
					else
						std::cout << std::right << std::setw(col_width) << " " << "|";
				}
				break;
			case 1:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("����", col_width * 4) << "|";
				// �������.
				for (size_t col = 0; col < columns; ++col) {
					size_t index = iter * columns + col;
					if (index < open_text.size()) {
						char current_char = open_text[index];
						// ��������, �������� �� ������ ������ ��������
						if (alphabet.find(current_char) != std::string::npos) {
							std::cout << std::right << std::setw(col_width)
								<< key_word[(index - shift) % key_word.size()] << "|";
						}
						else {
							std::cout << std::right << std::setw(col_width) << " " << "|";
							++shift; // ����������� �������� ������ ���� ������ �� ���������
						}
					}
					else {
						std::cout << std::right << std::setw(col_width) << " " << "|";
					}
				}
				break;
			case 2:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("����������", col_width * 4) << "|";
				for (size_t col = 0; col < columns; ++col) {
					if (iter * columns + col < encrypt_word.size())
						std::cout << std::right << std::setw(col_width) << encrypt_word[iter * columns + col] << "|";
					else
						std::cout << std::right << std::setw(col_width) << " " << "|";
				}
				break;
			default:;
			}
			std::cout << std::endl;
			if (row != 2) HorizontalLineForTable(col_width * 14 + col_width * 4 + 14);
		}
		HorizontalDoubleLineForTable(col_width * 14 + col_width * 4 + 14);
	}
}