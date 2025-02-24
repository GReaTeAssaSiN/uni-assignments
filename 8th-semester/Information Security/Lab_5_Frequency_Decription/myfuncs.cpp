#include <iostream>
#include "mystruct.h"
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
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1: >������������ ��������� ������ ��������" << std::endl <<
		"2: >����������� ��������� ����" << std::endl <<
		"0: >����� �� ���������" << std::endl;
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
void DrawLine(const char& del) {
	std::cout << std::endl << "|" << std::string(200, del) << "|" << std::endl;
}
//������� ��� ������������� ������.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // ��������� ������������.
	int left_padding = padding / 2;  // ����� �����.
	int right_padding = padding - left_padding; // ������ �����.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}

/*�������� �������*/
//��������� �������������� ������������ ��� ������� ����������� ��������.
void AnalyzeFrequencyProcess() 
{
	while (true) {
		//���� ����� ��� �������.
		std::string file_in{};
		std::cout << "��� ���������� ������� ����, ������� ���� ����������������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������� [opentext.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_in);
		if (file_in == "quit") break;
		if (file_in.empty()) file_in = "opentext.txt";

		//��������� ��� ��������� � ������� ������ ����� ��������.
		std::map<unsigned char, CharInfo> freq{};
		int total_chars = 0;

		//1. ������ �����.
		if (!analyzeFile(file_in, freq, total_chars)) break;
		DrawLine('-');
		std::cout << std::endl;
		//2. ���������� ����������� ����������� ����������� ��������.
		computePercentages(freq, total_chars);
		//3. ����� �����������.
		std::string file_out{};
		std::cout << "��� ���������� ������� ����, � ������� ���� ������� ����������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������ ����������� [ANALYZE_opentext.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_out);
		if (file_out == "quit") break;
		if (file_out.empty()) file_out = "ANALYZE_opentext.txt";
		if (!writeResults(file_out, freq)) break;

		DrawLine('-');
		std::cout << std::endl;
		
		//�����.
		std::cout << "�����: ���� " << file_in << " ��� ������� ���������������, ��������� ������ �������� ������� � ���� " << file_out << "!" << std::endl;
	
		DrawLine('=');
		std::cout << std::endl;
	}
	return;
}
//��������� �������������� ������������ ��� ����������� �������� � ��������� �����.
void DecryptFileProcess()
{
	while (true) {
		//���� ����� � �������� ������� ��� �������.
		std::string file_freq1{};
		std::cout << "��� ���������� ������� ���� � �������� �������, ������� ���� ����������������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������� [opentext.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_freq1);
		if (file_freq1 == "quit") break;
		if (file_freq1.empty()) file_freq1 = "opentext.txt";

		DrawLine('-');
		std::cout << std::endl;

		//���� ����� � ������������� ������� ��� �������.
		std::string file_freq2{};
		std::cout << "��� ���������� ������� ���� � ������������� �������, ������� ���� ����������������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������� [open.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_freq2);
		if (file_freq2 == "quit") break;
		if (file_freq2.empty()) file_freq2 = "open.txt";

		DrawLine('-');
		std::cout << std::endl;

		//���� ������������� �����.
		std::string file_encrypt{};
		std::cout << "��� ���������� ������� ���� � �������, ������� ���� ������������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������� [" << file_freq2 << " - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_encrypt);
		if (file_encrypt == "quit") break;
		if (file_encrypt.empty()) file_encrypt = file_freq2;

		DrawLine('-');
		std::cout << std::endl;

		//����� ����������� (�����������).
		std::string file_decrypt{};
		std::cout << "��� ���������� ������� ����, � ������� ���� ������� ���������� �����������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������ ����������� [DECRYPT_open.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_decrypt);
		if (file_decrypt == "quit") break;
		if (file_decrypt.empty()) file_decrypt = "DECRYPT_open.txt";

		DrawLine('-');
		std::cout << std::endl;

		//������� ������� ����������� � ��������� ����.
		std::string file_table{};
		std::cout << "��� ���������� ������� ����, ���� ���������� ������� �����������, � ������� <file.txt>." << std::endl;
		std::cout << "���� ��� ������ ������� [TABLE_ENCR_DECR_opentext_open.txt - �� ���������, ������� Enter] (quit - �����) : ";
		std::getline(std::cin, file_table);
		if (file_table == "quit") break;
		if (file_table.empty()) file_table = "TABLE_ENCR_DECR_opentext_open.txt";

		DrawLine('-');

		//������.
		if (!decryptFile(file_freq1, file_freq2, file_encrypt, file_decrypt, file_table)) break;
		else std::cout << std::endl;

		//�����.
		std::cout << "�����: ���� " << file_encrypt << " ��� ������� �����������, ���������� �������� � ���� " << file_decrypt << "!"
			<< std::endl << "����������� ������������� �� ������ ���������� ������� �������� ��������� ������: " << file_freq1 << " -> " 
			<< file_freq2 << "." << std::endl
			<< "������� ����������� �������� � ���� " << file_table << "." << std::endl
			<< "���� �� ������ ���������� ����� � ��������� ��������, ��������� ������� 1 ���� ��������� ��� ����������� ������:)" << std::endl;

		DrawLine('=');
		std::cout << std::endl;
	}
	return;
}
//������� ��� ���������� �� �������� ���������� ���������.
bool compare(const std::pair<unsigned char, CharInfo>& a, const std::pair<unsigned char, CharInfo>& b) {
	if (a.second.count == b.second.count) {
		return a.first < b.first;
	}
	return a.second.count > b.second.count;
}
//������� ��� ������� ������� �������� � �����.
bool analyzeFile(const std::string& inputFilename, std::map<unsigned char, CharInfo>& freq, int& total_chars) 
{
	std::ifstream file(inputFilename, std::ios::binary); //�������� ����� � �������� ������.

	if (!file) {
		std::cerr << std::endl << "������: �� ������� ������� ���� " << inputFilename << "!" << std::endl;
		return false;
	}

	std::cout << std::endl << "���� " << inputFilename << " �������������. ����������, ���������..." << std::endl;

	//������� ������� ��������.
	char ch{};
	while (file.get(ch)) {
		unsigned char uch = static_cast<unsigned char>(ch);
		freq[uch].character = uch;
		freq[uch].count++;
		total_chars++;
	}

	file.close(); //�������� ��������� �����.
	std::cout << std::endl << "���� " << inputFilename << " ��� ������� ���������������!" << std::endl;

	return true;
}
//������� ��� ���������� ����������� ����������� ����������� ��������.
void computePercentages(std::map<unsigned char, CharInfo>& freq, int total_chars)
{
	for (auto& pair : freq) {
		pair.second.percentage = (pair.second.count * 100.0) / total_chars;
	}
}
//������� ��� ������ ����������� � ����.
bool writeResults(const std::string& outputFilename, const std::map<unsigned char, CharInfo>& freq)
{
	//�������� ��������� ����� � ������������.
	std::ofstream outFile(outputFilename);
	if (!outFile) {
		std::cerr << std::endl << "������: �� ������� ������� ���� " << outputFilename << "!" << std::endl;
		return false;
	}

	std::cout << std::endl << "� ���� " << outputFilename << " ��������� ����������. ����������, ���������..." << std::endl;

	//���������� �����������.
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq(freq.begin(), freq.end());
	std::sort(sorted_freq.begin(), sorted_freq.end(), compare);

	//������ ���������� �������.
	outFile << "NN\tDEC\tHEX\tCHAR\tCOUNT\t%\n";

	int index{ 1 };
	for (const auto& pair : sorted_freq) {
		unsigned char uch = pair.first;
		//���� ������ �� ��������, �� ����������� ����� �� ����������� �������.
		std::string charRep = std::isprint(uch) ? std::string(1, uch)
			: (uch == 13 ? "\\r"                              
				: (uch == 10 ? "\\n"                          
					: std::string(1, uch)));

		//�������������� 16-������� ������ (������� �������).
		std::stringstream hexStream{};
		hexStream << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(uch);

		outFile << index++ << "\t"
			<< static_cast<int>(uch) << "\t"
			<< hexStream.str() << "\t"
			<< charRep << "\t"
			<< pair.second.count << "\t"
			<< std::fixed << std::setprecision(3) << pair.second.percentage << "%" << "\n";
	}

	outFile.close(); //�������� ��������� �����.
	std::cout << std::endl << "���������� �������� � ���� " << outputFilename << std::endl;
	
	return true;
}
//������� ��� ����������� ���������� ����� �� ������������ ������.
bool decryptFile(const std::string& freqFile1, const std::string& freqFile2,
	const std::string& inputFilename, const std::string& outputFilename, const std::string& file_table) {
	//����� ��� �������� ������.
	std::map<unsigned char, CharInfo> freq1{}, freq2{};
	int total_chars1{}, total_chars2{};

	//����������� ��� ����� � ���������.
	//���� � �������� �������.
	if (!analyzeFile(freqFile1, freq1, total_chars1)) return false;
	//���� � ������������� �������.
	if (!analyzeFile(freqFile2, freq2, total_chars2)) return false;
	computePercentages(freq1, total_chars1);
	computePercentages(freq2, total_chars2);

	//��������� �������.
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq1(freq1.begin(), freq1.end());
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq2(freq2.begin(), freq2.end());
	std::sort(sorted_freq1.begin(), sorted_freq1.end(), compare);
	std::sort(sorted_freq2.begin(), sorted_freq2.end(), compare);

	//������� ������� �����������.
	std::vector<std::pair<unsigned char, unsigned char>> substitution{};// ���� - ������������� ������, �������� - �������������� ������.
	for (size_t i = 0; i < std::min(sorted_freq1.size(), sorted_freq2.size()); ++i) {
		substitution.emplace_back(sorted_freq2[i].first, sorted_freq1[i].first);//������������� ������ -> ������ ��������� ������.
	}

	//����� ������� � ����.
	if (!saveSubstitutionTable(substitution, file_table)) return false;

	//��������� ������������� ���� � ���� ��� ��������������� ������.
	std::ifstream inputFile(inputFilename, std::ios::binary);//������������� ����.
	std::ofstream outputFile(outputFilename, std::ios::binary);//���� �����������.
	if (!inputFile || !outputFile) {
		std::cerr << std::endl << "������: �� ������� ������� ������� ��� �������� ����!" << std::endl;
		return false;
	}

	//�������� ������� �� ������� �����������.
	char ch{};
	while (inputFile.get(ch)) {
		unsigned char uch = static_cast<unsigned char>(ch);
		bool replaced{};
		//���� ������������� ������.
		for (const auto& pair : substitution) {
			if (pair.first == uch) {  // ���� ������ ������ � �������,
				outputFile.put(pair.second); //�� ��������.
				replaced = true;
				break;
			}
		}

		if (!replaced) {  // ���� ������ �� ��� �������, ��������� ��� ��� ����.
			outputFile.put(ch);
		}
	}

	//�������� ������.
	inputFile.close();
	outputFile.close();
	std::cout << std::endl << "����������� ���������! ��������� ������� � " << outputFilename << std::endl;

	return true;
}
//������� ��� ���������� ������� ����������� � ��������� ����.
bool saveSubstitutionTable(const std::vector<std::pair<unsigned char, unsigned char>>& substitution, const std::string& filename) 
{
	std::ofstream tableFile(filename);
	if (!tableFile) {
		std::cerr << std::endl << "������: �� ������� ������� ���� ��� ������� �����!" << std::endl;
		return false;
	}

	tableFile << "������� ����� ��������� ����������" << std::endl;
	//������ ���������� �������.
	tableFile << "NN\tENCR_S\t\tDECR_S\n";

	int index{ 1 };
	for (const auto& pair : substitution) {
		unsigned char encr_s = pair.first;
		unsigned char decr_s = pair.second;
		
		std::string encr_s_Rep = std::isprint(encr_s) ? std::string(1, encr_s)
			: (encr_s == 13 ? "\\r"
				: (encr_s == 10 ? "\\n"
					: std::string(1, encr_s)));

		std::string decr_s_Rep = std::isprint(decr_s) ? std::string(1, decr_s)
			: (decr_s == 13 ? "\\r"
				: (decr_s == 10 ? "\\n"
					: std::string(1, decr_s)));

		tableFile << index++ << "\t"
			<< encr_s_Rep << "\t"
			<< "->" << "\t"
			<< decr_s_Rep << "\n"; 
	}

	tableFile.close();
	std::cout << std::endl << "������� ����� ��������� � " << filename << std::endl;
	
	return true;
}