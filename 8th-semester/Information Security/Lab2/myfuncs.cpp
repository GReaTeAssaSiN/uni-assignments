#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //rand() и srand()
#include <ctime>   //time()
#include <iomanip>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Жду Ваших указаний:" << std::endl <<
		"1 - Взаимодействие с файлом" << std::endl <<
		"2 - Выйти из системы" << std::endl <<
		"0 - Выход из программы" << std::endl;
}
//Запрос дейтсвий у пользователя.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "0")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 0 до 2). Повторите ввод:" << std::endl;
		}
	}
}
//Пользовательское подменю.
void SubMenuForChoices(const std::string& object_name) {
	std::cout << "Какое действие с файлом " << object_name << " Вы хотите совершить?" << std::endl <<
		"1 - Чтение файла" << std::endl <<
		"2 - Запись в файл" << std::endl <<
		"3 - Передача прав" << std::endl <<
		"0 - Выход" << std::endl;
}
//Запрос действий в подменю.
char getSubmenuCase(const std::string& object_name) {
	while (true)
	{
		SubMenuForChoices(object_name);
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "0")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 0 до 3). Повторите ввод:" << std::endl;
		}
	}
}


/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
//Функция для отрисовки горизонтальной линии таблицы.
void horizontal_table_line(const int& col_width, const std::vector<std::string>& objects) {
	std::cout << "\n" << std::string(col_width * (objects.size() + 1) + objects.size() + 2, '-') << "\n";
}
//Функция для центрирования текста.
std::string center_text(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Функция для преобразования уровня доступа в строку прав.
std::string access_level_to_string(const int& access) {
	std::string result = "";

	//Проверка каждого бита и добавление соответствующего символа.
	result += (access & 4) ? "R" : "-"; // Чтение.
	result += (access & 2) ? "W" : "-"; // Запись.
	result += (access & 1) ? "G" : "-"; // Передача прав.

	return result;
}
//Функция отрисовки разделительной черты.
void draw_line() {
	std::cout << std::string(200, '-') << std::endl;
}
//Поиск субъекта по идентификатору.
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
//Поиск объекта по названию.
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

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Вывод таблицы.
void display_table(const std::vector<std::string> subjects, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix) {
	const int col_width{ 20 }; // Ширина столбца.

	//Заголовок таблицы.
	horizontal_table_line(col_width, objects);
	std::cout << "|" << center_text("МАТРИЦА ДОСТУПА СУБЪЕКТОВ К ОБЪЕКТАМ", col_width * (objects.size() + 1) + objects.size()) << "|";
	horizontal_table_line(col_width, objects);
	//Шапка таблицы.
	std::cout << "|" << center_text("Субъект / Объект", col_width) << "|";
	for (const auto& obj : objects) {
		std::cout << center_text(obj, col_width) << "|";
	}
	horizontal_table_line(col_width, objects);
	// Вывод строк таблицы.
	for (size_t i = 0; i < subjects.size(); ++i) {
		std::cout << "|" << center_text(subjects[i], col_width) << "|"; // Имя субъекта.
		for (size_t j = 0; j < objects.size(); ++j) {
			std::cout << center_text(access_level_to_string(access_matrix[i][j]), col_width) << "|"; //Уровень доступа.
		}
		if (i != objects.size() - 1) { std::cout << "\n"; }
	}
	horizontal_table_line(col_width, objects);
	std::cout << std::endl;
}
//Функция для генерации матрицы доступа
void generate_access_matrix(std::vector<std::vector<int>>& access_matrix) {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //ГПСЧ.
	for (size_t i = 0; i < access_matrix.size(); i++) {
		for (size_t j = 0; j < access_matrix[i].size(); j++) {
			access_matrix[i][j] = (i == 0) ? 7 : rand() % 8; // Администратор получает полный доступ.
		}
	}
}
//Запрос идентификатора пользователя.
int enter_the_program(const std::vector<std::string>& subjects) {
	std::string subject_name{};
	std::cout << "Пожалуйста, введите свой логин для входа! (quit - выход)" << std::endl;
	while (true) {
		std::getline(std::cin, subject_name);
		if (subject_name == "quit") return -1;
		int subject_index = find_subject(subjects, subject_name);
		if (subject_index != -1) {
			draw_line();
			std::cout << std::endl << "Здравствуйте, " << subjects[subject_index] << "!\nДобро пожаловать в систему!" << std::endl << std::endl;
			return subject_index;
		}
		std::cout << "Ошибка идентификации. Попробуйте снова или выйдите из программы:" << std::endl;
	}
}
//Вывод прав субъекта над объектом.
void display_subject_permissions(const int& subject_index, const std::vector<std::string>& objects, const std::vector<std::vector<int>>& access_matrix) {
	std::cout << "Перечень Ваших прав:" << std::endl;
	for (size_t i = 0; i < objects.size(); ++i) {
		std::cout << objects[i] << " -> " << access_level_to_string(access_matrix[subject_index][i]) << std::endl;
	}
}
//Выбор файла.
void file_choice(const int& subject_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects, 
	std::vector<std::vector<int>>& access_matrix) 
{
	while (true) {
		std::cout << "С каким файлом Вы хотите взаимодействовать? Введите название файла: (quit - выход)" << std::endl;
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = find_object(objects, object_name);
		if (object_index == -1) {
			std::cout << "Данный файл не был обнаружен в системе. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		while (true) {
			if (!file_interract(subject_index, object_index, subjects, objects, access_matrix)) {
				std::cout << "Работа с файлом " << object_name << " закончена!" << std::endl << std::endl;
				break;
			}
		}
	}
}
//Взаимодействие с файлом.
bool file_interract(const int& subject_index, const int& object_index, const std::vector<std::string>& subjects, const std::vector<std::string>& objects,
	std::vector<std::vector<int>>& access_matrix)
{
	std::cout << std::endl;
	bool access{};

	switch (getSubmenuCase(objects[object_index])) {
	case '1'://Чтение.
		access = check_permission(access_matrix, subject_index, object_index, 2);
		if (access) {
			std::cout << std::endl << "Чтение файла...\nФайл успешно прочитан!" << std::endl;
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl;
		break;
	case '2'://Запись.
		access = check_permission(access_matrix, subject_index, object_index, 1);
		if (access) {
			std::cout << std::endl << "Идет запись в файл...\nФайл успешно перезаписан!" << std::endl;
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl;
		break;
	case '3'://Передача прав.
		access = check_permission(access_matrix, subject_index, object_index, 0);
		if (access) {
			modify_access_matrix(subjects, object_index, access_matrix, subject_index);
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl;
		break;
	case '0'://Выход.
		return false;
	default:;
	}
	return true;
}
//Проверка прав субъекта над объектом.
bool check_permission(const std::vector<std::vector<int>>& access_matrix, const int& subject_index, const int& object_index, const int& bit) {
	return (access_matrix[subject_index][object_index] >> bit) % 2 == 1;
}
//Преобразование матрицы доступа при передаче прав.
void modify_access_matrix(const std::vector<std::string>& subjects, const int& target_object_index, std::vector<std::vector<int>>& access_matrix, const int& subject_index){
	while (true) {
		//Кому передается право.
		std::cout << std::endl;
		std::cout << "Кому Вы хотите передать доступ? Введите идентификатор: (quit - выход)" << std::endl;
		std::cout << "Имя пользователя: ";
		std::string target_subject_name{};
		std::getline(std::cin, target_subject_name);
		if (target_subject_name == "quit") return;
		int target_subject_index = find_subject(subjects, target_subject_name);
		if (target_subject_index == -1) {
			std::cout << "Указанный идентификатор не обнаружен в системе. Попробуйте заново." << std::endl;
			continue;
		}

		//Проверка, не передает ли пользователь права самому себе.
		if (target_subject_index == subject_index) {
			std::cout << "Передача прав самому себе запрещена! Можете попробовать передать права другому пользователю или завершить работу с файлом." << std::endl;
			continue;
		}

		//Какое право передается.
		std::cout << "Введите право: (read/write/grant)" << std::endl;
		std::cout << "Право: ";
		std::string right{};
		std::getline(std::cin, right);
		if (right == "read" || right == "write" || right == "grant") {
			int right_value = (right == "read") ? 4 : (right == "write") ? 2 : (right == "grant") ? 1 : 0;
			
			//Проверка, есть ли у субъекта, передающего права, это право над объектом.
			if (!(access_matrix[subject_index][target_object_index] & right_value)) {
				std::cout << "Ошибка: Вы не можете передать право '" << right << "' пользователю " << target_subject_name << ", т.к. не обладаете этим правом!\n";
				continue;
			}

			//Проверка, есть ли у субъекта, которому передается право, уже это право над объектом.
			if (access_matrix[target_subject_index][target_object_index] & right_value) {
				std::cout << "Ошибка: Пользователь " << target_subject_name << " уже обладает правом '" << right << "'!\n";
				continue;
			}

			//Передача прав.
			access_matrix[target_subject_index][target_object_index] |= right_value;
			std::cout << "Идет передача прав пользователю " << target_subject_name << "...\nПрава успешно переданы!" << std::endl;
			break;
		}
		else {
			std::cout << "Указанное право некорректно. Попробуйте заново." << std::endl;
		}
	}
}