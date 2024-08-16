//Рекурсивная процедура для отображения оглавления каталога, включая подкаталоги и файлы.
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
	//Объект файловой системы.
	var fso = WScript.CreateObject("Scripting.FileSystemObject");
	//2 Копирование каталогов:	
	//2.1 Создать исходный каталог;
	var fromDir = fso.CreateFolder(WScript.Arguments(0)); //Исходный каталог (путь + имя).
	//2.2 С помощью Блокнота создать исходный файл
	//(в данном случае с помощью объекта файловой системы создать исходный файл расширения .txt (по общему условию задания));
	//Исходный файл создается в исходном каталоге с кодировкой ASCII и перезаписывается, если уже существует.
	var sourceFile = fso.CreateTextFile(WScript.Arguments(0) + "\\" + WScript.Arguments(1), true, false); //Исходный файл (путь + имя) (имеет путь исходного каталога)
	//Запись в исходный файл фразы "Hello, world", чтобы отличать содержимое и атрибуты файлов исходного и результирающего каталога.
	sourceFile.WriteLine("Привет, мир!");
	//2.3 Скопировать исходный каталог в результирующий каталог.
		//2.3.1 Создание результирующего каталога.	
		var toDir = fso.CreateFolder(WScript.Arguments(2)); //Результирующий каталог (путь + имя).
		//2.3.2 Копирование исходного каталога в результирующий каталог.
		fso.CopyFolder(WScript.Arguments(0), WScript.Arguments(2));
	//2.4 Изменить атрибуты файла в результирующем каталоге;
	//Удаление атрибута "Архивный" и добавление атрибута "Только чтение".
	var copySourceFile = fso.GetFile(WScript.Arguments(2) + "\\" + WScript.Arguments(1)); //Получение файла в результирующем каталоге.
		//objFile.Attributes возвращает значение логической комбинации битовых флагов, которые представляют атрибуты соответствующего файла.
		//Установка значения "1" сбрасывает все битовые флаги и активирует битовый флаг, отвечающий за атрибут "Только чтение". 
	copySourceFile.Attributes = 1;
	//2.5 Вывести оглавление исходного и результирующего каталогов;
	if (WScript.Arguments.Count() == 3)
	{
		//2.5.1 Оглавление исходного каталога.
		WScript.Echo("Оглавление исходного каталога " + WScript.Arguments(0) + "\\\\ :");
		ProcessDirectory(fromDir,"","");
		//2.5.2 Оглавление результирующего каталога.
		WScript.Echo("\nОглавление результирующего каталога " + WScript.Arguments(2) + "\\\\ :");
		ProcessDirectory(toDir,"","");
	}
	else
	{
		//Результирующий файл создается в результирующем каталоге с кодировкой ASCII и перезаписывается, если уже существует.
		var resFile = fso.CreateTextFile(WScript.Arguments(2) + "\\" + WScript.Arguments(3), true, false); //Результирующий файл (путь + имя) (имеет путь результирующего каталога).
		//2.5.1 Оглавление исходного каталога.
		resFile.WriteLine("Оглавление исходного каталога " + WScript.Arguments(0) + "\\\\:");
		ProcessDirectory(fromDir,"",resFile);
		//2.5.2 Оглавление результирющего каталога.
		resFile.WriteLine("\nОглавление результирующего каталога " + WScript.Arguments(2) + "\\\\:");
		ProcessDirectory(toDir,"",resFile);
	}
	//2.6 Вывести содержимое файла результирующего каталога;
	//Открытие потока для построчного чтения файла (path[,iomode[,create[,unicode]]]) (существующий файл открываетя только для чтения в кодировке ASCII).
	var textStreamReadFile = fso.OpenTextFile(copySourceFile, 1, false, 0);
	if (WScript.Arguments.Count() == 3)
		WScript.Echo("Содержимое файла в результирующем каталоге:");
	else
		resFile.WriteLine("\nСодержимое файла в результирующем каталоге:");
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
			WScript.Echo(str, "\n[Файл в результирующем каталоге пуст! Содержимого не обнаружено.]");
		else
			resFile.WriteLine(str + "\n[Файл в результирующем каталоге пуст! Содержимого не обнаружено.]");
	}
	//Закрытие открытого потока и одного/двух неявно открытых потоков при создании текстового(-ых) файла(-ов).
	textStreamReadFile.Close();
	sourceFile.Close();
	if (WScript.Arguments.Count() == 4)
		resFile.Close();
}
else
{
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path>[используйте \\\\] " + "<source_file_name>.txt" + " <to_folder_path>[используйте \\\\] " + " <result_file_name>.txt");
	WScript.Echo("Использование: cscript //nologo " + WScript.ScriptFullName + " <from_folder_path>[используйте \\\\] " + "<source_file_name>.txt" + " <to_folder_path>[используйте \\\\] ");
}