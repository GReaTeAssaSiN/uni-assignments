//������ � ������������ ����� ������ n ������ ���� � ������� ���������� ��������� ������.
var obj = WScript.Arguments;
if (WScript.Arguments.Count() == 1)
{
	var n = obj.Item(0);
	WScript.Echo("����� n (������ n ������ ����) =", n);
	//���������� ��� �������� 2^n � (n+1)!.
	var pow_two_n = 1;
	//���������� ��� ������� ����� ������ n ������ ����.
	var sum = 0;

	//���������� ���������� (n+1)! ����������.
	function factorial(number)
	{
		if (number <= 1)
			return 1;
		else
			return number*factorial(number - 1);
	}

	//���������� ����� ������ n ������ ��������� ����.
	for (var i = 1; i <= n; i++)
	{
		var n_plus_one_fact = 1;
		pow_two_n *= 2;
		n_plus_one_fact = factorial(i + 1);
		sum += pow_two_n / n_plus_one_fact;
	}

	//����� ���������� �����.
	WScript.Echo("����� ������", n, "������ ��������� ����: sum =", sum);
}
else
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " 15");

