#include <iostream>
#include <vector>
#include <string>
//#include <map>
#include <cstdlib> //system()
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	//������� �������� ��������.
	std::vector<std::string> subjects = { "Alex", "User_1", "User_2", "User_3" }; //������ ��������� (����� - 4).
	std::vector<std::string> objects = { "File_1.txt", "File_2.txt", "File_3.txt", "File_4.txt", "File_5.txt", "File_6.txt" }; //������ �������� (����� - 6).
	/*std::map<int, std::string> PERMISSIONS = {
		{0, "NONCONFIDENTIAL"}, {1, "CONFIDENTIAL"}, {2, "SECRET"}, {3, "TOP SECRET"}
	};*/
	//������ ��� (�����-��������).
	std::vector<int> subjects_level_access(subjects.size()); //������ ������� ���������.
	std::vector<int> objects_level_access(objects.size()); //����� ����������� ��������.
	//���������� ������ ��� ��������� ������� � ������ ������� ������ Alex ������ ��������� ������� ���������.
	GenerateModelBLM(subjects_level_access, objects_level_access);
	//����������� ����� ������� ������� ���������.
	std::vector<int> COPY_subjects_level_access(subjects_level_access);
	//����������� ������ ���.
	DisplayModelBLM(subjects, objects, subjects_level_access, objects_level_access);
	//���� � ���������.
	int subject_index{ EnterTheProgram(subjects) };
	if (subject_index != -1) {
		//���� ������ � ����������.
		bool cycle{ true };
		while (cycle){
			if (subject_index == -1) break;
			switch (GetCase()) {
			case '1'://������.
				DrawLine();
				std::cout << std::endl;
				ReadTheObjectBySubject(subjects_level_access[subject_index], objects, objects_level_access);
				break;
			case '2'://������.
				DrawLine();
				std::cout << std::endl;
				WriteToObjectBySubject(subjects_level_access[subject_index], objects, objects_level_access);
				break;
			case '3'://���������.
				DrawLine();
				std::cout << std::endl;
				ChangeLevelAccessBySubject(COPY_subjects_level_access, subjects_level_access, subject_index);
				break;
			case '4'://�������� ������ ���.
				DrawLine();
				std::cout << std::endl;
				DisplayModelBLM(subjects, objects, subjects_level_access, objects_level_access);
				break;
			case '0'://�����.
				system("cls");
				DisplayModelBLM(subjects, objects, subjects_level_access, objects_level_access);
				subject_index = EnterTheProgram(subjects);
				if (subject_index == -1) {
					cycle = false;
				}
				break;
			default:;
			}
			DrawLine();
			std::cout << std::endl;
		}
	}
	return 0;
}