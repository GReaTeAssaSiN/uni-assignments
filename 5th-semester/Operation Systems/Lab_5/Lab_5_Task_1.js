//����� ���������� � �������� ������� MS-DOS �� ���������� ���� � �������� ����.
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
//����� ���������� � �������� MS-DOS �� ���������� ���� � �������� ����.
else if (WScript.Arguments.Count() == 2)
{
	var path = WScript.Arguments(0);
	var filename = WScript.Arguments(1);

	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /C help " + ">\"" + path + filename + "\"";
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ���������� � �������� ������� MS-DOS �� ������� � ��������� ����.
else if (WScript.Arguments.Count() == 1)
{
	var command = WScript.Arguments(0);
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help " + command;
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ���������� � �������� MS-DOS �� ������� � ��������� ����.
else if (WScript.Arguments.Count() == 0)
{
	var shell = WScript.CreateObject("WScript.Shell");
	var strCommand = "%COMSPEC% /K help"; 
	WScript.Echo(strCommand);
	shell.Run(strCommand);
}
//����� ����� � ���������� �������� ������ ���������.
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <command_name> " + "<file_path>" + " <file_name>.doc");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <file_path>" + " <file_name>.doc");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <command_name>");
	WScript.ECho("�������������: cscript //nologo " + WScript.ScriptFullName);
} 