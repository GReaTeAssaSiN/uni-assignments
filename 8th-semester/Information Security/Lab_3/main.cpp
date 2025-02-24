#include <iostream>
#include <vector>
#include <string>
//#include <map>
#include <cstdlib> //system()
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	//Задание исходных структур.
	std::vector<std::string> subjects = { "Alex", "User_1", "User_2", "User_3" }; //Массив субъектов (Длина - 4).
	std::vector<std::string> objects = { "File_1.txt", "File_2.txt", "File_3.txt", "File_4.txt", "File_5.txt", "File_6.txt" }; //Массив объектов (Длина - 6).
	/*std::map<int, std::string> PERMISSIONS = {
		{0, "NONCONFIDENTIAL"}, {1, "CONFIDENTIAL"}, {2, "SECRET"}, {3, "TOP SECRET"}
	};*/
	//Модель БЛМ (Белла-ЛаПадулы).
	std::vector<int> subjects_level_access(subjects.size()); //Уровни доступа субъектов.
	std::vector<int> objects_level_access(objects.size()); //Грифы секретности объектов.
	//Заполнение модели БЛМ случайным образом с учетом наличия админа Alex первым элементом массива субъектов.
	GenerateModelBLM(subjects_level_access, objects_level_access);
	//Программная копия уровней доступа субъектов.
	std::vector<int> COPY_subjects_level_access(subjects_level_access);
	//Отображение модели БЛМ.
	DisplayModelBLM(subjects, objects, subjects_level_access, objects_level_access);
	//Вход в программу.
	int subject_index{ EnterTheProgram(subjects) };
	if (subject_index != -1) {
		//Цикл работы с программой.
		bool cycle{ true };
		while (cycle){
			if (subject_index == -1) break;
			switch (GetCase()) {
			case '1'://Чтение.
				DrawLine();
				std::cout << std::endl;
				ReadTheObjectBySubject(subjects_level_access[subject_index], objects, objects_level_access);
				break;
			case '2'://Запись.
				DrawLine();
				std::cout << std::endl;
				WriteToObjectBySubject(subjects_level_access[subject_index], objects, objects_level_access);
				break;
			case '3'://Изменение.
				DrawLine();
				std::cout << std::endl;
				ChangeLevelAccessBySubject(COPY_subjects_level_access, subjects_level_access, subject_index);
				break;
			case '4'://Показать модель БЛМ.
				DrawLine();
				std::cout << std::endl;
				DisplayModelBLM(subjects, objects, subjects_level_access, objects_level_access);
				break;
			case '0'://Выход.
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