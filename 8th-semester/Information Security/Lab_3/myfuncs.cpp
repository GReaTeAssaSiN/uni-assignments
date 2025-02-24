#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //rand() � srand()
#include <ctime>   //time()
#include <iomanip>
#include "myfuncs.h"

/*���������������� �������*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "������ ������ ��� ������ � ��������:" << std::endl <<
		"1 - ��������� ����" << std::endl <<
		"2 - �������� � ����" << std::endl <<
		"3 - �������� ������� �������" << std::endl <<
		"4 - �������� ������ ���" << std::endl <<
		"0 - ����� �� �������" << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "0")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 0 �� 4). ��������� ����:" << std::endl;
		}
	}
}

/*�������������� �������*/
//������� ��� ��������� �������������� ����� �������.
void HorizontalLineForModel(const int& col_width) {
	std::cout << std::string(col_width * 2 + 3, '-') << std::endl;
}
//������� ��� ������������� ������.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // ��������� ������������.
	int left_padding = padding / 2;  // ����� �����.
	int right_padding = padding - left_padding; // ������ �����.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//������� ��� �������������� ������ �������/����� ����������� � ������.
std::string AccessLevelToString(const int& access) {
	std::string result = "";

	switch (access) {
	case 0:
		result += "NONCONFIDENTIAL";
		break;
	case 1:
		result += "CONFIDENTIAL";
		break;
	case 2:
		result += "SECRET";
		break;
	case 3:
		result += "TOP SECRET";
		break;
	default:;
	}

	return result;
}
//������� ��� �������������� ������ �������/����� ����������� � ��������.
int AccessLevelToValue(const std::string& access) {
	if (access == "NONCONFIDENTIAL") return 0;
	else if (access == "CONFIDENTIAL") return 1;
	else if (access == "SECRET") return 2;
	else if (access == "TOP SECRET") return 3;
	else return -1;
}
//������� ��������� �������������� �����.
void DrawLine() {
	std::cout << std::string(200, '-') << std::endl;
}
//����� �������� �� ��������������.
int FindSubject(const std::vector<std::string> subjects, const std::string subject_name) {
	int subject_index{ -1 };
	for (size_t i = 0; i < subjects.size(); ++i) {
		if (subjects[i] == subject_name) {
			subject_index = static_cast<int>(i);
			break;
		}
	}
	return subject_index;
}
//����� ������� �� ��������.
int FindObject(const std::vector<std::string> objects, const std::string object_name) {
	int object_index{ -1 };
	for (size_t i = 0; i < objects.size(); ++i) {
		if (objects[i] == object_name) {
			object_index = static_cast<int>(i);
			break;
		}
	}
	return object_index;
}


/*�������� �������*/
//����������� ������ ���.
void DisplayModelBLM(const std::vector<std::string>& subjects, const std::vector<std::string>& objects, 
	const std::vector<int>& subjects_level_access, const std::vector<int>& objects_level_access) 
{
	const int col_width{ 20 }; //������ �������.

	//���������.
	std::cout << std::endl;
	HorizontalLineForModel(col_width);
	std::cout << "|" << CenterText("������ ���", col_width * 2 + 1) << "|" << std::endl;
	HorizontalLineForModel(col_width);

	//����� ��� ���������.
	std::cout << "|" << std::right << std::setw(col_width) << "�������������" << "|" << std::right << std::setw(col_width) << "������� �������" << "|" << std::endl;
	HorizontalLineForModel(col_width);
	//������ ��� ���������.
	for (size_t i = 0; i < subjects.size(); ++i) {
		std::cout << "|" << std::right << std::setw(col_width) << subjects[i] << "|" << std::right << std::setw(col_width) << AccessLevelToString(subjects_level_access[i]) << "|" << std::endl;
	}
	HorizontalLineForModel(col_width);

	//����� ��� ��������.
	std::cout << "|" << std::right << std::setw(col_width) << "��������" << "|" << std::right << std::setw(col_width) << "���� �����������" << "|" << std::endl;
	HorizontalLineForModel(col_width);
	//������ ��� ��������.
	for (size_t i = 0; i < objects.size(); ++i) {
		std::cout << "|" << std::right << std::setw(col_width) << objects[i] << "|" << std::right << std::setw(col_width) << AccessLevelToString(objects_level_access[i]) << "|" << std::endl;
	}
	HorizontalLineForModel(col_width);
	std::cout << std::endl;
}
//������� ��� ��������� ������ ���.
void GenerateModelBLM(std::vector<int>& subjects_level_access, std::vector<int>& objects_level_access) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //����.
	//������ ������� ���������.
	for (size_t i = 0; i < subjects_level_access.size(); ++i) {
		subjects_level_access[i] = (i == 0) ? 3 : rand() % 4; //������������� ����� ������� ������� TOP SECRET.
	}
	//����� ����������� ��������.
	for (size_t i = 0; i < objects_level_access.size(); ++i) {
		objects_level_access[i] = rand() % 4;
	}
}
//������ �������������� ������������.
int EnterTheProgram(const std::vector<std::string>& subjects) {
	std::string subject_name{};
	std::cout << "����������, ������� ���� ����� ��� �����! (quit - �����)" << std::endl;
	while (true) {
		std::getline(std::cin, subject_name);
		if (subject_name == "quit") return -1;
		int subject_index = FindSubject(subjects, subject_name);
		if (subject_index != -1) {
			DrawLine();
			std::cout << std::endl << "������������, " << subjects[subject_index] << "!\n����� ���������� � �������!" << std::endl << std::endl;
			return subject_index;
		}
		std::cout << "������ �������������. ���������� ����� ��� ������� �� ���������:" << std::endl;
	}
}
//�������� ������ ������� � ����� �����������.
bool CheckNRU(const int& subject_level_access, const int& object_level_access) {
	return subject_level_access >= object_level_access ? true : false;
}
bool CheckNWD(const int& subject_level_access, const int& object_level_access) {
	return subject_level_access <= object_level_access ? true : false;
}
//������ ����� �������������.
void ReadTheObjectBySubject(const int& subject_level_access, const std::vector<std::string>& objects, const std::vector<int>& objects_level_access) {
	while (true) {
		//������ �������� �������.
		std::cout << "����� ���� �� ������ ���������? (quit - �����)" << std::endl;
		std::cout << "����: ";
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = FindObject(objects, object_name);
		if (object_index == -1) {
			std::cout << "������ ���� �� ��� ��������� � �������. ���������� �����." << std::endl << std::endl;
			continue;
		}

		//�������� ���������� �������� ������.
		if (CheckNRU(subject_level_access, objects_level_access[object_index])) std::cout << "�������� ������ ��������� �������!" << std::endl;
		else std::cout << "�������� �� ���������! ��� ������� ������� ���� ����� ����������� �����." << std::endl;
		break;
	}
	return;
}
//������ � ���� �������������.
void WriteToObjectBySubject(const int& subject_level_access, const std::vector<std::string>& objects, const std::vector<int>& objects_level_access) {
	while (true) {
		//������ �������� �������.
		std::cout << "� ����� ���� �� ������ ��������? (quit - �����)" << std::endl;
		std::cout << "����: ";
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = FindObject(objects, object_name);
		if (object_index == -1) {
			std::cout << "������ ���� �� ��� ��������� � �������. ���������� �����." << std::endl << std::endl;
			continue;
		}
		
		//�������� ���������� �������� ������.
		if (CheckNWD(subject_level_access, objects_level_access[object_index])) std::cout << "�������� ������ ��������� �������!" << std::endl;
		else std::cout << "�������� �� ���������! ��� ������� ������� ���� ����� ����������� �����." << std::endl;
		break;
	}
}
//��������� ������ ������� ������������.
void ChangeLevelAccessBySubject(const std::vector<int>& COPY_subjects_level_access, std::vector<int>& subjects_level_access, const int& subject_index) {
	while (true) {
		//������ ���������� ������ ������� (��������� ��� ��� ��).
		std::cout << "����� ������� ������� �� ������ ��������? ('NONCONFIDENTIAL', 'CONFIDENTIAL', 'SECRET', 'TOP SECRET' ��� quit - �����)" << std::endl;
		std::cout << "������� �������: ";
		std::string subject_target_level_access{};
		std::getline(std::cin, subject_target_level_access);
		if (subject_target_level_access == "quit") return;
		
		//�������� ����������� ��������� ��������� ������ �������.
		int target_level_access{ AccessLevelToValue(subject_target_level_access) };
		if (target_level_access == -1) {
			std::cout << "������ ������ ������� �� ����������! ��������� ����." << std::endl << std::endl;
			continue;
		}

		//��������: ����� ������� ������� �� ����� ��������� ��������.
		if (target_level_access > COPY_subjects_level_access[subject_index]) {
			std::cout << "������ ���������� ������� ������� ���� ��������� �������� ������� ������� �����������! ������� ������� �������: " <<
				AccessLevelToString(subjects_level_access[subject_index]) << ". ��������� ����." << std::endl << std::endl;
			continue;
		}

		//��������: ��������� ���������, ���������� ������ �������.
		subjects_level_access[subject_index] = target_level_access;
		std::cout << "��� ������� ������� ������� ������� �� " << AccessLevelToString(subjects_level_access[subject_index]) << std::endl;
		break;
	}
	return;
}