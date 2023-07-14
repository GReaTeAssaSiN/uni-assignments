#include <iostream>
#include <string>
#include <math.h>
#include "myfuncs.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Rus");
	if (argc == 4)
	{
		unsigned long long nnum;
		unsigned int bit;
		unsigned long long nbit;
		try
		{
			nnum = std::stoull(argv[1]);
			bit = static_cast<unsigned int>(std::stoi(argv[2]));
			nbit = static_cast<unsigned long long>(std::stoi(argv[3]));
		}
		catch (const::std::invalid_argument& ia)
		{
			std::cerr << "���������� ������������� ��������(-�) � ����� ����: " << ia.what() << std::endl;
			return 0;
		}
		unsigned long long copynnum{ nnum };
		unsigned int flag{ 1 };
		if (static_cast<unsigned long long>(nnum) < 0 || static_cast<long long>(nnum) > 18446744073709551615)
		{
			std::cout << "������ ����� ����� nnum! ������� � ��������� ��� ����� � ��������� 8 ���� (�� 0 �� 2^64-1)." << std::endl;
			return 0;
		}
		if (nbit >= 0 && nbit <= 64)
		{
			nnum = shiftr(nnum, bit, nbit, flag);
			if (flag != 0)
			{
				std::cout << "�������� �������� nnum : " << copynnum << std::endl;
				std::cout << "�������� nnum ����� ������ ���� � ��������� �������: " << nnum << std::endl;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			std::cerr << "������� ������� ������� ������������� ���� nbit!" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "���������� ������� ������ ��������� ��������� ������: "
			<< "**���� �� ���������**, **����� nnum**, **��� bit**, **������� ���� nbit**." << std::endl;
	}
	return 0;
}