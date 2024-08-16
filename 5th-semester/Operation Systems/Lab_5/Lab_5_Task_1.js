//Вывод информации о заданной команде MS-DOS по указанному пути в заданный файл.
if (WScript.Arguments.Count() == 3)
{
	var command = WScript.Arguments(0);
	var path = WScript.Arguments(1);
	var filename = WScript.Arguments(2);

	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + command + ">\"" + path + filename + "\"";
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Вывод информации о командах MS-DOS по указанному пути в заданный файл.
else if (WScript.Arguments.Count() == 2)
{
	var path = WScript.Arguments(0);
	var filename = WScript.Arguments(1);

	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + ">\"" + path + filename + "\"";
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Вывод информации о заданной команде MS-DOS на консоль в отдельном окне.
else if (WScript.Arguments.Count() == 1)
{
	var command = WScript.Arguments(0);
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help " + command;
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Вывод информации о командах MS-DOS на консоль в отдельном окне.
else if (WScript.Arguments.Count() == 0)
{
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help"; 
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//Иначе вывод о допустимых командах данной процедуры.
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>" + " <file_name>.doc");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <file_path>" + " <file_name>.doc");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <command_name>");
	WScript.ECho("Использование: cscript //nologo " + WScript.ScriptFullName);
} 