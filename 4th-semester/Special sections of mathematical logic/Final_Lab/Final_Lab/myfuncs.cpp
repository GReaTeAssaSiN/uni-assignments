#include <iostream>
#include <stack>
#include <string>
#include "myfuncs.h"

/*ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ*/
//Информация о номере группы и номере в списке группы, выборе варианта, ФИО исполнителя.
void getAboutInformation()
{
	printDashes();
	//Выбор варианта.
	std::cout << "\t\t\t\t\t\t\t\t\t\t\t    Горшков Алексей Олегович" << std::endl <<
		"\t\t\t\t\t\t\t\t\t\t\t\t\t Группа " << g << std::endl;
	std::cout << "Номер группы g = " << g << std::endl;
	std::cout << "Номер в списке группы n = " << n << std::endl << std::endl;
	std::cout << "Унарная операция из табл. 1 выбирается под номером (g + n - 1)(mod 6) + 1, где s = [n / 7], [.] - целая часть числа." << std::endl <<
		"Таким образом, номер унарной операции из табл. 1: '" << (g + n - 1) % 6 + 1 << "'. _x - отрицание Поста " << 
		"(вычисление s не требуется)." << std::endl << std::endl;
	std::cout << "Бинарная операция из табл. 2 выбирается под номером (g + n - 1)(mod 7) + 1." << std::endl <<
		"Таким образом, номер бинарной операции из табл. 2: " << "'" << (g + n - 1) % 7 + 1 << "'. x-.y - усеченная разность." << std::endl << std::endl;
	std::cout << "Стандартная форма представления функции под номером (g + n - 1)(mod 3) + 1." << std::endl <<
		"Таким образом, номер стандартной формы представления функции: '" << (g + n - 1) % 3 + 1 << "'. Вторая форма." << std::endl;
	printDashes();
}
//Вывод визуального разделения между действиями пользователя в консоль.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//Вывод пользователю информации об унарных и бинарных операциях.
void getLogicOperationInformation(const int& value_logic, const int& n)
{
	printDashes();
	std::cout << "Здесь приведена информация об операциях в данной k-значной логике (кавычки использованы для наглядности):" << std::endl <<
		"I. Константы задаются цифрами: 0, 1, 2, ..., k - 1." << std::endl;
	std::cout << "II. Унарные операции:\n" << "\t* Отрицание Поста - '_x' и т.п." << std::endl;
	if (n == 1)
		std::cout << "III. Бинарные операции:\n" << "\t* Усеченная разность - 'x-.2' и т.п." << std::endl;
	if (n == 2)
		std::cout << "III. Бинарные операции:\n" << "\t* Усеченная разность - 'x-.y' и т.п." << std::endl;
	printDashes();
	std::cout << "Вы должны ввести функцию без пробелов, используя только операции отрицания Поста и усеченной разности (в случае одной\nсущественной переменной с константой), " <<
		"переменные 'x' и/или 'y' (и - если используются 2 существенные переменные\nв задаваемой функции k - значной логики), целочисленные константы (0, ..., " << 
		value_logic - 1 << ")." << std::endl;	
}
//Желание продолжить ввод множества E.
bool doItAgain()
{
	std::cout << "Вы желаете продолжить ввод множества E и проверку принадлежности данной функции классу T(E)?" << std::endl <<
		"Да (yes)/ Нет (no): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "yes")
			return true;
		else if (user_wishes == "no")
			return false;
		else
			std::cout << "Ошибка ввода. Вы должны ввести 'yes' или 'no'. Повторите ввод: ";
	}
}
//Выход из программы или продолжение работы.
bool exitOrContinue()
{
	std::cout << "Вы желаете продолжить выполнение программы или хотите выйти?" << std::endl <<
		"Продолжить (continue)/ Выйти (exit): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "continue")
			return true;
		else if (user_wishes == "exit")
			return false;
		else
			std::cout << "Ошибка ввода. Вы должны ввести 'continue' или 'exit'. Повторите ввод: ";
	}
}

/*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*/
//Проверка введённой пользователем строки на возможность преобразования в целое число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)//Итерация по строке - динам. массив.
	{
		if ((i == 0) && (tempStr[i] == '-'))//Если первым символом стоит '-', то он допускается.
			continue;
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))//Если символ не является цифрой, то строка не является числом.
			return false;
	}
	return !tempStr.empty();//Если строка после проверка не пустая, то она является числом.
}
//Преобразование введённой пользователем строки в число.
int convertStrToInt(std::string convertStr)
{
	double number{};
	bool negative_number{ false };
	for (int i{}; i < convertStr.length(); i++)//Итерация по строке - динам. массив.
	{
		if ((i == 0) && (convertStr[i] == '-'))//Если первым символом стоит минус, то будущее число помечается флагом отрицательного числа.
		{
			negative_number = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);//Конвертация строки в число.
	}
	return negative_number ? static_cast<int>(-number) : static_cast<int>(number);//Возвращение числа (отрицательного или положительного).
}
//Получение k-значной логики от пользователя.
int getValueOfLogic()
{
	while (true)
	{
		std::string value_of_logic{};
		std::getline(std::cin, value_of_logic);
		if (checkStrIsNumeric(value_of_logic) && convertStrToInt(value_of_logic) > 0)//Если введенная строка число, которое больше 0, то принимается.
			return convertStrToInt(value_of_logic);
		else//Иначе повторный ввод.
			std::cout << "Ошибка ввода. Вы должны ввести целое положительное число. Повторите ввод: ";
	}
}
//Получение количества существенных переменных k-значной логики от пользователя.
int getCountOfSignificantVariables()
{
	while (true)
	{
		std::string count_of_significant_variables{};
		std::getline(std::cin, count_of_significant_variables);
		if (checkStrIsNumeric(count_of_significant_variables) &&
			(convertStrToInt(count_of_significant_variables) == 1 || convertStrToInt(count_of_significant_variables) == 2))//Если число существенных переменных = 1 или =2, то принимается.
			return convertStrToInt(count_of_significant_variables);
		else//Иначе повторный ввод.
			std::cout << "Ошибка ввода. Вы должны ввести '1' или '2'. Повторите ввод: ";
	}
}
//Проверка введенной пользователем функции на допустимые символы.
bool checkStringFunction(const std::string& user_logic_function, const int& value_logic)
{
	for (int i{}; i < user_logic_function.size(); i++)//Итерация по строке.
	{
		if (!strElemIsDigit(user_logic_function[i]))//Если символ строки - не число.
		{
			bool correct_symbol{};
			for (int j{}; j < mass_of_symbols.size(); j++)//Итерация по массиву допустимых символов.
			{
				if (user_logic_function[i] == mass_of_symbols[j])
				{
					correct_symbol = true;
					break;
				}
			}
			if (!correct_symbol)//Если символ строки - допустимый символ, то принимается.
				return false;
		}
		else//Иначе - если число.
		{
			std::string substr_numeric{};//Подстрока, хранящее в себе число.
			int checking_index{ i + 1 };//Дополнительный итератор по строке.
			substr_numeric.push_back(user_logic_function[i]);//Добавление текущего символа в подстроку.
			while ((checking_index != user_logic_function.size()) && strElemIsDigit(user_logic_function[checking_index]))//Все символы строки, являющиеся цифрами текущего числа, добавляются в подстроку.
			{
				substr_numeric.push_back(user_logic_function[checking_index]);
				checking_index++;
			}
			if (!(convertStrToInt(substr_numeric) >= 0 && convertStrToInt(substr_numeric) < value_logic))//Если число не принадлежит множестве E_k, то НЕ принимается.
				return false;
		}
	}
	return true;//Иначе строка принимается.
}
//Проверка введенной пользователем функции на корректную последовательность символов.
bool checkCharacterSequenceOfStrFunction(const std::string& user_logic_function)
{
	for (int i{}; i < user_logic_function.size() - 1; i++)//Итерация по строке.
	{
		//Различные проверки.
		if (user_logic_function[i] == '_' || user_logic_function[i] == '.' || user_logic_function[i] == '(')
		{
			if (user_logic_function[static_cast<char>(i + 1)] == '-' || user_logic_function[static_cast<char>(i + 1)] == '.' || user_logic_function[static_cast<char>(i + 1)] == ')')
				return false;
		}
		else if (user_logic_function[i] == ')' || user_logic_function[i] == 'x' || user_logic_function[i] == 'y')
		{
			if (user_logic_function[static_cast<char>(i + 1)] != '-' && user_logic_function[static_cast<char>(i + 1)] != ')')
				return false;
		}
		else if (user_logic_function[i] == '-')
		{
			if (user_logic_function[static_cast<char>(i + 1)] != '.')
				return false;
		}
		else//Если число.
		{
			if (user_logic_function[static_cast<char>(i + 1)] == 'x' || user_logic_function[static_cast<char>(i + 1)] == 'y' || user_logic_function[static_cast<char>(i + 1)] == '(' ||
				user_logic_function[static_cast<char>(i + 1)] == '_' || user_logic_function[static_cast<char>(i + 1)] == '.')
				return false;
		}
	}
	//Проверка первого символа строки.
	if (user_logic_function[0] == ')' || user_logic_function[0] == '-' || user_logic_function[0] == '.')
		return false;
	//Проверка последнего символа строки.
	if (user_logic_function[user_logic_function.size() - 1] == '(' || user_logic_function[user_logic_function.size() - 1] == '-' ||
		user_logic_function[user_logic_function.size() - 1] == '.' || user_logic_function[user_logic_function.size() - 1] == '_')
	{
		return false;
	}
	return true;
}
//Получение приоритета операции в k-значной логике.
int getOperationPriority(const char& operation)
{
	int priority_of_operation{};
	switch (operation)
	{
	case '_':
		priority_of_operation = 3;
		break;
	case '-':
		priority_of_operation = 2;
		break;
	case '.':
		priority_of_operation = 2;
		break;
	case '(':
		priority_of_operation = 1;
		break;
	case ')':
		priority_of_operation = 1;
		break;
	default:;
	}
	return priority_of_operation;
}
//Проверка элемента строки на соответствие цифре.
bool strElemIsDigit(const char& str_elem)
{
	return (str_elem >= '0' && str_elem <= '9') ? true : false;
}
//Преобразование введенной функции k-значной логики по методу обратной польской нотации (придумал Лукасевич).
bool reversePolishNotationForFunction(const std::string& logic_function, std::string& logic_function_by_RPN, const int& significant_variables_count)
{
	//Флаги для обработки исключительных ситуаций.
	bool x_is_used{}, y_is_used{};
	int balance_of_brackets{};//Баланс скобок '(' и ')'.

	//Флаг для ввода разделительных символов между константами и переменными (т.к. после ОПН не ясно, какими были исходные константы или значения переменных).
	bool operator_was_added{};
	std::stack<char> operators{};//Стек операторов.
	for (int i{}; i < logic_function.size(); i++)//Итерация по копии исходной строки и построение строки по методу ОПН.
	{
		bool binary_operation_is_using{};//Флаг использования бинарной операции.
		if (logic_function[i] == '(')//Если '(', то кладется в стек операторов.
		{
			operators.push(logic_function[i]);
			operator_was_added = true;
			balance_of_brackets++;
		}
		else if (logic_function[i] == ')')//Если ')', до вынимаются все операторы до '('. Затем скобки уничтожаются.
		{
			if (balance_of_brackets > 0)
			{
				while (operators.top() != '(')
				{
					logic_function_by_RPN.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
				balance_of_brackets--;
			}
			else
				return false;
		}
		else if (logic_function[i] == '_' || logic_function[i] == '-')//Если иной оператор.
		{
			operator_was_added = true;
			if (logic_function[i] == '-')//Бинарный оператор.
				binary_operation_is_using = true;
			int current_operation_priority{ getOperationPriority(logic_function[i]) }, sp_operation_priority{};//Опеределение приоритета текущего и в вершине стека операторов.
			if (!operators.empty())
				sp_operation_priority = getOperationPriority(operators.top());
			//Если унарный оператор, то в случае приоритета текущего оператора >= приоритету оператора в вершине стека текущий оператор кладется в стек.
			//Если же бинарный оператор, то просто >.
			if (!binary_operation_is_using && current_operation_priority >= sp_operation_priority || binary_operation_is_using && current_operation_priority > sp_operation_priority)
			{
				if (binary_operation_is_using)
					operators.push('.');//Оператор '.' не является ключевым, он визуальное дополнение оператора усеченной разности '-.'.
				operators.push(logic_function[i]);
			}
			else//Иначе выгружаются все операторы из стека до тех пор, пока условие выше не выполнится.
			{
				while (current_operation_priority < sp_operation_priority && !binary_operation_is_using || 
					binary_operation_is_using && current_operation_priority <= sp_operation_priority)
				{
					logic_function_by_RPN.push_back(operators.top());
					operators.pop();
					if (!operators.empty())
						sp_operation_priority = getOperationPriority(operators.top());
					else
						break;
				}
				if (binary_operation_is_using)//Бинарный оператор.
					operators.push('.');
				operators.push(logic_function[i]);
			}
		}
		else if (logic_function[i] == '.')//Если '.', то пропускается (из соображений выше и учета пользовательского ввода).
			continue;
		else//Если переменная или константа, вводится из соображений выше разделитель '|'.
		{
			if (logic_function[i] == 'x' && !x_is_used)
				x_is_used = true;
			if (logic_function[i] == 'y' && !y_is_used)
				y_is_used = true;
			if (operator_was_added)
			{
				logic_function_by_RPN.push_back('|');
				operator_was_added = false;
			}
			logic_function_by_RPN.push_back(logic_function[i]);
		}
	}
	while (!operators.empty())//Выгружаются все оставшиеся операторы из стека.
	{
		logic_function_by_RPN.push_back(operators.top());
		operators.pop();
	}
	//Вывод преобразованной исходной строки (для удобства).
	/*std::cout << logic_function_by_RPN << std::endl;*/
	//Обработка исключительных ситуаций и соответствующий вывод.
	if (balance_of_brackets != 0)
		return false;
	if (significant_variables_count == 1)
		return (x_is_used && !y_is_used || !x_is_used && y_is_used) ? true : false;
	else
		return (x_is_used && y_is_used) ? true : false;
}
//Выполнение операции отрицания Поста k-значной логики.
int PostSubstraction(const int& number, const int& value_logic)
{
	return (number + 1) % value_logic;
}
//Выполнение операции усеченной разности k-значной логики.
int truncatedDifference(const int& first_operand, const int& second_operand)
{
	return (first_operand > second_operand) ? (first_operand - second_operand) : 0;
}
//Выполнения операции произведения по модулю k (для постоянной функции).
int compositionModuloK(const int& first_operand, const int& second_operand, const int& value_logic)
{
	return first_operand * second_operand % value_logic;
}
//Проверка введенного пользователем множества E.
bool checkStringSetOfValues(const std::string& set_of_values, const int& value_logic, int& number_of_values)
{
	std::string substr_number{};
	//Проверка первого и последнего символа строки.
	if (set_of_values[0] != '{' || set_of_values[set_of_values.size() - 1] != '}')
		return false;
	//Проверка второго и предпоследнего символа строки.
	if (set_of_values[1] == ',' || set_of_values[set_of_values.size() - 2] == ',')
		return false;
	//Проверка оставшихся символов.
	for (int i{ 1 }; i < set_of_values.size() - 1; i++)
	{
		if (!(strElemIsDigit(set_of_values[i]) || set_of_values[i] == ','))//На допустимые символы.
			return false;
		else//Если допустимый символ.
		{
			if (strElemIsDigit(set_of_values[i]))//Построение элемента множества из элементов строки.
				substr_number.push_back(set_of_values[i]);
			if (!strElemIsDigit(set_of_values[i]) || i == set_of_values.size() - 2)//Проверка элемента и запоминание количества введенных элементов множества.
			{
				if (substr_number.empty())
				{
					number_of_values = 0;
					return false;
				}
				number_of_values++;
				if (convertStrToInt(substr_number) >= value_logic)//Если элемент множества не принадлежит E_k, то не допускается.
				{
					number_of_values = 0;
					return false;
				}
				substr_number.clear();
			}
		}
	}
	return (number_of_values > 0) ? true : false;
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Получение функции k-значной логики от пользователя с проверкой на корректность.
std::string getFunctionFromUser(std::string& logic_function_by_RPN, const int& value_logic, const int& significant_variables_count)
{
	while (true)
	{
		if (significant_variables_count == 1)
			std::cout << "f(x/y) = ";
		else
			std::cout << "f(x,y) = ";
		std::string user_logic_function{ };
		std::getline(std::cin, user_logic_function);
		if (checkStringFunction(user_logic_function, value_logic) &&
			checkCharacterSequenceOfStrFunction(user_logic_function) && reversePolishNotationForFunction(user_logic_function, logic_function_by_RPN, significant_variables_count))
		{
			return user_logic_function;
		}
		else
		{
			logic_function_by_RPN.clear();
			std::cout << "Ошибка ввода. Вы ввели функцию некорректно. Повторите ввод: " << std::endl;
		}
	}
}
//Вывод значений заданной функции k-значной логики в виде таблицы.
void functionValuesInTableForm(const std::string& logic_function_by_RPN, const int& value_logic, const int& significant_variables_count, int**& function_values)
{
	if (significant_variables_count == 1)
	{
		std::cout << "_________________" << std::endl;
		std::cout << "| x/y\t" << "|f(x/y)\t|" << std::endl;
		for (int i{}; i < value_logic; i++)
		{
			std::cout << "_________________" << std::endl;
			std::cout << "| " << i << "\t|" << evaluateFunction(logic_function_by_RPN, value_logic, i, 0, function_values) << "\t|" << std::endl;
		}
	}
	else//significant_variables_count == 2
	{
		std::cout << "_________________________" << std::endl;
		std::cout << "| x\t" << "| y\t" << "|f(x,y)\t|" << std::endl;
		for (int i{}; i < value_logic; i++)
			for (int j{}; j < value_logic; j++)
			{
				std::cout << "_________________________" << std::endl;
				std::cout << "| " << i << "\t| " << j << "\t| " << evaluateFunction(logic_function_by_RPN, value_logic, i, j, function_values) << "\t|" << std::endl;
			}
	}
	std::cout << std::endl;
}
//Вычисление значений функции k-значной логики по каждому набору переменных и запоминание значений в квадратной матрице (двумерный динам. массив).
int evaluateFunction(const std::string& logic_function_by_RPN, const int& value_logic, const int& x_value, const int& y_value, int**& function_values)
{
	std::stack<int> operands{};
	std::string sequence_of_digits{};
	for (int i{}; i < logic_function_by_RPN.size(); i++)
	{
		if (logic_function_by_RPN[i] == 'x')
			operands.push(x_value);
		else if (logic_function_by_RPN[i] == 'y')
			operands.push(y_value);
		else if (strElemIsDigit(logic_function_by_RPN[i]))
			operands.push(logic_function_by_RPN[i] - '0');
		else if (logic_function_by_RPN[i] == '|')
			operands.push(-1);
		else if (logic_function_by_RPN[i] == '-' || logic_function_by_RPN[i] == '*')
		{
			int  discharge{ 1 }, second_operand{ discharge * operands.top() };
			operands.pop();
			while (operands.top() != -1)
			{
				discharge *= 10;
				second_operand += operands.top() * discharge;
				operands.pop();
			}
			operands.pop();
			discharge = 1;
			int first_operand{ discharge * operands.top() };
			operands.pop();
			while (!operands.empty() && operands.top() != -1)
			{
				discharge *= 10;
				first_operand += operands.top() * discharge;
				operands.pop();
			}
			if (logic_function_by_RPN[i] == '-')
				operands.push(truncatedDifference(first_operand, second_operand));
			else
				operands.push(compositionModuloK(first_operand, second_operand, value_logic));
		}
		else if (logic_function_by_RPN[i] == '.')
			continue;
		else//Унарный оператор.
		{
			int discharge{ 1 }, current_operand{ discharge * operands.top() };
			operands.pop();
			while (!operands.empty() && operands.top() != -1)
			{
				discharge *= 10;
				current_operand += discharge * operands.top();
				operands.pop();
			}
			operands.push(PostSubstraction(current_operand, value_logic));
		}
	}
	function_values[x_value][y_value] = operands.top();
	return operands.top();
}
//Вывод второй формы заданной функции k-значной логики.
void getTheSecondFormOfTheFunction(const int& significant_variables_count, const int& value_logic, int**& function_values)
{
	bool put_a_plus{};
	std::cout << "Вторая форма: ";
	if (significant_variables_count == 1)
	{
		std::cout << "f(x/y) = ";
		for (int i{}; i < value_logic; i++)
		{
			if (function_values[i][0] == 0)
				continue;
			else if (function_values[i][0] == 1)
			{
				if (put_a_plus)
					std::cout << " + ";
				std::cout << "j_" << i << "(x)";
				if (!put_a_plus)
					put_a_plus = true;
			}
			else
			{
				if (put_a_plus)
					std::cout << " + ";
				std::cout << function_values[i][0] << "j_" << i << "(x)";
				if (!put_a_plus)
					put_a_plus = true;
			}
			
		}
	}
	else
	{
		std::cout << "f(x,y) = ";
		for (int i{}; i < value_logic; i++)
			for (int j{}; j < value_logic; j++)
			{
				if (function_values[i][j] == 0)
					continue;
				else if (function_values[i][j] == 1)
				{
					if (put_a_plus)
						std::cout << " + ";
					std::cout << "j_" << i << "(x)" << "j_" << j << "(y)";
					if (!put_a_plus)
						put_a_plus = true;
				}
				else
				{
					if (put_a_plus)
						std::cout << " + ";
					std::cout << function_values[i][j] << "j_" << i << "(x)" << "j_" << j << "(y)";
					if (!put_a_plus)
						put_a_plus = true;
				}
			}
	}
	if (!put_a_plus)
		std::cout << "0";
	std::cout << "." << std::endl << std::endl;
}
//Получение множества E от пользователя с проверкой на корректность.
std::string getSetValues(const int& value_logic, int& number_of_values)
{
	std::cout << "Введите множество E для определения принадлежности заданной функции к классу T(Е)\n(значения из E_k через ',' без пробелов в фигурных скобках):" << std::endl;
	while (true)
	{
		std::cout << "E = ";
		std::string set_of_values{};
		std::getline(std::cin, set_of_values);
		if (checkStringSetOfValues(set_of_values, value_logic, number_of_values))
			return set_of_values;
		else
			std::cout << "Вы ввели множество Е некорректно. Повторите ввод:" << std::endl;
	}
}
//Проверка принадлежности функции k-значной логики классу T(E).
bool getMembershipFunctionToClass(const std::string& set_of_values, int**& function_values, const int& value_logic, const int& significant_variables_count, const int& number_of_values)
{
	int mass_iter{}, * mass_of_values = new int[number_of_values] {};
	std::string substr_number{};
	for (int i{ 1 }; i < set_of_values.size() - 1; i++)//Получение элементов множества E из введенной пользователем строки.
	{
		if (strElemIsDigit(set_of_values[i]))
			substr_number.push_back(set_of_values[i]);
		if (!strElemIsDigit(set_of_values[i]) || i == set_of_values.size() - 2)
		{
			mass_of_values[mass_iter] = convertStrToInt(substr_number);
			if (mass_iter + 1 < number_of_values) mass_iter++;
			substr_number.clear();
		}
	}
	//Проверка функции k-значной логики на принадлежность классу T(E) для случая одной или двух переменных.
	if (significant_variables_count == 1)
	{
		for (int i{}; i < value_logic; i++)
		{
			bool correct_variable_set{}, correct_function_value{};
			for (int k{}; k < number_of_values; k++)
			{
				if (!correct_variable_set && i == mass_of_values[k])
					correct_variable_set = true;
				if (!correct_function_value && function_values[i][0] == mass_of_values[k])
					correct_function_value = true;
			}
			if (correct_variable_set == true)
			{
				if (correct_function_value == false)
					return false;
			}
		}
	}
	else
	{
		for (int i{}; i < value_logic; i++)
		{
			for (int j{}; j < value_logic; j++)
			{
				bool correct_variable_x{}, correct_variable_y{}, correct_function_value{};
				for (int k{}; k < number_of_values; k++)
				{
					if (!correct_variable_x && i == mass_of_values[k])
						correct_variable_x = true;
					if (!correct_variable_y && j == mass_of_values[k])
						correct_variable_y = true;
					if (!correct_function_value && function_values[i][j] == mass_of_values[k])
						correct_function_value = true;
				}
				if (correct_variable_x == true && correct_variable_y == true)
				{
					if (correct_function_value == false)
						return false;
				}
			}
		}
	}
	//Освобождение выделенной динамической памяти от массива.
	delete[] mass_of_values;
	return true;
}
//Основная функция выполнения программы.
void programExecution()
{
	std::cout << std::endl << "Введите значение k (далее будет использоваться k-значная логика): ";
	int value_logic{ getValueOfLogic() };
	std::cout << std::endl << "Введите значение n (1 или 2 существенные переменные задаваемой функции k-значной логики): ";
	int significant_variables_count{ getCountOfSignificantVariables() };
	std::cout << std::endl << "Введите функцию k-значной логики в аналитической форме." << std::endl;
	getLogicOperationInformation(value_logic, significant_variables_count);//Информация о вводимых операциях и прочих символах.
	//Введенная пользователем функция в обратной польской нотации и в исходном виде соответственно.
	std::string logic_function_by_RPN{}, logic_function{ getFunctionFromUser(logic_function_by_RPN, value_logic, significant_variables_count) };
	//Динамический двумерный массив для хранения значений функции.
	int** function_values = new int* [value_logic] {};
	for (int i{}; i < value_logic; i++)
		function_values[i] = new int[value_logic] {};
	for (int i{}; i < value_logic; i++)
		for (int j{}; j < value_logic; j++)
			function_values[i][j] = -1;
	//Получение значений заданной функции в виде таблицы.
	functionValuesInTableForm(logic_function_by_RPN, value_logic, significant_variables_count, function_values);
	//Вывод второй формы заданной функции.
	getTheSecondFormOfTheFunction(significant_variables_count, value_logic, function_values);
	while (true)
	{
		//Количество элементов множества E.
		int number_of_values{};
		//Получение множества элементов множества E.
		std::string set_of_values{ getSetValues(value_logic, number_of_values) };
		//Проверка принадлежности функции классу T(E).
		if (getMembershipFunctionToClass(set_of_values, function_values, value_logic, significant_variables_count, number_of_values))
			std::cout << "Да, данная функция принадлежит указанному классу T(E)." << std::endl << std::endl;
		else
			std::cout << "Нет, данная функция не принадлежит указанному классу T(E)!" << std::endl << std::endl;
		if (!doItAgain())
			break;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//Освобождение выделенной динамической памяти от массива массивов.
	for (int i{}; i < value_logic; i++)
		delete[] function_values[i];
	delete[] function_values;
}