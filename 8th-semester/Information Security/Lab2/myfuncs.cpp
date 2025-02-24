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
	std::cout << "��� ����� ��������:" << std::endl <<
		"1 - �������������� � ������" << std::endl <<
		"2 - ����� �� �������" << std::endl <<
		"0 - ����� �� ���������" << std::endl;
}
//������ �������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "0")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 0 �� 2). ��������� ����:" << std::endl;
		}
	}
}
//���������������� �������.
void SubMenuForChoices(const std::string& object_name) {
	std::cout << "����� �������� � ������ " << object_name << " �� ������ ���������?" << std::endl <<
		"1 - ������ �����" << std::endl <<
		"2 - ������ � ����" << std::endl <<
		"3 - �������� ����" << std::endl <<
		"0 - �����" << std::endl;
}
//������ �������� � �������.
char getSubmenuCase(const std::string& object_name) {
	while (true)
	{
		SubMenuForChoices(object_name);
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "0")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "������ �����, ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 0 �� 3). ��������� ����:" << std::endl;
		}
	}
}


/*�������������� �������*/
//������� ��� ��������� �������������� ����� �������.
void horizontal_table_line(const int& col_width, const std::vector<std::string>& objects) {
	std::cout << "\n" << std::string(col_width * (objects.size() + 1) + objects.size() + 2, '-') << "\n";
}
//������� ��� ������������� ������.
std::string center_text(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // ��������� ������������.
	int left_padding = padding / 2;  // ����� �����.
	int right_padding = padding - left_padding; // ������ �����.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//������� ��� �������������� ������ ������� � ������ ����.
std::string access_level_to_string(const int& access) {
	std::string result = "";

	//�������� ������� ���� � ���������� ���������������� �������.
	result += (access & 4) ? "R" : "-"; // ������.
	result += (access & 2) ? "W" : "-"; // ������.
	result += (access & 1) ? "G" : "-"; // �������� ����.

	return result;
}
//������� ��������� �������������� �����.
void draw_line() {
	std::cout << std::string(200, '-') << std::endl;
}
//����� �������� �� ��������������.
int find_subject(const std::vector<std::string> subjects, const std::string subject_name) {
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
int find_object(const std::vector<std::string> objects, const std::string object_name) {
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
//����� �������.
void display_table(const std::vector<std::string> subjects, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix) {
	const int col_width{ 20 }; // ������ �������.

	//��������� �������.
	horizontal_table_line(col_width, objects);
	std::cout << "|" << center_text("������� ������� ��������� � ��������", col_width * (objects.size() + 1) + objects.size()) << "|";
	horizontal_table_line(col_width, objects);
	//����� �������.
	std::cout << "|" << center_text("������� / ������", col_width) << "|";
	for (const auto& obj : objects) {
		std::cout << center_text(obj, col_width) << "|";
	}
	horizontal_table_line(col_width, objects);
	// ����� ����� �������.
	for (size_t i = 0; i < subjects.size(); ++i) {
		std::cout << "|" << center_text(subjects[i], col_width) << "|"; // ��� ��������.
		for (size_t j = 0; j < objects.size(); ++j) {
			std::cout << center_text(access_level_to_string(access_matrix[i][j]), col_width) << "|"; //������� �������.
		}
		if (i != objects.size() - 1) { std::cout << "\n"; }
	}
	horizontal_table_line(col_width, objects);
	std::cout << std::endl;
}
//������� ��� ��������� ������� �������
void generate_access_matrix(std::vector<std::vector<int>>& access_matrix) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //����.
	for (size_t i = 0; i < access_matrix.size(); i++) {
		for (size_t j = 0; j < access_matrix[i].size(); j++) {
			access_matrix[i][j] = (i == 0) ? 7 : rand() % 8; // ������������� �������� ������ ������.
		}
	}
}
//������ �������������� ������������.
int enter_the_program(const std::vector<std::string>& subjects) {
	std::string subject_name{};
	std::cout << "����������, ������� ���� ����� ��� �����! (quit - �����)" << std::endl;
	while (true) {
		std::getline(std::cin, subject_name);
		if (subject_name == "quit") return -1;
		int subject_index = find_subject(subjects, subject_name);
		if (subject_index != -1) {
			draw_line();
			std::cout << std::endl << "������������, " << subjects[subject_index] << "!\n����� ���������� � �������!" << std::endl << std::endl;
			return subject_index;
		}
		std::cout << "������ �������������. ���������� ����� ��� ������� �� ���������:" << std::endl;
	}
}
//����� ���� �������� ��� ��������.
void display_subject_permissions(const int& subject_index, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix) {
	std::cout << "�������� ����� ����:" << std::endl;
	for (size_t i = 0; i < objects.size(); ++i) {
		std::cout << objects[i] << " -> " << access_level_to_string(access_matrix[subject_index][i]) << std::endl;
	}
}
//����� �����.
void file_choice(const int& subject_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects, 
	std::vector<std::vector<int>>& access_matrix) 
{
	while (true) {
		std::cout << "� ����� ������ �� ������ �����������������? ������� �������� �����: (quit - �����)" << std::endl;
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = find_object(objects, object_name);
		if (object_index == -1) {
			std::cout << "������ ���� �� ��� ��������� � �������. ���������� �����." << std::endl << std::endl;
			continue;
		}

		while (true) {
			if (!file_interract(subject_index, object_index, subjects, objects, access_matrix)) {
				std::cout << "������ � ������ " << object_name << " ���������!" << std::endl << std::endl;
				break;
			}
		}
	}
}
//�������������� � ������.
bool file_interract(const int& subject_index, const int& object_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects,
	std::vector<std::vector<int>>& access_matrix)
{
	std::cout << std::endl;
	bool access{};

	switch (getSubmenuCase(objects[object_index])) {
	case '1'://������.
		access = check_permission(access_matrix, subject_index, object_index, 2);
		if (access) {
			std::cout << std::endl << "������ �����...\n���� ������� ��������!" << std::endl;
		}
		else
			std::cout << "�������� � �������! � ��� ��� ���� ��� ���������� ����� ��������!" << std::endl;
		break;
	case '2'://������.
		access = check_permission(access_matrix, subject_index, object_index, 1);
		if (access) {
			std::cout << std::endl << "���� ������ � ����...\n���� ������� �����������!" << std::endl;
		}
		else
			std::cout << "�������� � �������! � ��� ��� ���� ��� ���������� ����� ��������!" << std::endl;
		break;
	case '3'://�������� ����.
		access = check_permission(access_matrix, subject_index, object_index, 0);
		if (access) {
			modify_access_matrix(subjects, object_index, access_matrix, subject_index);
		}
		else
			std::cout << "�������� � �������! � ��� ��� ���� ��� ���������� ����� ��������!" << std::endl;
		break;
	case '0'://�����.
		return false;
	default:;
	}
	return true;
}
//�������� ���� �������� ��� ��������.
bool check_permission(const std::vector<std::vector<int>>& access_matrix, const int& subject_index, const int& object_index, const int& bit) {
	return (access_matrix[subject_index][object_index] >> bit) % 2 == 1;
}
//�������������� ������� ������� ��� �������� ����.
void modify_access_matrix(const std::vector<std::string>& subjects, const int& target_object_index, std::vector<std::vector<int>>& access_matrix, const int& subject_index){
	while (true) {
		//���� ���������� �����.
		std::cout << std::endl;
		std::cout << "���� �� ������ �������� ������? ������� �������������: (quit - �����)" << std::endl;
		std::cout << "��� ������������: ";
		std::string target_subject_name{};
		std::getline(std::cin, target_subject_name);
		if (target_subject_name == "quit") return;
		int target_subject_index = find_subject(subjects, target_subject_name);
		if (target_subject_index == -1) {
			std::cout << "��������� ������������� �� ��������� � �������. ���������� ������." << std::endl;
			continue;
		}

		//��������, �� �������� �� ������������ ����� ������ ����.
		if (target_subject_index == subject_index) {
			std::cout << "�������� ���� ������ ���� ���������! ������ ����������� �������� ����� ������� ������������ ��� ��������� ������ � ������." << std::endl;
			continue;
		}

		//����� ����� ����������.
		std::cout << "������� �����: (read/write/grant)" << std::endl;
		std::cout << "�����: ";
		std::string right{};
		std::getline(std::cin, right);
		if (right == "read" || right == "write" || right == "grant") {
			int right_value = (right == "read") ? 4 : (right == "write") ? 2 : (right == "grant") ? 1 : 0;
			
			//��������, ���� �� � ��������, ����������� �����, ��� ����� ��� ��������.
			if (!(access_matrix[subject_index][target_object_index] & right_value)) {
				std::cout << "������: �� �� ������ �������� ����� '" << right << "' ������������ " << target_subject_name << ", �.�. �� ��������� ���� ������!\n";
				continue;
			}

			//��������, ���� �� � ��������, �������� ���������� �����, ��� ��� ����� ��� ��������.
			if (access_matrix[target_subject_index][target_object_index] & right_value) {
				std::cout << "������: ������������ " << target_subject_name << " ��� �������� ������ '" << right << "'!\n";
				continue;
			}

			//�������� ����.
			access_matrix[target_subject_index][target_object_index] |= right_value;
			std::cout << "���� �������� ���� ������������ " << target_subject_name << "...\n����� ������� ��������!" << std::endl;
			break;
		}
		else {
			std::cout << "��������� ����� �����������. ���������� ������." << std::endl;
		}
	}
}