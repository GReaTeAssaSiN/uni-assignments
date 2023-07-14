#include <iostream>
#include <bitset>
#include "myfuncs.h"

unsigned long long shiftr(unsigned long long nnum, unsigned int bit, unsigned long long nbit, unsigned int& flag)
{
	unsigned long long a = nnum;
	unsigned int count{};
	for (unsigned i = 0; i < 64; i++)
	{
		if (a / 2 != 0)
		{
			count++;
			a /= 2;
		}
		else
		{
			count++;
			break;
		}
	}
	unsigned char nbyte{};
	if (count % 8 == 0)
	{
		nbyte = count / 8;
	}
	else
	{
		nbyte = count / 8 + 1;
	}
	std::bitset<64> BinaryNumber = nnum;
	std::cout << "¬аше исходное число nnum в двоичном представлении (по 4 бита): ";
	for (int i = nbyte*2 - 1; i > -1; i--)
	{
		for (int j = 3; j > -1; j--)
		{
			std::cout << BinaryNumber[j + i * 4];
		}
		std::cout << ' ';
	}
	std::cout << std::endl;

	nbyte = static_cast<unsigned char>(nbyte);
	unsigned long long mask;
	{
		switch (nbyte) {
		case 1: mask = 0xFF; break;
		case 2: mask = 0xFFFF; break;
		case 3: mask = 0xFFFFFF; break;
		case 4: mask = 0xFFFFFFFF; break;
		case 5: mask = 0xFFFFFFFFFF; break;
		case 6: mask = 0xFFFFFFFFFFFF; break;
		case 7: mask = 0xFFFFFFFFFFFFFF; break;
		case 8: mask = 0xFFFFFFFFFFFFFFFF; break;
		default:;
		}
	}
	if (0 <= nbit && nbit <= (static_cast<unsigned long long>(count) - 1))
	{
		if (bit == 1 || bit == 0)
		{
			if (bit == 1)
			{
				nnum = mask & (((mask & 0x1) << nbit) | nnum);
			}
			else
			{
				nnum = mask & (~((mask & 0x1) << nbit) & nnum);
			}
			std::bitset<64> BinaryNumber = nnum;
			std::cout << "¬аше число nnum в двоичном представлении (по 4 бита) после преобразований: ";
			for (int i = nbyte * 2 - 1; i > -1; i--)
			{
				for (int j = 3; j > -1; j--)
				{
					std::cout << BinaryNumber[j + i * 4];
				}
				std::cout << ' ';
			}
			std::cout << std::endl;
			return nnum;
		}
		else
		{
			std::cout << "ќшибочно указано значение бита bit! ќно должно быть равно \"0\" или \"1\"." << std::endl;
			flag = 0;
			return 0;
		}
	}
	else
	{
		std::cout << "ќшибочно указана позици€ записываемого бита nbit!" << std::endl;
		flag = 0;
		return 0;
	}
}