//����� ���������� � ���������� ������ ������ ��������� ����.
var n = 15;
WScript.Echo("����� n (������ n ������ ����) =", n);
//���������� ��� ������� ����� ������ n ������ ����.\
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

