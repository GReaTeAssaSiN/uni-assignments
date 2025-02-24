#include <iostream>
#include <vector>
//#include <map>
#include <string>
#include <cstdlib> // system()
#include "myfuncs.h"

int main() {
	setlocale(LC_ALL, "Rus");
	//Задание исходных структур.
	std::vector<std::string> subjects = { "Alex", "User_1", "User_2", "User_3" }; //Массив субъектов (Длина - 4).
	std::vector<std::string> objects = { "File_1.txt", "File_2.txt", "File_3.txt", "File_4.txt" }; //Массив объектов (Длина - 4).
	//std::map<int, std::string> PERMISSIONS = { //Контейнер для хранения множества типов доступа и соответствующих значений.
	//	{0, "Запрет"}, {1, "Передача"}, {2, "Запись"}, {3, "Запись, Передача"},
	//	{4, "Чтение"}, {5, "Чтение, Передача"}, {6, "Чтение, Запись"}, {7, "Полные права"}
	//};
	std::vector<std::vector<int>> access_matrix(subjects.size(), std::vector<int>(objects.size())); //Матрица доступа.
	//Заполнение матрицы доступа случайным образом с учетом наличия админа Alex на первой строке матрицы.
	generate_access_matrix(access_matrix);
	//Отображение исходных данных.
	display_table(subjects, objects, access_matrix);
	//Вход в программу.
	int user_index{ enter_the_program(subjects) };
	if (user_index != -1) {
		//Вывод прав пользователя.
		display_subject_permissions(user_index, objects, access_matrix);
		std::cout << std::endl;
		//Цикл работы программы.
		bool cycle{ true };
		while (cycle) {
			switch (getCase()) {
			case '1':
				std::cout << std::endl;
				file_choice(user_index, subjects, objects, access_matrix);
				break;
			case '2':
				system("cls");
				//Оторбажение исходных данных.
				display_table(subjects, objects, access_matrix);
				user_index = enter_the_program(subjects);
				if (user_index != -1) {
					//Вывод прав пользователя.
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