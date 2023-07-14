#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include "constants.h"
#include "myfuncs.h"

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

bool init(double mass[NM])
{
    for (unsigned i = 0; i < NM; i++)
    {
        if (i == 0)
        {
            std::cout << "[x] = ";
        }
        else
        {
            std::cout << "[y" << i << "] = ";
        }
        mass[i] = getValue();
    }
    return true;
}

bool finit(std::ifstream& f, double mass[NM])
{
    for (unsigned i = 0; i < NM; i++)
    {
        f >> mass[i];
        if (f.fail())
        {
            if (i == 0)
            {
                std::cout << "������ ����� �� ����� \"in.txt\" �������� [x]." << std::endl;
            }
            else
            {
                std::cout << "������ ����� �� ����� \"in.txt\" �������� [y" << i << "]." << std::endl;
            }
            return false;
        }
    }
    return true;
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
            std::cout << "������ �����. �� ����� �� �����. ��������� ����: \n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

bool check_FirstCondition(double mass[NM])
{
    return (mass[1] <= mass[0] && mass[0] <= mass[12]) ? true : false;
}

bool check_SecondCondition(double mass[NM], double &t1, double &t2)
{
    t1 = mass[1];
    t2 = mass[12];
    for (unsigned i = 1; i < NM; i++)
    {
        if (mass[i] < t1)
            t1 = mass[i];
        if (mass[i] > t2)
            t2 = mass[i];
    }
    return (t1 <= mass[0] && mass[0] <= t2) ? true : false;
}

void conditions_answer(std::ostream& f, double mass[NM], double t1, double t2)
{
    f << "�������� ������:" << std::endl;
    for (unsigned i = 0; i < NM; i++)
        f << mass[i] << '\t';
    f << std::endl;
    f << "*** ����� ��, ��� y1 <= x <= y12?" << std::endl;
    if (check_FirstCondition(mass))
        f << "��, �����!" << " (" << mass[1] << " <= " << mass[0] << " <= " << mass[12] << ") " << std::endl << std::endl;
    else
        f << "���, �������!" << " (" << mass[1] << " <= " << mass[0] << " <= " << mass[12] << ") " << std::endl << std::endl;
    f << "*** ����� ��, ��� t1 <= x <= t2, ��� t1 - ����������, � t2 - ���������� ����� y1,...,y12?" << std::endl;
    if (check_SecondCondition(mass, t1, t2))
        f << "��, �����!" << " (" << t1 << " <= " << mass[0] << " <= " << t2 << ") " << std::endl;
    else
        f << "���, �������!" << " (" << t1 << " <= " << mass[0] << " <= " << t2 << ") " << std::endl;
}