#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include <string>
#include "constants.h"
#include "myfuncs.h"

std::string selectFile(Blank blank, const std::string defaultPath)
{
	std::string s;
	std::cout << "���� �� ����� " << ((blank == Blank::INPUT) ? "�����" : "������") << "[" << defaultPath << "]: ";
	std::getline(std::cin, s);
	if (s.empty())
	{
		return defaultPath;
	}
	else
	{
		return s;
	}
}

bool getNext()
{
	std::cout << "����������?(0 - ���, 1 - ��): ";
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (sm == '0' || sm == '1')
		{
			return sm == '1' ? true : false;
		}
		else
		{
			std::cout << "������ �����. ������� 0 ��� 1: \n";
		}
	}
}

unsigned char get_0_1()
{
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (sm == '0' || sm == '1')
		{
			return sm;
		}
		else
		{
			std::cout << "������ �����. ������� 0 ��� 1: \n";
		}
	}
}

double getLength()
{
	while (true)
	{
		double a;
		std::cin >> a;
		if (std::cin.fail() || a != int(a) || a <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����. ������� ����������� �����. \n";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return a;
		}
	}
}

std::string CheckStrLength(unsigned NM)
{
	while (true)
	{
		std::string StrForCheck;
		std::getline(std::cin, StrForCheck);
		if (StrForCheck.length() != NM)
		{
			std::cout << "����� ������������������ �� ������������� ���������� N (N=" << NM << " != " << StrForCheck.length() << ")."
				<< " ��������� ����: " << std::endl;
		}
		else
		{
			return StrForCheck;
		}
	}
}

bool initStr(Select select, std::istream& f, std::string &subsequence, unsigned &NM)
{
	if (select == Select::CONSOLE)
	{
		std::cout << "������� ����� N (���-�� �������� � ������������������): ";
		double a = getLength();
		NM = int(a);
		std::cout << "������� ������������������ �������� S1,S2,...,Sn: ";
		subsequence = CheckStrLength(NM);
	}
	else
	{
		double length{};
		f >> length;
		if (f.fail() || length <0 || length != int(length))
		{
			std::cout << "������ ����� �� ����� ����� ������������������ S1,S2,...,Sn. ";
			return false;
		}
		NM = int(length);
		std::string m;
		std::getline(f, m);
		std::getline(f, subsequence);
		if (subsequence.length() != NM)
		{
			std::cout << "����� ������������������ �� ������������� ���������� N (N=" << NM << " != " << subsequence.length() << ")." << std::endl;
			return false;
		}
	}
	if (f.fail())
	{
		std::cout << "������ ����� ����� ������������������ �� " << ((Select::FILE == select) ? "�����" : "�������") << "." << std::endl;
		return false;
	}
	return true;
}

void result(std::ostream& f, unsigned NM, std::string strOut)
{
	f << "�������� ������������������: " << std::endl;
	unsigned number{ 0 };
	for (unsigned i = 0; i < NM; i++)
	{
		if (strOut[i] == '+' || strOut[i] == '-' || strOut[i] == '*')
		{
			number++;
		}
	}
	char* mass = new char[number*2];
	unsigned count{ 0 };
	for (unsigned i = 0; i < NM; i++)
	{
		f << strOut[i];
		if (strOut[i] == '+' || strOut[i] == '-' || strOut[i] == '*')
		{
			mass[count++] = strOut[i];
		}
	}
	f << std::endl;
	unsigned countPlus{ 0 };
	unsigned countStar{ 0 };
	unsigned countDash{ 0 };
	f << "a) ������� ��� ����� ������ �������� ����������� ������ \"+\" � ������� ��� ������ \"*\"?" << std::endl;
	for (unsigned i = 0; i < count; i++)
	{
		if (mass[i] == '+')
		{
			countPlus += 1;
		}
		else if (mass[i] == '*')
		{
			countStar += 1;
		}
		else if (mass[i] == '-')
		{
			countDash += 1;
		}
	}
	f << "*** ������ \"+\" �����������: " << countPlus << " ���(-�)." << std::endl;
	f << "*** ������ \"*\" �����������: " << countStar << " ���(-�)." << std::endl << std::endl;
	f << "�) ����� ����� ��������� �������� \"+\",\"-\",\"*\" � ������������������ S1,S2,...,Sn: " << std::endl;
	f << "*** ������� \"+\",\"-\",\"*\" ����������� � �����: " << countPlus + countStar + countDash << " ���(-�)." << std::endl << std::endl;
	delete[] mass;
}