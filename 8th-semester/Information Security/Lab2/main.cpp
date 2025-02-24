#include <iostream>
#include <vector>
//#include <map>
#include <string>
#include <cstdlib> // system()
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	//������� �������� ��������.
	std::vector<std::string> subjects = { "Alex", "User_1", "User_2", "User_3" }; //������ ��������� (����� - 4).
	std::vector<std::string> objects = { "File_1.txt", "File_2.txt", "File_3.txt", "File_4.txt" }; //������ �������� (����� - 4).
	//std::map<int, std::string> PERMISSIONS = { //��������� ��� �������� ��������� ����� ������� � ��������������� ��������.
	//	{0, "������"}, {1, "��������"}, {2, "������"}, {3, "������, ��������"},
	//	{4, "������"}, {5, "������, ��������"}, {6, "������, ������"}, {7, "������ �����"}
	//};
	std::vector<std::vector<int>> access_matrix(subjects.size(), std::vector<int>(objects.size())); //������� �������.
	//���������� ������� ������� ��������� ������� � ������ ������� ������ Alex �� ������ ������ �������.
	generate_access_matrix(access_matrix);
	//����������� �������� ������.
	display_table(subjects, objects, access_matrix);
	//���� � ���������.
	int user_index{ enter_the_program(subjects) };
	if (user_index != -1) {
		//����� ���� ������������.
		display_subject_permissions(user_index, objects, access_matrix);
		std::cout << std::endl;
		//���� ������ ���������.
		bool cycle{ true };
		while (cycle) {
			switch (getCase()) {
			case '1':
				std::cout << std::endl;
				file_choice(user_index, subjects, objects, access_matrix);
				break;
			case '2':
				system("cls");
				//����������� �������� ������.
				display_table(subjects, objects, access_matrix);
				user_index = enter_the_program(subjects);
				if (user_index != -1) {
					//����� ���� ������������.
					display_subject_permissions(user_index, objects, access_matrix);
				}
				else cycle = false;
				break;
			case '0':
				cycle = false;
				break;
			default:;
			}
			std::cout << std::endl;
		}
	}
	return 0;
}