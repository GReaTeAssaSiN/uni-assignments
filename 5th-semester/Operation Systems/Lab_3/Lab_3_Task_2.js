//Запрос у пользователя числа первых n членов ряда с помощью параметров командной строки.
var obj = WScript.Arguments;
if (WScript.Arguments.Count() == 1)
{
	var n = obj.Item(0);
	WScript.Echo("Число n (первые n членов ряда) =", n);
	//Переменная для посчета суммы первых n членов ряда.
	var sum = 0;

	//Вычисление суммы первых n членов заданного ряда.
	for (var i = 2; i <= n+1; i++)
	{
		//Переменные для подсчета n^ln(n) и (ln(n))^n.
		var numenator = 1;
		var denominator = 1;
		numenator = Math.pow(i, Math.log(i));
		denominator = Math.pow(Math.log(i), i);
		sum += numenator/denominator;
	}

	//Вывод полученной суммы.
	WScript.Echo("Сумма первых", n, "членов заданного ряда: sum =", sum);
}
else
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " 15");

