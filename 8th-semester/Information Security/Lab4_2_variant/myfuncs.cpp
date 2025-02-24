#include <iostream>
#include <string>
#include <iomanip>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Вывод приветсвия.
void WelcomeUser() {
	std::cout << std::endl << "|" << std::string(200, '-') << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << CenterText("УВАЖАЕМЫЙ ПОЛЬЗОВАТЕЛЬ, ДОБРО ПОЖАЛОВАТЬ В ПРОГРАММУ!", 200) << "|" << std::endl;
	std::cout << "|" << std::string(200, ' ') << "|" << std::endl;
	std::cout << "|" << std::string(200, '-') << "|" << std::endl << std::endl;
}
//Пользовательское меню.
void MenuForChoices()
{
	std::cout << "Выберите метод шифрования из списка ниже:" << std::endl <<
		"1 - Простая моноалфавитная замена (обобщенный метод Цезаря)" << std::endl <<
		"2 - Система шифрования Вижинера" << std::endl <<
		"0 - Выход из программы" << std::endl;
}
//Запрос дейтсвий у пользователя.
char GetCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice.size() == 1 && choice[0] >= '0' && choice[0] <= '3')
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с нижеперечисленными пунктами (от 0 до 2). " <<
				"Повторите ввод." << std::endl;
		}
	}
}

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
//Функция отрисовки разделительной черты.
void DrawLine() {
	std::cout << std::endl << "|" << std::string(200, '=') << "|" << std::endl;
}
//Функция отрисовки горизонтальной черты таблицы.
void HorizontalLineForTable(const int& col_width)
{
	std::cout << std::string(col_width + 2, '-') << std::endl;
}
//Функция отрисовки горизонтальной двойной черты таблицы.
void HorizontalDoubleLineForTable(const int& col_width)
{
	std::cout << std::string(col_width + 2, '=') << std::endl;
}
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Проверка введённой пользователем строки на возможность преобразования в целое число.
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
//Преобразование введённой пользователем строки в число.
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
//Проверка строки на русский ("RUS") или латинский ("LATIN") алфавит, смешанный = "MIXED", без букв = "NONE".
const std::string CheckMixedAlphabet(const std::string& text)
{
	bool hasLatin{};
	bool hasRussian{};

	for (const char& c : text) {
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			hasLatin = true;
		}
		else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я') || c == 'Ё' || c == 'ё') {
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
//Функция для нахождения НОД (gcd) двух чисел.
int gcd(int a, int b) {
	//Алгоритм Евклида.
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
//Функция для нахождения обратного числа к a по модулю M.
int modInverse(int a, int M) {
	//Расширенный алгоритм Евклида.
	int m0{ M }, t{}, q{};
	int x0{ 0 }, x1{ 1 }; //Коэффициенты: a * x0 + M * x1 = gcd(a,M) - уравнение.

	//Проверка, что a и M взаимно просты.
	if (M == 1)
		return 0;

	while (a > 1) {
		q = a / M;			// Шаг 1: Целочисленное деление (нахождение коэффициента q).
		t = M;				// Шаг 2: Сохранение старого M перед обновлением.
		M = a % M;			// Шаг 3: Остаток от деления (обновление M).
		a = t;				// Шаг 4: Обновление a (a теперь предыдущее M).
		// Шаги 1 - 4: Поиск НОД по алгоритму Евклида.
		t = x0;				// Шаг 5: Сохранение предыдущего x0. 
		x0 = x1 - q * x0;	// Шаг 6: Обновление x0 по формуле x0 = x1 - q * x0. 
		x1 = t;				// Шаг 7: Обновление x1 (x1 теперь старый x0).
	}

	// Если x1 отрицательное, добавляем M, чтобы получить положительное число.
	if (x1 < 0)
		x1 += m0;

	return x1;
}
//Верхний -> нижний регистр русских и латинских символов.
char UpperToLower(const char& c, const std::string& type_alphabet)
{
	if (type_alphabet == "RUS") {
		if (c >= 'А' && c <= 'Я')
			return c + ('а' - 'А');
		if (c == 'Ё')
			return 'ё';
	}
	else if (type_alphabet == "LATIN") {
		if (c >= 'A' && c <= 'Z') {
			return c + ('a' - 'A');
		}
	}
	return c;
}
//Нижний -> верхний регистр русских и латинских символов.
char LowerToUpper(const char& c, const std::string& type_alphabet)
{
	if (type_alphabet == "RUS") {
		if (c >= 'а' && c <= 'я')
			return c - ('а' - 'А');
		if (c == 'ё')
			return 'Ё';
	}
	else if (type_alphabet == "LATIN") {
		if (c >= 'a' && c <= 'z') {
			return c - ('a' - 'A');
		}
		return c;
	}
	return c;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Шифрование методом простой моноалфавитной замены.
std::string SimpleSubstitutionEncryption(const std::string& text, const int& a, const int& shift, const std::string& type_alphabet)
{
	//Шифрование.
	std::string result{};

	//Обработка.
	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; //Размерность русского алфавита.
		//Строчные и прописные буквы русского алфавита.
		const std::string russian_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		const std::string russian_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				int mod_shift = (shift % RUSSIAN_M + RUSSIAN_M) % RUSSIAN_M; //Нормализация.
				char encrypted = russian_upper[(a * russian_upper.find(c) + mod_shift) % RUSSIAN_M];
				result += encrypted;
			}
			else if (russian_lower.find(c) != std::string::npos) {
				int mod_shift = (shift % RUSSIAN_M + RUSSIAN_M) % RUSSIAN_M; //Нормализация.
				char encrypted = russian_lower[(a * russian_lower.find(c) + mod_shift) % RUSSIAN_M];
				result += encrypted;
			}
			else {
				result += c;
			}
		}
	}
	else if (type_alphabet == "LATIN") {
		const int LATIN_M = 26; //Размерность латинского алфавита.
		//Строчные и прописные буквы латинского алфавита.
		const std::string latin_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const std::string latin_lower = "abcdefghijklmnopqrstuvwxyz";

		for (const char& c : text) {
			if (latin_upper.find(c) != std::string::npos) {
				int mod_shift = (shift % LATIN_M + LATIN_M) % LATIN_M; //Нормализация.
				char encrypted = latin_upper[(a * latin_upper.find(c) + mod_shift) % LATIN_M];
				result += encrypted;
			}
			else if (latin_lower.find(c) != std::string::npos) {
				int mod_shift = (shift % LATIN_M + LATIN_M) % LATIN_M; //Нормализация.
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
//Дешифрование методом простой моноалфавитной замены.
std::string SimpleSubstitutionDecryption(const std::string& text, const int& a_inv, const int& shift, const std::string& type_alphabet) {
	//Дешифрование.
	std::string result{};

	//Обработка.
	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; //Размерность русского алфавита.
		//Строчные и прописные буквы русского алфавита.
		const std::string russian_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		const std::string russian_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

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
		const int LATIN_M = 26; //Размерность латинского алфавита.
		//Строчные и прописные буквы латинского алфавита.
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
//Шифрование методом простой моноалфавитной замены - обработка.
void SimpleSubstitutionProcess()
{
	//Обработка.
	std::cout << "Шифрование методом простой моноалфавитной замены. Осуществляется шифрование русских символов -> русские символы, "
		"латинских символов -> латинские символы." << std::endl;
	DrawLine();
	std::cout << std::endl;
	while (true) {
		//СТРОКА.
		std::cout << "Введите строку для шифрования (quit - выход): ";
		std::string open_text{};
		std::getline(std::cin, open_text);
		if (open_text == "quit") break;
		//Проверка строки на моноалфавит.
		const std::string type_alphabet{ CheckMixedAlphabet(open_text) };
		if (type_alphabet == "MIXED") {
			std::cout << "Ошибка! Строка для шифрования должна содержать символы из одного алфавита. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//Проверка необходимости шифровать.
		if (type_alphabet == "NONE") {
			std::cout << "***Шифровать/Дешифровать нечего!***" << std::endl;
			std::cout << "Зашифрованная строка: " << open_text << std::endl;
			std::cout << "Дешифрованная строка: " << open_text << std::endl;
			DrawLine();
			std::cout << std::endl;
			continue;
		}
		else
			std::cout << "Размерность алфавита M = " << ((type_alphabet == "RUS") ? 33 : 26) << ". Учтите при выборе 'a' (НОД(a,M) = 1)." << std::endl << std::endl;

		//ЗНАЧЕНИЕ a.
		std::cout << "Введите значение a (quit - выход): ";
		std::string a_value{};
		std::getline(std::cin, a_value);
		if (a_value == "quit") break;
		//Проверка значения a.
		if (!(CheckStrIsNumeric(a_value) && ConvertStrToInt(a_value) >= 0)) {
			std::cout << "Ошибка! Значение 'a' должно быть целым неотрицательным числом. Попробуйте снова." << std::endl << std::endl;
			continue;
		}
		//Проверка НОД(a,M)=1.
		const int a{ ConvertStrToInt(a_value) };
		int M{};
		if (type_alphabet == "RUS")
			M = 33; //Размерность русского алфавита.
		else if (type_alphabet == "LATIN")
			M = 26; //Размерность латинского алфавита.
		else
			M = 1; //mod M ничего не делает.
		const int gcd_value{ gcd(a,M) };//НОД(a,M).
		if (gcd_value != 1) {
			std::cout << "Ошибка! НОД(a,M) = НОД(" << a << "," << M << ") = " << gcd_value << ", а должен быть равен 1! (иначе простая моноалфавитная замена " <<
				"не имеет взаимно однозначное отображение в своей схеме). Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//КЛЮЧ.
		std::cout << "Введите значение ключа K (quit - выход): ";
		std::string key_crypt{};
		std::getline(std::cin, key_crypt);
		if (key_crypt == "quit") break;
		//Проверка значения ключа K.
		if (!(CheckStrIsNumeric(key_crypt) && ConvertStrToInt(key_crypt) >= 0 && ConvertStrToInt(key_crypt) < M)) {
			std::cout << "Ошибка! Значение ключа K должно быть целым неотрицательным числом, 0 <= K < M = " << M << ". Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//ОБРАБОТКА.
		const int shift{ ConvertStrToInt(key_crypt) };//Ключ.
		const int a_inv{ modInverse(a, M) };//Обратное значение к 'a' по модулю M.
		std::string encrypt_str{ SimpleSubstitutionEncryption(open_text, a, shift, type_alphabet) };
		std::string	decrypt_str{ SimpleSubstitutionDecryption(encrypt_str, a_inv, shift, type_alphabet) };

		//ВЫВОД.
		DisplaySimpleSubstitutionTable(type_alphabet, a, shift);
		std::cout << "Зашифрованная строка: " << encrypt_str << std::endl;
		std::cout << "Дешифрованная строка: " << decrypt_str << std::endl;
		DrawLine();
		std::cout << std::endl;
	}
}
//Вывод подстановок шифрования методом простой моноалфавитной замены.
void DisplaySimpleSubstitutionTable(const std::string& type_alphabet, const int& a, const int& shift)
{
	//Определение алфавита.
	std::string alphabet{};
	if (type_alphabet == "RUS") alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	else if (type_alphabet == "LATIN") alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else return;

	const int col_width{ 3 }; //Ширина столбца.

	//Заголовок.
	std::cout << std::endl;
	HorizontalLineForTable(col_width * 15 + 14);
	std::cout << "|" << CenterText("Таблица подстановок обобщенного метода Цезаря", col_width * 15 + 14) << "|" << std::endl;
	HorizontalLineForTable(col_width * 15 + 14);

	//Вывод таблицы подстановок.
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
//Проверка ключа Вижинера на корректность.
bool CheckKeyViginer(const std::string& key_word, const std::string& type_alphabet)
{
	//Алфавиты.
	const std::string RUS_alphabet = "АаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя";
	const std::string LATIN_alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	const std::string digits = "0123456789";
	//Проверка.
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
//Шифрование методом Вижинера.
std::string ViginerEncryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet)
{
	std::string result{};

	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33;
		const std::string russian_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		const std::string russian_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
		const std::string digits = "0123456789";

		// Отдельный счётчик для символов, которые шифруются (в алфавите)
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
				++cipher_count; // увеличиваем счётчик только для шифруемых символов
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
				result += c; // для нешифруемых символов ключ не используется
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
//Дешифрование методом Вижинера.
std::string ViginerDecryption(const std::string& text, const std::string& key_word, const std::string& type_alphabet)
{
	std::string result{};

	if (type_alphabet == "RUS") {
		const int RUSSIAN_M = 33; // Размерность русского алфавита.
		const std::string russian_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		const std::string russian_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
		const std::string digits = "0123456789";

		size_t cipher_count{}; // Счётчик для дешифруемых символов.

		for (const char& c : text) {
			if (russian_upper.find(c) != std::string::npos) {
				size_t pos_encr_symbol = russian_upper.find(c);
				char key_symbol = key_word[cipher_count % key_word.size()];
				char decrypted{};
				if (!isdigit(key_symbol)) { // Не цифра.
					size_t pos_key_symbol{};
					if (key_symbol == LowerToUpper(key_symbol, type_alphabet))
						pos_key_symbol = russian_upper.find(key_symbol);
					else
						pos_key_symbol = russian_lower.find(key_symbol);
					decrypted = russian_upper[(pos_encr_symbol + RUSSIAN_M - pos_key_symbol) % RUSSIAN_M];
				}
				else { // Цифра.
					decrypted = russian_upper[(pos_encr_symbol + RUSSIAN_M - digits.find(key_symbol)) % RUSSIAN_M];
				}
				result += decrypted;
				++cipher_count; // увеличиваем только если символ шифруемый
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
		const int LATIN_M = 26; // Размерность латинского алфавита.
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

//Шифрование методом Вижинера - обработка.
void ViginerProcess() {
	//Обработка.
	std::cout << "Шифрование методом Вижинера.  Осуществляется шифрование русских символов -> русские символы, "
		"латинских символов -> латинские символы." << std::endl;
	DrawLine();
	std::cout << std::endl;
	while (true) {
		//СТРОКА.
		std::cout << "Введите строку для шифрования (quit - выход): ";
		std::string open_text{};
		std::getline(std::cin, open_text);
		if (open_text == "quit") break;
		//Проверка строки на моноалфавит.
		const std::string type_alphabet{ CheckMixedAlphabet(open_text) };
		if (type_alphabet == "MIXED") {
			std::cout << "Ошибка! Строка для шифрования должна содержать символы из заданных алфавитов. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//Проверка необходимости шифровать.
		if (type_alphabet == "NONE") {
			std::cout << "***Шифровать/Дешифровать нечего!***" << std::endl;
			std::cout << "Зашифрованная строка: " << open_text << std::endl;
			std::cout << "Дешифрованная строка: " << open_text << std::endl;
			DrawLine();
			std::cout << std::endl;
			continue;
		}

		//КЛЮЧ.
		std::cout << "Введите ключевое слово (символы " << ((type_alphabet == "RUS") ? "русского " : "латинского ") << "алфавита и цифры (0-9) (quit - выход)." << std::endl;
		std::cout << "Ключ: ";
		std::string key_word{};
		std::getline(std::cin, key_word);
		if (key_word == "quit") break;
		//Проверка ключа на корректность.
		if (!CheckKeyViginer(key_word, type_alphabet)) {
			std::cout << "Ошибка при вводе ключа! Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//ОБРАБОТКА.
		std::string encrypt_str{ ViginerEncryption(open_text, key_word, type_alphabet)};
		std::string	decrypt_str{ ViginerDecryption(encrypt_str, key_word, type_alphabet)};

		//ВЫВОД.
		DisplayViginerTable(type_alphabet, open_text, key_word, encrypt_str);
		std::cout << "Зашифрованная строка: " << encrypt_str << std::endl;
		std::cout << "Дешифрованная строка: " << decrypt_str << std::endl;
		DrawLine();
		std::cout << std::endl;
	}
}
//Вывод таблицы Вижинера.
void DisplayViginerTable(const std::string& type_alphabet, const std::string& open_text, const std::string& key_word, const std::string& encrypt_word) {
	//Определение алфавита.
	std::string alphabet{};
	if (type_alphabet == "RUS") alphabet = "АаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯя";
	else if (type_alphabet == "LATIN") alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	else return;

	const int col_width{ 3 }; //Ширина столбца.

	//Заголовок.
	std::cout << std::endl;
	HorizontalDoubleLineForTable(col_width * 14 + col_width * 4 + 14);
	std::cout << "|" << CenterText("Полученная таблица шифрования по методу Вижинера", col_width * 14 + col_width * 4 + 14) << "|" << std::endl;
	HorizontalDoubleLineForTable(col_width * 14 + col_width * 4 + 14);

	//Вывод таблицы подстановок.
	int columns{ 14 };
	int steps = static_cast<int>(open_text.size()) / columns + ((static_cast<int>(open_text.size()) % columns) == 0 ? 0 : 1);
	int shift{};
	//Этапы.
	for (size_t iter = 0; iter < steps; ++iter) {
		//Подэтапы.
		for (size_t row = 0; row < 3; ++row) {
			switch (row) {
			case 0:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("Сообщение", col_width * 4) << "|";
				//Колонки.
				for (size_t col = 0; col < columns; ++col) {
					if (iter * columns + col < open_text.size())
						std::cout << std::right << std::setw(col_width) << open_text[iter * columns + col] << "|";
					else
						std::cout << std::right << std::setw(col_width) << " " << "|";
				}
				break;
			case 1:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("Ключ", col_width * 4) << "|";
				// Колонки.
				for (size_t col = 0; col < columns; ++col) {
					size_t index = iter * columns + col;
					if (index < open_text.size()) {
						char current_char = open_text[index];
						// Проверка, является ли символ частью алфавита
						if (alphabet.find(current_char) != std::string::npos) {
							std::cout << std::right << std::setw(col_width)
								<< key_word[(index - shift) % key_word.size()] << "|";
						}
						else {
							std::cout << std::right << std::setw(col_width) << " " << "|";
							++shift; // Увеличиваем смещение только если символ не шифруется
						}
					}
					else {
						std::cout << std::right << std::setw(col_width) << " " << "|";
					}
				}
				break;
			case 2:
				std::cout << "|" << std::setw(static_cast<size_t>(col_width * 4)) << CenterText("Шифротекст", col_width * 4) << "|";
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