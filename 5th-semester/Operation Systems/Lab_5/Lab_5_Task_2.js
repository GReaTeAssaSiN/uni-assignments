//������ �� ���������� ���� �������� ��������� � ��������� ������ �������.
if (WScript.Arguments.Count() == 3)
{
	var path_procedure = WScript.Arguments(0);
	var name_procedure = WScript.Arguments(1);
	var mode = WScript.Arguments(2);
	//�������� ��������������� ��������� � ��������.
	var shell = WScript.CreateObject("WScript.Shell");
	shell.run(("%WINDIR%\\notepad.exe " + path_procedure + name_procedure),1,true);
	//���������� ��������� � ����������� �� ���������� ������ ������� ���������.
	if (mode == "cmd")//�������.
	{	
		WScript.Echo("%COMSPEC% /K cscript " + "\"" + path_procedure + name_procedure + "\"");
		shell.run("%COMSPEC% /K cscript " + "\"" + path_procedure + name_procedure + "\"");
	}
	else if (mode == "window")//����.
	{
		WScript.Echo("%COMSPEC% /K wscript " + "\"" + path_procedure + name_procedure + "\"");
		//"& exit" ��������� ����������� ���� ������� ��� ������� �������� ��������� � ������� ������.
		shell.run("%COMSPEC% /K wscript " + "\"" + path_procedure + name_procedure + "\"" + "& exit");
	}
	//����� ����� � �������������� ������ ������ ������� ���������.
	else
		WScript.Echo("������ ������ ������ ������� ���������.");
}
//����� ����� � ���������� �������� ������ ���������.
else
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path_procedure> " + "<name_procedure>.js" + " <mode>");