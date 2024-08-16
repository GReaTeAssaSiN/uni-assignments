if (WScript.Arguments.Count() == 1 || WScript.Arguments.Count() == 2)
{
	//Создание объекта WshShell.
	var shell = WScript.CreateObject("WScript.Shell");
	//Создание исходного текста на русском языке в текстовом файле путем вызова блокнота.
	var strSourceFile = "%WINDIR%\\notepad.exe " + "\"" + WScript.Arguments(0) + "\"";
	shell.Run(shell.ExpandEnvironmentStrings(strSourceFile),1,true);

	//Создание файла с результатами выполнения процедуры.	
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	if (WScript.Arguments.Count() == 2)
		var resFile = fso.CreateTextFile(WScript.Arguments(1), true, false);
	
	//Обработка исходного текстового файла.
	//Открытие потока для построчного чтения файла (path[,iomode[,create[,unicode]]]) (существующий файл с исходными данными открываетя только для чтения в кодировке ASCII).
	var textStreamReadFile = fso.OpenTextFile(WScript.Arguments(0), 1, true, 0);
	var word = "";		//Переменная для сохранения слова максимальной длины в исходном тексте.
	var max_word_len = 0;	//Переменная для сохранения длины искомого слова в исходном тексте.
	if (WScript.Arguments.Count() == 1)
		WScript.Echo("Исходный текст:");
	else
		resFile.WriteLine("Исходный текст:");
	if (!textStreamReadFile.AtEndOfStream)
	{
		while (!textStreamReadFile.AtEndOfStream)
		{
			//Считываем первую строчку из текстового файла с исходным текстом.
			var str = textStreamReadFile.ReadLine();
			if (WScript.Arguments.Count() == 1)
				WScript.Echo(str);
			else
				resFile.WriteLine(str);
			//Переменные.
			var iter_word = 0; 	//Переменная для сохранения указателя на начале рассматриваемого слова исходного текста.
			var iter_text = 0; 	//Переменная для сохранения указателя на рассматриваемом символе считанной строки исходного текста.
			//Итерация по считанной строке исходного текста.
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
				var word_len = iter_text - iter_word; //Длина рассматриваемого слова считанной строки исходного текста.
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
			WScript.Echo("\nИскомое слово максимальной длины: " + word + ".");
			WScript.Echo("Длина искомого слова: ", max_word_len + ".");
		}
		else
		{	
			resFile.WriteLine("\nИскомое слово максимальной длины: " + word + ".");
			resFile.WriteLine("Длина искомого слова: " + max_word_len + ".");
		}
	}
	else
	{
		if (WScript.Arguments.Count() == 1)
			WScript.Echo("undefined\n[Текстовый файл с исходным текстом пуст! Содержимого не обнаружено.]");
		else
			resFile.WriteLine("undefined\n[Текстовый файл с исходным текстом пуст! Содержимого не обнаружено.]");
	}
	//Закрытие открытого потока.
	textStreamReadFile.Close();
}
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <path_source_file>.txt " + "<path_res_file>.txt");
}