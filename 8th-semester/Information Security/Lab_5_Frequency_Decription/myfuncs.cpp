#include <iostream>
#include "mystruct.h"
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
	std::cout << "Что Вы хотите сделать?" << std::endl <<
		"1: >Сформировать частотный анализ символов" << std::endl <<
		"2: >Дешифровать указанный файл" << std::endl <<
		"0: >Выйти из программы" << std::endl;
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
void DrawLine(const char& del) {
	std::cout << std::endl << "|" << std::string(200, del) << "|" << std::endl;
}
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Обработка взаимодействия пользователя при анализе частотности символов.
void AnalyzeFrequencyProcess() 
{
	while (true) {
		//Ввод файла для анализа.
		std::string file_in{};
		std::cout << "Вам необходимо указать файл, который надо проанализировать, в формате <file.txt>." << std::endl;
		std::cout << "Файл для анализа [opentext.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_in);
		if (file_in == "quit") break;
		if (file_in.empty()) file_in = "opentext.txt";

		//Структура для обработки и подсчет общего числа символов.
		std::map<unsigned char, CharInfo> freq{};
		int total_chars = 0;

		//1. Анализ файла.
		if (!analyzeFile(file_in, freq, total_chars)) break;
		DrawLine('-');
		std::cout << std::endl;
		//2. Вычисление процентного соотношения частотности символов.
		computePercentages(freq, total_chars);
		//3. Вывод результатов.
		std::string file_out{};
		std::cout << "Вам необходимо указать файл, в который надо вывести результаты, в формате <file.txt>." << std::endl;
		std::cout << "Файл для вывода результатов [ANALYZE_opentext.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_out);
		if (file_out == "quit") break;
		if (file_out.empty()) file_out = "ANALYZE_opentext.txt";
		if (!writeResults(file_out, freq)) break;

		DrawLine('-');
		std::cout << std::endl;
		
		//Конец.
		std::cout << "ИТОГИ: Файл " << file_in << " был успешно проанализирован, частотный анализ символов выведен в файл " << file_out << "!" << std::endl;
	
		DrawLine('=');
		std::cout << std::endl;
	}
	return;
}
//Обработка взаимодействия пользователя при расшифровки символов в указанном файле.
void DecryptFileProcess()
{
	while (true) {
		//Ввод файла с открытым текстом для анализа.
		std::string file_freq1{};
		std::cout << "Вам необходимо указать файл с открытым текстом, который надо проанализировать, в формате <file.txt>." << std::endl;
		std::cout << "Файл для анализа [opentext.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_freq1);
		if (file_freq1 == "quit") break;
		if (file_freq1.empty()) file_freq1 = "opentext.txt";

		DrawLine('-');
		std::cout << std::endl;

		//Ввод файла с зашифрованным текстом для анализа.
		std::string file_freq2{};
		std::cout << "Вам необходимо указать файл с зашифрованным текстом, который надо проанализировать, в формате <file.txt>." << std::endl;
		std::cout << "Файл для анализа [open.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_freq2);
		if (file_freq2 == "quit") break;
		if (file_freq2.empty()) file_freq2 = "open.txt";

		DrawLine('-');
		std::cout << std::endl;

		//Ввод расшифруемого файла.
		std::string file_encrypt{};
		std::cout << "Вам необходимо указать файл с текстом, который надо расшифровать, в формате <file.txt>." << std::endl;
		std::cout << "Файл для анализа [" << file_freq2 << " - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_encrypt);
		if (file_encrypt == "quit") break;
		if (file_encrypt.empty()) file_encrypt = file_freq2;

		DrawLine('-');
		std::cout << std::endl;

		//Вывод результатов (расшифровка).
		std::string file_decrypt{};
		std::cout << "Вам необходимо указать файл, в который надо вывести результаты расшифровки, в формате <file.txt>." << std::endl;
		std::cout << "Файл для вывода результатов [DECRYPT_open.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_decrypt);
		if (file_decrypt == "quit") break;
		if (file_decrypt.empty()) file_decrypt = "DECRYPT_open.txt";

		DrawLine('-');
		std::cout << std::endl;

		//Выводим таблицу подстановки в указанный файл.
		std::string file_table{};
		std::cout << "Вам необходимо указать файл, куда отобразить таблицу подстановок, в формате <file.txt>." << std::endl;
		std::cout << "Файл для вывода таблицы [TABLE_ENCR_DECR_opentext_open.txt - по умолчанию, нажмите Enter] (quit - выход) : ";
		std::getline(std::cin, file_table);
		if (file_table == "quit") break;
		if (file_table.empty()) file_table = "TABLE_ENCR_DECR_opentext_open.txt";

		DrawLine('-');

		//Запуск.
		if (!decryptFile(file_freq1, file_freq2, file_encrypt, file_decrypt, file_table)) break;
		else std::cout << std::endl;

		//Конец.
		std::cout << "ИТОГИ: Файл " << file_encrypt << " был успешно расшифрован, результаты записаны в файл " << file_decrypt << "!"
			<< std::endl << "Расшифровка производилась на основе частотного анализа символов следующих файлов: " << file_freq1 << " -> " 
			<< file_freq2 << "." << std::endl
			<< "Таблица подстановок выведена в файл " << file_table << "." << std::endl
			<< "Если Вы хотите посмотреть файлы с частотным анализом, запустите функцию 1 этой программы для необходимых файлов:)" << std::endl;

		DrawLine('=');
		std::cout << std::endl;
	}
	return;
}
//Функция для сортировки по убыванию количества вхождений.
bool compare(const std::pair<unsigned char, CharInfo>& a, const std::pair<unsigned char, CharInfo>& b) {
	if (a.second.count == b.second.count) {
		return a.first < b.first;
	}
	return a.second.count > b.second.count;
}
//Функция для анализа частоты символов в файле.
bool analyzeFile(const std::string& inputFilename, std::map<unsigned char, CharInfo>& freq, int& total_chars) 
{
	std::ifstream file(inputFilename, std::ios::binary); //Открытие файла в бинарном режиме.

	if (!file) {
		std::cerr << std::endl << "Ошибка: не удалось открыть файл " << inputFilename << "!" << std::endl;
		return false;
	}

	std::cout << std::endl << "Файл " << inputFilename << " анализируется. Пожалуйста, подождите..." << std::endl;

	//Подсчет частоты символов.
	char ch{};
	while (file.get(ch)) {
		unsigned char uch = static_cast<unsigned char>(ch);
		freq[uch].character = uch;
		freq[uch].count++;
		total_chars++;
	}

	file.close(); //Закрытие открытого файла.
	std::cout << std::endl << "Файл " << inputFilename << " был успешно проанализирован!" << std::endl;

	return true;
}
//Функция для вычисления процентного соотношения частотности символов.
void computePercentages(std::map<unsigned char, CharInfo>& freq, int total_chars)
{
	for (auto& pair : freq) {
		pair.second.percentage = (pair.second.count * 100.0) / total_chars;
	}
}
//Функция для записи результатов в файл.
bool writeResults(const std::string& outputFilename, const std::map<unsigned char, CharInfo>& freq)
{
	//Открытие выходного файла с результатами.
	std::ofstream outFile(outputFilename);
	if (!outFile) {
		std::cerr << std::endl << "Ошибка: не удалось открыть файл " << outputFilename << "!" << std::endl;
		return false;
	}

	std::cout << std::endl << "В файл " << outputFilename << " выводятся результаты. Пожалуйста, подождите..." << std::endl;

	//Сортировка результатов.
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq(freq.begin(), freq.end());
	std::sort(sorted_freq.begin(), sorted_freq.end(), compare);

	//Запись заголовков таблицы.
	outFile << "NN\tDEC\tHEX\tCHAR\tCOUNT\t%\n";

	int index{ 1 };
	for (const auto& pair : sorted_freq) {
		unsigned char uch = pair.first;
		//Если символ не печатный, то проверяется вывод на специальные символы.
		std::string charRep = std::isprint(uch) ? std::string(1, uch)
			: (uch == 13 ? "\\r"                              
				: (uch == 10 ? "\\n"                          
					: std::string(1, uch)));

		//Форматирование 16-ричного вывода (верхний регистр).
		std::stringstream hexStream{};
		hexStream << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(uch);

		outFile << index++ << "\t"
			<< static_cast<int>(uch) << "\t"
			<< hexStream.str() << "\t"
			<< charRep << "\t"
			<< pair.second.count << "\t"
			<< std::fixed << std::setprecision(3) << pair.second.percentage << "%" << "\n";
	}

	outFile.close(); //Закрытие открытого файла.
	std::cout << std::endl << "Результаты записаны в файл " << outputFilename << std::endl;
	
	return true;
}
//Функция для расшифровки указанного файла по соответствию частот.
bool decryptFile(const std::string& freqFile1, const std::string& freqFile2,
	const std::string& inputFilename, const std::string& outputFilename, const std::string& file_table) {
	//Карты для хранения частот.
	std::map<unsigned char, CharInfo> freq1{}, freq2{};
	int total_chars1{}, total_chars2{};

	//Анализируем оба файла с частотами.
	//Файл с открытым текстом.
	if (!analyzeFile(freqFile1, freq1, total_chars1)) return false;
	//Файл с зашифрованным текстом.
	if (!analyzeFile(freqFile2, freq2, total_chars2)) return false;
	computePercentages(freq1, total_chars1);
	computePercentages(freq2, total_chars2);

	//Сортируем частоты.
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq1(freq1.begin(), freq1.end());
	std::vector<std::pair<unsigned char, CharInfo>> sorted_freq2(freq2.begin(), freq2.end());
	std::sort(sorted_freq1.begin(), sorted_freq1.end(), compare);
	std::sort(sorted_freq2.begin(), sorted_freq2.end(), compare);

	//Создаем таблицу подстановки.
	std::vector<std::pair<unsigned char, unsigned char>> substitution{};// Ключ - зашифрованный символ, значение - расшифрованный символ.
	for (size_t i = 0; i < std::min(sorted_freq1.size(), sorted_freq2.size()); ++i) {
		substitution.emplace_back(sorted_freq2[i].first, sorted_freq1[i].first);//Зашифрованный символ -> символ открытого текста.
	}

	//Вывод таблицы в файл.
	if (!saveSubstitutionTable(substitution, file_table)) return false;

	//Открываем зашифрованный файл и файл для расшифрованного текста.
	std::ifstream inputFile(inputFilename, std::ios::binary);//Зашифрованный файл.
	std::ofstream outputFile(outputFilename, std::ios::binary);//Файл расшифровки.
	if (!inputFile || !outputFile) {
		std::cerr << std::endl << "Ошибка: не удалось открыть входной или выходной файл!" << std::endl;
		return false;
	}

	//Заменяем символы по таблице подстановки.
	char ch{};
	while (inputFile.get(ch)) {
		unsigned char uch = static_cast<unsigned char>(ch);
		bool replaced{};
		//Ищем зашифрованный символ.
		for (const auto& pair : substitution) {
			if (pair.first == uch) {  // Если символ найден в таблице,
				outputFile.put(pair.second); //То заменяем.
				replaced = true;
				break;
			}
		}

		if (!replaced) {  // Если символ не был заменен, оставляем его как есть.
			outputFile.put(ch);
		}
	}

	//Закрытие файлов.
	inputFile.close();
	outputFile.close();
	std::cout << std::endl << "Расшифровка завершена! Результат записан в " << outputFilename << std::endl;

	return true;
}
//Функция для сохранения таблицы подстановок в указанный файл.
bool saveSubstitutionTable(const std::vector<std::pair<unsigned char, unsigned char>>& substitution, const std::string& filename) 
{
	std::ofstream tableFile(filename);
	if (!tableFile) {
		std::cerr << std::endl << "Ошибка: не удалось открыть файл для таблицы замен!" << std::endl;
		return false;
	}

	tableFile << "ТАБЛИЦА ЗАМЕН АЛГОРИТМА ШИФРОВАНИЯ" << std::endl;
	//Запись заголовков таблицы.
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
	std::cout << std::endl << "Таблица замен сохранена в " << filename << std::endl;
	
	return true;
}