#include <iostream>
#include <stack>
#include <string>
#include "myfuncs.h"

/*���������������� ����*/
//���������� � ������ ������ � ������ � ������ ������, ������ ��������, ��� �����������.
void getAboutInformation()
{
	printDashes();
	//����� ��������.
	std::cout << "\t\t\t\t\t\t\t\t\t\t\t    ������� ������� ��������" << std::endl <<
		"\t\t\t\t\t\t\t\t\t\t\t\t\t ������ " << g << std::endl;
	std::cout << "����� ������ g = " << g << std::endl;
	std::cout << "����� � ������ ������ n = " << n << std::endl << std::endl;
	std::cout << "������� �������� �� ����. 1 ���������� ��� ������� (g + n - 1)(mod 6) + 1, ��� s = [n / 7], [.] - ����� ����� �����." << std::endl <<
		"����� �������, ����� ������� �������� �� ����. 1: '" << (g + n - 1) % 6 + 1 << "'. _x - ��������� ����� " << 
		"(���������� s �� ���������)." << std::endl << std::endl;
	std::cout << "�������� �������� �� ����. 2 ���������� ��� ������� (g + n - 1)(mod 7) + 1." << std::endl <<
		"����� �������, ����� �������� �������� �� ����. 2: " << "'" << (g + n - 1) % 7 + 1 << "'. x-.y - ��������� ��������." << std::endl << std::endl;
	std::cout << "����������� ����� ������������� ������� ��� ������� (g + n - 1)(mod 3) + 1." << std::endl <<
		"����� �������, ����� ����������� ����� ������������� �������: '" << (g + n - 1) % 3 + 1 << "'. ������ �����." << std::endl;
	printDashes();
}
//����� ����������� ���������� ����� ���������� ������������ � �������.
void printDashes()
{
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
}
//����� ������������ ���������� �� ������� � �������� ���������.
void getLogicOperationInformation(const int& value_logic, const int& n)
{
	printDashes();
	std::cout << "����� ��������� ���������� �� ��������� � ������ k-������� ������ (������� ������������ ��� �����������):" << std::endl <<
		"I. ��������� �������� �������: 0, 1, 2, ..., k - 1." << std::endl;
	std::cout << "II. ������� ��������:\n" << "\t* ��������� ����� - '_x' � �.�." << std::endl;
	if (n == 1)
		std::cout << "III. �������� ��������:\n" << "\t* ��������� �������� - 'x-.2' � �.�." << std::endl;
	if (n == 2)
		std::cout << "III. �������� ��������:\n" << "\t* ��������� �������� - 'x-.y' � �.�." << std::endl;
	printDashes();
	std::cout << "�� ������ ������ ������� ��� ��������, ��������� ������ �������� ��������� ����� � ��������� �������� (� ������ �����\n������������ ���������� � ����������), " <<
		"���������� 'x' �/��� 'y' (� - ���� ������������ 2 ������������ ����������\n� ���������� ������� k - ������� ������), ������������� ��������� (0, ..., " << 
		value_logic - 1 << ")." << std::endl;	
}
//������� ���������� ���� ��������� E.
bool doItAgain()
{
	std::cout << "�� ������� ���������� ���� ��������� E � �������� �������������� ������ ������� ������ T(E)?" << std::endl <<
		"�� (yes)/ ��� (no): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "yes")
			return true;
		else if (user_wishes == "no")
			return false;
		else
			std::cout << "������ �����. �� ������ ������ 'yes' ��� 'no'. ��������� ����: ";
	}
}
//����� �� ��������� ��� ����������� ������.
bool exitOrContinue()
{
	std::cout << "�� ������� ���������� ���������� ��������� ��� ������ �����?" << std::endl <<
		"���������� (continue)/ ����� (exit): ";
	while (true)
	{
		std::string user_wishes{};
		std::getline(std::cin, user_wishes);
		if (user_wishes == "continue")
			return true;
		else if (user_wishes == "exit")
			return false;
		else
			std::cout << "������ �����. �� ������ ������ 'continue' ��� 'exit'. ��������� ����: ";
	}
}

/*��������������� �������*/
//�������� �������� ������������� ������ �� ����������� �������������� � ����� �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)//�������� �� ������ - �����. ������.
	{
		if ((i == 0) && (tempStr[i] == '-'))//���� ������ �������� ����� '-', �� �� �����������.
			continue;
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))//���� ������ �� �������� ������, �� ������ �� �������� ������.
			return false;
	}
	return !tempStr.empty();//���� ������ ����� �������� �� ������, �� ��� �������� ������.
}
//�������������� �������� ������������� ������ � �����.
int convertStrToInt(std::string convertStr)
{
	double number{};
	bool negative_number{ false };
	for (int i{}; i < convertStr.length(); i++)//�������� �� ������ - �����. ������.
	{
		if ((i == 0) && (convertStr[i] == '-'))//���� ������ �������� ����� �����, �� ������� ����� ���������� ������ �������������� �����.
		{
			negative_number = true;
			continue;
		}
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);//����������� ������ � �����.
	}
	return negative_number ? static_cast<int>(-number) : static_cast<int>(number);//����������� ����� (�������������� ��� ��������������).
}
//��������� k-������� ������ �� ������������.
int getValueOfLogic()
{
	while (true)
	{
		std::string value_of_logic{};
		std::getline(std::cin, value_of_logic);
		if (checkStrIsNumeric(value_of_logic) && convertStrToInt(value_of_logic) > 0)//���� ��������� ������ �����, ������� ������ 0, �� �����������.
			return convertStrToInt(value_of_logic);
		else//����� ��������� ����.
			std::cout << "������ �����. �� ������ ������ ����� ������������� �����. ��������� ����: ";
	}
}
//��������� ���������� ������������ ���������� k-������� ������ �� ������������.
int getCountOfSignificantVariables()
{
	while (true)
	{
		std::string count_of_significant_variables{};
		std::getline(std::cin, count_of_significant_variables);
		if (checkStrIsNumeric(count_of_significant_variables) &&
			(convertStrToInt(count_of_significant_variables) == 1 || convertStrToInt(count_of_significant_variables) == 2))//���� ����� ������������ ���������� = 1 ��� =2, �� �����������.
			return convertStrToInt(count_of_significant_variables);
		else//����� ��������� ����.
			std::cout << "������ �����. �� ������ ������ '1' ��� '2'. ��������� ����: ";
	}
}
//�������� ��������� ������������� ������� �� ���������� �������.
bool checkStringFunction(const std::string& user_logic_function, const int& value_logic)
{
	for (int i{}; i < user_logic_function.size(); i++)//�������� �� ������.
	{
		if (!strElemIsDigit(user_logic_function[i]))//���� ������ ������ - �� �����.
		{
			bool correct_symbol{};
			for (int j{}; j < mass_of_symbols.size(); j++)//�������� �� ������� ���������� ��������.
			{
				if (user_logic_function[i] == mass_of_symbols[j])
				{
					correct_symbol = true;
					break;
				}
			}
			if (!correct_symbol)//���� ������ ������ - ���������� ������, �� �����������.
				return false;
		}
		else//����� - ���� �����.
		{
			std::string substr_numeric{};//���������, �������� � ���� �����.
			int checking_index{ i + 1 };//�������������� �������� �� ������.
			substr_numeric.push_back(user_logic_function[i]);//���������� �������� ������� � ���������.
			while ((checking_index != user_logic_function.size()) && strElemIsDigit(user_logic_function[checking_index]))//��� ������� ������, ���������� ������� �������� �����, ����������� � ���������.
			{
				substr_numeric.push_back(user_logic_function[checking_index]);
				checking_index++;
			}
			if (!(convertStrToInt(substr_numeric) >= 0 && convertStrToInt(substr_numeric) < value_logic))//���� ����� �� ����������� ��������� E_k, �� �� �����������.
				return false;
		}
	}
	return true;//����� ������ �����������.
}
//�������� ��������� ������������� ������� �� ���������� ������������������ ��������.
bool checkCharacterSequenceOfStrFunction(const std::string& user_logic_function)
{
	for (int i{}; i < user_logic_function.size() - 1; i++)//�������� �� ������.
	{
		//��������� ��������.
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
		else//���� �����.
		{
			if (user_logic_function[static_cast<char>(i + 1)] == 'x' || user_logic_function[static_cast<char>(i + 1)] == 'y' || user_logic_function[static_cast<char>(i + 1)] == '(' ||
				user_logic_function[static_cast<char>(i + 1)] == '_' || user_logic_function[static_cast<char>(i + 1)] == '.')
				return false;
		}
	}
	//�������� ������� ������� ������.
	if (user_logic_function[0] == ')' || user_logic_function[0] == '-' || user_logic_function[0] == '.')
		return false;
	//�������� ���������� ������� ������.
	if (user_logic_function[user_logic_function.size() - 1] == '(' || user_logic_function[user_logic_function.size() - 1] == '-' ||
		user_logic_function[user_logic_function.size() - 1] == '.' || user_logic_function[user_logic_function.size() - 1] == '_')
	{
		return false;
	}
	return true;
}
//��������� ���������� �������� � k-������� ������.
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
//�������� �������� ������ �� ������������ �����.
bool strElemIsDigit(const char& str_elem)
{
	return (str_elem >= '0' && str_elem <= '9') ? true : false;
}
//�������������� ��������� ������� k-������� ������ �� ������ �������� �������� ������� (�������� ���������).
bool reversePolishNotationForFunction(const std::string& logic_function, std::string& logic_function_by_RPN, const int& significant_variables_count)
{
	//����� ��� ��������� �������������� ��������.
	bool x_is_used{}, y_is_used{};
	int balance_of_brackets{};//������ ������ '(' � ')'.

	//���� ��� ����� �������������� �������� ����� ����������� � ����������� (�.�. ����� ��� �� ����, ������ ���� �������� ��������� ��� �������� ����������).
	bool operator_was_added{};
	std::stack<char> operators{};//���� ����������.
	for (int i{}; i < logic_function.size(); i++)//�������� �� ����� �������� ������ � ���������� ������ �� ������ ���.
	{
		bool binary_operation_is_using{};//���� ������������� �������� ��������.
		if (logic_function[i] == '(')//���� '(', �� �������� � ���� ����������.
		{
			operators.push(logic_function[i]);
			operator_was_added = true;
			balance_of_brackets++;
		}
		else if (logic_function[i] == ')')//���� ')', �� ���������� ��� ��������� �� '('. ����� ������ ������������.
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
		else if (logic_function[i] == '_' || logic_function[i] == '-')//���� ���� ��������.
		{
			operator_was_added = true;
			if (logic_function[i] == '-')//�������� ��������.
				binary_operation_is_using = true;
			int current_operation_priority{ getOperationPriority(logic_function[i]) }, sp_operation_priority{};//������������ ���������� �������� � � ������� ����� ����������.
			if (!operators.empty())
				sp_operation_priority = getOperationPriority(operators.top());
			//���� ������� ��������, �� � ������ ���������� �������� ��������� >= ���������� ��������� � ������� ����� ������� �������� �������� � ����.
			//���� �� �������� ��������, �� ������ >.
			if (!binary_operation_is_using && current_operation_priority >= sp_operation_priority || binary_operation_is_using && current_operation_priority > sp_operation_priority)
			{
				if (binary_operation_is_using)
					operators.push('.');//�������� '.' �� �������� ��������, �� ���������� ���������� ��������� ��������� �������� '-.'.
				operators.push(logic_function[i]);
			}
			else//����� ����������� ��� ��������� �� ����� �� ��� ���, ���� ������� ���� �� ����������.
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
				if (binary_operation_is_using)//�������� ��������.
					operators.push('.');
				operators.push(logic_function[i]);
			}
		}
		else if (logic_function[i] == '.')//���� '.', �� ������������ (�� ����������� ���� � ����� ����������������� �����).
			continue;
		else//���� ���������� ��� ���������, �������� �� ����������� ���� ����������� '|'.
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
	while (!operators.empty())//����������� ��� ���������� ��������� �� �����.
	{
		logic_function_by_RPN.push_back(operators.top());
		operators.pop();
	}
	//����� ��������������� �������� ������ (��� ��������).
	/*std::cout << logic_function_by_RPN << std::endl;*/
	//��������� �������������� �������� � ��������������� �����.
	if (balance_of_brackets != 0)
		return false;
	if (significant_variables_count == 1)
		return (x_is_used && !y_is_used || !x_is_used && y_is_used) ? true : false;
	else
		return (x_is_used && y_is_used) ? true : false;
}
//���������� �������� ��������� ����� k-������� ������.
int PostSubstraction(const int& number, const int& value_logic)
{
	return (number + 1) % value_logic;
}
//���������� �������� ��������� �������� k-������� ������.
int truncatedDifference(const int& first_operand, const int& second_operand)
{
	return (first_operand > second_operand) ? (first_operand - second_operand) : 0;
}
//���������� �������� ������������ �� ������ k (��� ���������� �������).
int compositionModuloK(const int& first_operand, const int& second_operand, const int& value_logic)
{
	return first_operand * second_operand % value_logic;
}
//�������� ���������� ������������� ��������� E.
bool checkStringSetOfValues(const std::string& set_of_values, const int& value_logic, int& number_of_values)
{
	std::string substr_number{};
	//�������� ������� � ���������� ������� ������.
	if (set_of_values[0] != '{' || set_of_values[set_of_values.size() - 1] != '}')
		return false;
	//�������� ������� � �������������� ������� ������.
	if (set_of_values[1] == ',' || set_of_values[set_of_values.size() - 2] == ',')
		return false;
	//�������� ���������� ��������.
	for (int i{ 1 }; i < set_of_values.size() - 1; i++)
	{
		if (!(strElemIsDigit(set_of_values[i]) || set_of_values[i] == ','))//�� ���������� �������.
			return false;
		else//���� ���������� ������.
		{
			if (strElemIsDigit(set_of_values[i]))//���������� �������� ��������� �� ��������� ������.
				substr_number.push_back(set_of_values[i]);
			if (!strElemIsDigit(set_of_values[i]) || i == set_of_values.size() - 2)//�������� �������� � ����������� ���������� ��������� ��������� ���������.
			{
				if (substr_number.empty())
				{
					number_of_values = 0;
					return false;
				}
				number_of_values++;
				if (convertStrToInt(substr_number) >= value_logic)//���� ������� ��������� �� ����������� E_k, �� �� �����������.
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

/*�������� �������*/
//��������� ������� k-������� ������ �� ������������ � ��������� �� ������������.
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
			std::cout << "������ �����. �� ����� ������� �����������. ��������� ����: " << std::endl;
		}
	}
}
//����� �������� �������� ������� k-������� ������ � ���� �������.
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
//���������� �������� ������� k-������� ������ �� ������� ������ ���������� � ����������� �������� � ���������� ������� (��������� �����. ������).
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
		else//������� ��������.
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
//����� ������ ����� �������� ������� k-������� ������.
void getTheSecondFormOfTheFunction(const int& significant_variables_count, const int& value_logic, int**& function_values)
{
	bool put_a_plus{};
	std::cout << "������ �����: ";
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
//��������� ��������� E �� ������������ � ��������� �� ������������.
std::string getSetValues(const int& value_logic, int& number_of_values)
{
	std::cout << "������� ��������� E ��� ����������� �������������� �������� ������� � ������ T(�)\n(�������� �� E_k ����� ',' ��� �������� � �������� �������):" << std::endl;
	while (true)
	{
		std::cout << "E = ";
		std::string set_of_values{};
		std::getline(std::cin, set_of_values);
		if (checkStringSetOfValues(set_of_values, value_logic, number_of_values))
			return set_of_values;
		else
			std::cout << "�� ����� ��������� � �����������. ��������� ����:" << std::endl;
	}
}
//�������� �������������� ������� k-������� ������ ������ T(E).
bool getMembershipFunctionToClass(const std::string& set_of_values, int**& function_values, const int& value_logic, const int& significant_variables_count, const int& number_of_values)
{
	int mass_iter{}, * mass_of_values = new int[number_of_values] {};
	std::string substr_number{};
	for (int i{ 1 }; i < set_of_values.size() - 1; i++)//��������� ��������� ��������� E �� ��������� ������������� ������.
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
	//�������� ������� k-������� ������ �� �������������� ������ T(E) ��� ������ ����� ��� ���� ����������.
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
	//������������ ���������� ������������ ������ �� �������.
	delete[] mass_of_values;
	return true;
}
//�������� ������� ���������� ���������.
void programExecution()
{
	std::cout << std::endl << "������� �������� k (����� ����� �������������� k-������� ������): ";
	int value_logic{ getValueOfLogic() };
	std::cout << std::endl << "������� �������� n (1 ��� 2 ������������ ���������� ���������� ������� k-������� ������): ";
	int significant_variables_count{ getCountOfSignificantVariables() };
	std::cout << std::endl << "������� ������� k-������� ������ � ������������� �����." << std::endl;
	getLogicOperationInformation(value_logic, significant_variables_count);//���������� � �������� ��������� � ������ ��������.
	//��������� ������������� ������� � �������� �������� ������� � � �������� ���� ��������������.
	std::string logic_function_by_RPN{}, logic_function{ getFunctionFromUser(logic_function_by_RPN, value_logic, significant_variables_count) };
	//������������ ��������� ������ ��� �������� �������� �������.
	int** function_values = new int* [value_logic] {};
	for (int i{}; i < value_logic; i++)
		function_values[i] = new int[value_logic] {};
	for (int i{}; i < value_logic; i++)
		for (int j{}; j < value_logic; j++)
			function_values[i][j] = -1;
	//��������� �������� �������� ������� � ���� �������.
	functionValuesInTableForm(logic_function_by_RPN, value_logic, significant_variables_count, function_values);
	//����� ������ ����� �������� �������.
	getTheSecondFormOfTheFunction(significant_variables_count, value_logic, function_values);
	while (true)
	{
		//���������� ��������� ��������� E.
		int number_of_values{};
		//��������� ��������� ��������� ��������� E.
		std::string set_of_values{ getSetValues(value_logic, number_of_values) };
		//�������� �������������� ������� ������ T(E).
		if (getMembershipFunctionToClass(set_of_values, function_values, value_logic, significant_variables_count, number_of_values))
			std::cout << "��, ������ ������� ����������� ���������� ������ T(E)." << std::endl << std::endl;
		else
			std::cout << "���, ������ ������� �� ����������� ���������� ������ T(E)!" << std::endl << std::endl;
		if (!doItAgain())
			break;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//������������ ���������� ������������ ������ �� ������� ��������.
	for (int i{}; i < value_logic; i++)
		delete[] function_values[i];
	delete[] function_values;
}