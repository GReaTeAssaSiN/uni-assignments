//Запуск по указанному пути заданной процедуры в выбранном режиме запуска.
if (WScript.Arguments.Count() == 3)
{
	var path_procedure = WScript.Arguments(0);
	var name_procedure = WScript.Arguments(1);
	var mode = WScript.Arguments(2);
	//Открытие соответствующей процедуры в Блокноте.
	var shell = WScript.CreateObject("WScript.Shell");
	shell.run(("%WINDIR%\\notepad.exe " + path_procedure + name_procedure),1,true);
	//Выполнение процедуры в зависимости от выбранного режима запуска процедуры.
	if (mode == "cmd")//Консоль.
	{	
		WScript.Echo("%COMSPEC% /K cscript " + "\"" + path_procedure + name_procedure + "\"");
		shell.run("%COMSPEC% /K cscript " + "\"" + path_procedure + name_procedure + "\"");
	}
	else if (mode == "window")//Окно.
	{
		WScript.Echo("%COMSPEC% /K wscript " + "\"" + path_procedure + name_procedure + "\"");
		//"& exit" закрывает всплывающее окно консоли при запуске заданной процедуры в оконном режиме.
		shell.run("%COMSPEC% /K wscript " + "\"" + path_procedure + name_procedure + "\"" + "& exit");
	}
	//Иначе вывод о некорректности выбора режима запуска процедуры.
	else
		WScript.Echo("Ошибка выбора режима запуска процедуры.");
}
//Иначе вывод о допустимых командах данной процедуры.
else
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path_procedure> " + "<name_procedure>.js" + " <mode>");