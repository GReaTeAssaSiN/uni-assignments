if (WScript.Arguments.Count() == 1 || WScript.Arguments.Count() == 2)
{
	//�������� ������� WshShell.
	var shell = WScript.CreateObject("WScript.Shell");
	//�������� ��������� ������ �� ������� ����� � ��������� ����� ����� ������ ��������.
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + WScript.Arguments(0) + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//�������� ����� � ������������ ���������� ���������.	
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	if (WScript.Arguments.Count() == 2)
		var resFile = fso.CreateTextFile(WScript.Arguments(1), true, false);
	
	//��������� ��������� ���������� �����.
	//�������� ������ ��� ����������� ������ ����� (path[,iomode[,create[,unicode]]]) (������������ ���� � ��������� ������� ���������� ������ ��� ������ � ��������� ASCII).
	var textStreamReadFile = fso.OpenTextFile(WScript.Arguments(0), 1, true, 0);
	var word = "";		//���������� ��� ���������� ����� ������������ ����� � �������� ������.
	var max_word_len = 0;	//���������� ��� ���������� ����� �������� ����� � �������� ������.
	if (WScript.Arguments.Count() == 1)
		WScript.Echo("�������� �����:");
	else
		resFile.WriteLine("�������� �����:");
	if (!textStreamReadFile.AtEndOfStream)
	{
		while (!textStreamReadFile.AtEndOfStream)
		{
			//��������� ������ ������� �� ���������� ����� � �������� �������.
			var str = textStreamReadFile.ReadLine();
			if (WScript.Arguments.Count() == 1)
				WScript.Echo(str);
			else
				resFile.WriteLine(str);
			//����������.
			var iter_word = 0; 	//���������� ��� ���������� ��������� �� ������ ���������������� ����� ��������� ������.
			var iter_text = 0; 	//���������� ��� ���������� ��������� �� ��������������� ������� ��������� ������ ��������� ������.
			//�������� �� ��������� ������ ��������� ������.
			while (iter_text < str.length)
			{
				while (str.charAt(iter_text) != ' ' &&
	   	       	       		str.charAt(iter_text) != '.' &&
	    	       	       		str.charAt(iter_text) != ',' &&
	    	       	      		str.charAt(iter_text) != ':' &&
	    	       	      		str.charAt(iter_text) != ';' &&
	    	       	       		str.charAt(iter_text) != '-' &&
	    	       	       		str.charAt(iter_text) != '(' &&
	    	       	       		str.charAt(iter_text) != ')' &&
	    	       	       		str.charAt(iter_text) != '!' &&
	    	       	       		str.charAt(iter_text) != '?' &&
	   	       	       		str.charAt(iter_text) != '"' &&
	    	       	       		str.charAt(iter_text) != '\'')
				{
					iter_text++;
				}
				var word_len = iter_text - iter_word; //����� ���������������� ����� ��������� ������ ��������� ������.
				if (max_word_len <= word_len)
				{
					if (max_word_len == word_len)
						word += ", " + str.substr(iter_word, word_len);	
					else
					{
						max_word_len = word_len;
						word = str.substr(iter_word, word_len);
					}
				}
				iter_text++;
				iter_word = iter_text;
			}
		}
		if (WScript.Arguments.Count() == 1)
		{	
			WScript.Echo("\n������� ����� ������������ �����: " + word + ".");
			WScript.Echo("����� �������� �����: ", max_word_len + ".");
		}
		else
		{	
			resFile.WriteLine("\n������� ����� ������������ �����: " + word + ".");
			resFile.WriteLine("����� �������� �����: " + max_word_len + ".");
		}
	}
	else
	{
		if (WScript.Arguments.Count() == 1)
			WScript.Echo("undefined\n[��������� ���� � �������� ������� ����! ����������� �� ����������.]");
		else
			resFile.WriteLine("undefined\n[��������� ���� � �������� ������� ����! ����������� �� ����������.]");
	}
	//�������� ��������� ������.
	textStreamReadFile.Close();
}
else
{
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt");
	WScript.Echo("�������������: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<path_res_file>.txt");
}