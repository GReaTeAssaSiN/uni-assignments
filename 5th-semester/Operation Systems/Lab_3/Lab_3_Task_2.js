//������ � ������������ ����� ������ n ������ ���� � ������� ���������� ��������� ������.
var obj = WScript.Arguments;
if (WScript.Arguments.Count() == 1)
{
	var n = obj.Item(0);
	WScript.Echo("����� n (������ n ������ ����) =", n);
	//���������� ��� ������� ����� ������ n ������ ����.
	var sum = 0;

	//���������� ����� ������ n ������ ��������� ����.
	for (var i = 2; i <= n+1; i++)
	{
		//���������� ��� �������� n^ln(n) � (ln(n))^n.
		var numenator = 1;
		var denominator = 1;
		numenator = Math.pow(i, Math.log(i));
		denominator = Math.pow(Math.log(i), i);
		sum += numenator/denominator;
	}

	//����� ���������� �����.
	WScript.Echo("����� ������", n, "������ ��������� ����: sum =", sum);
}
else
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " 15");

