//Запрос у пользователя числа первых n членов ряда с помощью параметров командной строки.
var obj = WScript.Arguments;
if (WScript.Arguments.Count() == 1)
{
	var n = obj.Item(0);
	WScript.Echo("Число n (первые n членов ряда) =", n);
	//Переменные для подсчета 2^n и (n+1)!.
	var pow_two_n = 1;
	//Переменная для посчета суммы первых n членов ряда.
	var sum = 0;

	//Вычисление факториала (n+1)! рекурсивно.
	function factorial(number)
	{
		if (number <= 1)
			return 1;
		else
			return number*factorial(number - 1);
	}

	//Вычисление суммы первых n членов заданного ряда.
	for (var i = 1; i <= n; i++)
	{
		var n_plus_one_fact = 1;
		pow_two_n *= 2;
		n_plus_one_fact = factorial(i + 1);
		sum += pow_two_n / n_plus_one_fact;
	}

	//Вывод полученной суммы.
	WScript.Echo("Сумма первых", n, "членов заданного ряда: sum =", sum);
}
else
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " 15");

