#include <iostream>
#include "myfuncs.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//���� ��������� �������� ������������.
	bool cycle{ true };
	getAboutInformation();//����� ���������� �� ������ � ��������.
	while (cycle)
	{
		programExecution();//�������� �������, ����������� ���������� ���������.
		printDashes();//�������������� �����.
		if (!exitOrContinue())
			break;
	}
	return 0;
}