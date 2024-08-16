//����������� ��������� ��� ����������� ���������� ��������, ������� ����������� � �����.
function ProcessDirectory(dir,prefix,of) 
{ 
	var foldPrefix=prefix+"-"; 
	prefix+="|"; 
	var newPrefix=prefix+" "; 
	var fc = new Enumerator(dir.SubFolders); 
	while(!fc.atEnd()) 
	{ 
		if (WScript.Arguments.Count() == 3)
			WScript.Echo(foldPrefix+fc.item().Name, "\n");
		else
			of.WriteLine(foldPrefix+fc.Item().Name);
		ProcessDirectory(fc.item(),newPrefix); 
		fc.moveNext();	
	} 
	fc = new Enumerator(dir.Files);
	while(!fc.atEnd()) 
	{
		if (WScript.Arguments.Count() == 3)
			WScript.Echo(prefix+fc.item().Name, "\n");
		else
			of.WriteLine(prefix+fc.item().Name);
		fc.moveNext();
	}
}

if (WScript.Arguments.Count() == 3 || WScript.Arguments.Count() == 4)
{
	//������ �������� �������.
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	//2 ����������� ���������:	
	//2.1 ������� �������� �������;
	var fromDir = fso.CreateFolder(WScript.Arguments(0)); //�������� ������� (���� + ���).
	//2.2 � ������� �������� ������� �������� ����
	//(� ������ ������ � ������� ������� �������� ������� ������� �������� ���� ���������� .txt (�� ������ ������� �������));
	//�������� ���� ��������� � �������� �������� � ���������� ASCII � ����������������, ���� ��� ����������.
	var sourceFile = fso.CreateTextFile(WScript.Arguments(0) + "\\" + WScript.Arguments(1), true, false); //�������� ���� (���� + ���) (����� ���� ��������� ��������)
	//������ � �������� ���� ����� "Hello, world", ����� �������� ���������� � �������� ������ ��������� � ��������������� ��������.
	sourceFile.WriteLine("������, ���!");
	//2.3 ����������� �������� ������� � �������������� �������.
		//2.3.1 �������� ��������������� ��������.	
		var toDir = fso.CreateFolder(WScript.Arguments(2)); //�������������� ������� (���� + ���).
		//2.3.2 ����������� ��������� �������� � �������������� �������.
		fso.CopyFolder(WScript.Arguments(0), WScript.Arguments(2));
	//2.4 �������� �������� ����� � �������������� ��������;
	//�������� �������� "��������" � ���������� �������� "������ ������".
	var copySourceFile = fso.GetFile(WScript.Arguments(2) + "\\" + WScript.Arguments(1)); //��������� ����� � �������������� ��������.
		//objFile.Attributes ���������� �������� ���������� ���������� ������� ������, ������� ������������ �������� ���������������� �����.
		//��������� �������� "1" ���������� ��� ������� ����� � ���������� ������� ����, ���������� �� ������� "������ ������". 
	copySourceFile.Attributes = 1;
	//2.5 ������� ���������� ��������� � ��������������� ���������;
	if (WScript.Arguments.Count() == 3)
	{
		//2.5.1 ���������� ��������� ��������.
		WScript.Echo("���������� ��������� �������� " + WScript.Arguments(0) + "\\\\ :");
		ProcessDirectory(fromDir,"","");
		//2.5.2 ���������� ��������������� ��������.
		WScript.Echo("\n���������� ��������������� �������� " + WScript.Arguments(2) + "\\\\ :");
		ProcessDirectory(toDir,"","");
	}
	else
	{
		//�������������� ���� ��������� � �������������� �������� � ���������� ASCII � ����������������, ���� ��� ����������.
		var resFile = fso.CreateTextFile(WScript.Arguments(2) + "\\" + WScript.Arguments(3), true, false); //�������������� ���� (���� + ���) (����� ���� ��������������� ��������).
		//2.5.1 ���������� ��������� ��������.
		resFile.WriteLine("���������� ��������� �������� " + WScript.Arguments(0) + "\\\\:");
		ProcessDirectory(fromDir,"",resFile);
		//2.5.2 ���������� �������������� ��������.
		resFile.WriteLine("\n���������� ��������������� �������� " + WScript.Arguments(2) + "\\\\:");
		ProcessDirectory(toDir,"",resFile);
	}
	//2.6 ������� ���������� ����� ��������������� ��������;
	//�������� ������ ��� ����������� ������ ����� (path[,iomode[,create[,unicode]]]) (������������ ���� ���������� ������ ��� ������ � ��������� ASCII).
	var textStreamReadFile = fso.OpenTextFile(copySourceFile, 1, false, 0);
	if (WScript.Arguments.Count() == 3)
		WScript.Echo("���������� ����� � �������������� ��������:");
	else
		resFile.WriteLine("\n���������� ����� � �������������� ��������:");
	if (!textStreamReadFile.AtEndOfStream)
	{
		var str = textStreamReadFile.ReadLine();
		if (WScript.Arguments.Count() == 3)
		{
			WScript.Echo(str, "\n");
			while (!textStreamReadFile.AtEndOfStream)
			{
				str = textStreamReadFile.ReadLine();	
				WScript.Echo(str, "\n");
			} 
		}
		else
		{
			resFile.WriteLine(str);
			while (!textStreamReadFile.AtEndOfStream)
			{
				str = textStreamReadFile.ReadLine();
				resFile.WriteLine(str);	
			}
		}
	}
	else
	{
		if (WScript.Arguments.Count() == 3)
			WScript.Echo(str, "\n[���� � �������������� �������� ����! ����������� �� ����������.]");
		else
			resFile.WriteLine(str + "\n[���� � �������������� �������� ����! ����������� �� ����������.]");
	}
	//�������� ��������� ������ � ������/���� ������ �������� ������� ��� �������� ����������(-��) �����(-��).
	textStreamReadFile.Close();
	sourceFile.Close();
	if (WScript.Arguments.Count() == 4)
		resFile.Close();
}
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path>[����������� \\\\] " + "<source_file_name>.txt" + " <to_folder_path>[����������� \\\\] " + " <result_file_name>.txt");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path>[����������� \\\\] " + "<source_file_name>.txt" + " <to_folder_path>[����������� \\\\] ");
}