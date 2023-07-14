#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

bool init(double*** mass, unsigned& NM, unsigned &i1, unsigned &i2)
{
    std::cout << "������� ����������� �������������� ���������� �������: ";
    NM = getIndex();
    std::cout << "������� ����� ������, ������� ���������� �������: ";
    i1 = getIndex() - 1;
    std::cout << "������� ����� �������, ������� ���������� �������: ";
    i2 = getIndex() - 1;
    if (checkIndexes(i1, i2, NM))
    {
        if (makeMass(mass, NM))
        {
            for (unsigned i = 0; i < NM; i++)
            {
                for (unsigned j = 0; j < NM; j++)
                {
                    std::cout << "[" << i << "][" << j << "] = ";
                    *(*((*mass) + i) + j) = getValue();
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        std::cout << "�������� ������(-�) �����(-�) ������ �/��� �������, �������(-��/-��) ���������� �������. ������� �� � �������� ����������� �������." 
            << std::endl;
        return false;
    }
    return true;
}

bool finit(std::istream& f, double*** mass, unsigned& NM, unsigned& i1, unsigned& i2)
{
    f >> NM;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ����������� �������." << std::endl;
        return false;
    }
    f >> i1;
    i1 -= 1;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ������ ������, ������� ���������� �������!";
        return false;
    }
    f >> i2;
    i2 -= 1;
    if (f.fail())
    {
        std::cout << "������ ����� �� ����� ������ �������, ������� ���������� �������!";
        return false;
    }
    if (checkIndexes(i1, i2, NM) && makeMass(mass, NM))
    {
        for (unsigned i = 0; i < NM; i++)
        {
            for (unsigned j = 0; j < NM; j++)
            {
                f >> *(*((*mass) + i) + j);
                if (f.fail())
                {
                    std::cout << "������ ����� �� ����� �������� [" << i << "][" << j << "]." << std::endl;
                    return false;
                }
            }
        }
    }
    else
    {
        std::cout << "�������� ������(-�) ������(-�) ������ �/��� �������, �������(-��/-��) ���������� �������." << std::endl;
        return false;
    }
    return true;
}

void fdelpartmass(std::ostream& f, double** mass, unsigned NM, unsigned i1, unsigned i2)
{
    f << "�������� �������:" << std::endl;
    for (unsigned i = 0; i < NM; i++)
    {
        for (unsigned j = 0; j < NM; j++)
        {
            f << mass[i][j] << "\t";
        }
        f << std::endl << std::endl;
    }
    f << "��������������� ������� ����� �������� " << i1 + 1 << "-� ������ � " << i2 + 1 << "-�� �������:" << std::endl;
    for (unsigned i = i1; i < NM - 1; i++)
    {
        for (unsigned j = 0; j < NM; j++)
        {
            mass[i][j] = mass[i + 1][j];
        }
    }
    for (unsigned i = 0; i < NM; i++)
    {
        for (unsigned j = i2; j < NM - 1; j++)
        {
            mass[i][j] = mass[i][j + 1];
        }
    }
    for (unsigned i = 0; i < NM-1; i++)
    {
        for (unsigned j = 0; j < NM-1; j++)
        {
            f << mass[i][j] << "\t";
        }
        f << std::endl << std::endl;
    }
    f << std::endl;
}

unsigned getIndex()
{
    while (true)
    {
        double a;
        std::cin >> a;
        if (std::cin.fail() || a != int(a) || a <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ �����. ������� ����������� �����: \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

double getValue()
{
    while (true)
    {
        double a;
        std::cin >> a;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ �����. \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

bool getNext()
{
    std::cout << "������ ��������� ���� �������� ������? �� - 1, ��� - 0:" << "\t";
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

bool checkIndexes(unsigned i1, unsigned i2, unsigned NM)
{
    return (i1 >= 0 && i1 < NM&& i2 >= 0 && i2 < NM) ? true : false;
}

bool makeMass(double*** mass, unsigned NM)
{
    *mass = new (std::nothrow) double* [NM];
    if (!(*mass))
    {
        std::cout << "�� ������� �������� ������ ��� �������!" << std::endl;
        return false;
    }
    else
    {
        for (unsigned i = 0; i < NM; i++)
        {
            *(*mass + i) = new (std::nothrow) double[NM];
            if (!(*(*mass + i)))
            {
                std::cout << "�� ������� �������� ������ ��� �������!" << std::endl;
                return false;
            }
        }
    }
    return true;
}