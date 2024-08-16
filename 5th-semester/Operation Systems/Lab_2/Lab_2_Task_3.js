//Инициализация экземпляра объекта String для задания исходного текста.
var str_text = new String(["Теперь не время думать о том, чего у тебя нет. Подумай о том , как бы обойтись с тем, что есть."]);
WScript.Echo("Исходный текст: " + str_text);
//Переменные.
var str_char = 'т'; //Строковый литерал - заданный символ.
var iter_ind = 0; //Переменная для интерации по исходному тексту.
var word_count = 0; //Количество отобранных слов по условию задачи.

//Итерация по исходному тексту.
while (iter_ind < str_text.length)
{
	if (str_text.charAt(iter_ind) != ' ' &&
	    str_text.charAt(iter_ind) != '.' &&
	    str_text.charAt(iter_ind) != ',' &&
	    str_text.charAt(iter_ind) != ':' &&
	    str_text.charAt(iter_ind) != ';' &&
	    str_text.charAt(iter_ind) != '-' &&
	    str_text.charAt(iter_ind) != '(' &&
	    str_text.charAt(iter_ind) != ')' &&
	    str_text.charAt(iter_ind) != '!' &&
	    str_text.charAt(iter_ind) != '?' &&
	    str_text.charAt(iter_ind) != '"' &&
	    str_text.charAt(iter_ind) != '\'')
	{
		if (str_text.toUpperCase().charAt(iter_ind) == str_char || str_text.toLowerCase().charAt(iter_ind) == str_char)
		{
			while (str_text.charAt(iter_ind) != ' ' &&
	   	       	       str_text.charAt(iter_ind) != '.' &&
	    	       	       str_text.charAt(iter_ind) != ',' &&
	    	       	       str_text.charAt(iter_ind) != ':' &&
	    	       	       str_text.charAt(iter_ind) != ';' &&
	    	       	       str_text.charAt(iter_ind) != '-' &&
	    	       	       str_text.charAt(iter_ind) != '(' &&
	    	       	       str_text.charAt(iter_ind) != ')' &&
	    	       	       str_text.charAt(iter_ind) != '!' &&
	    	       	       str_text.charAt(iter_ind) != '?' &&
	   	       	       str_text.charAt(iter_ind) != '"' &&
	    	       	       str_text.charAt(iter_ind) != '\'')
			{
				iter_ind++;
			}
		}
		else
		{
			var word_start = iter_ind; //Индекс первого символа рассматриваемого слова исходного текста.
			var word_len = 0; //Длина рассматриваемого слова исходного текста.
			var flag = false; //Флаг для отметки вхождения заданной буквы в слово НЕ первым символом.
			while (str_text.charAt(iter_ind) != ' ' &&
	   	       	       str_text.charAt(iter_ind) != '.' &&
	    	       	       str_text.charAt(iter_ind) != ',' &&
	    	       	       str_text.charAt(iter_ind) != ':' &&
	    	       	       str_text.charAt(iter_ind) != ';' &&
	    	       	       str_text.charAt(iter_ind) != '-' &&
	    	       	       str_text.charAt(iter_ind) != '(' &&
	    	       	       str_text.charAt(iter_ind) != ')' &&
	    	       	       str_text.charAt(iter_ind) != '!' &&
	    	       	       str_text.charAt(iter_ind) != '?' &&
	   	       	       str_text.charAt(iter_ind) != '"' &&
	    	       	       str_text.charAt(iter_ind) != '\'')
			{
				iter_ind++;
				word_len++;
				if ((str_text.toUpperCase().charAt(iter_ind) == str_char || str_text.toLowerCase().charAt(iter_ind) == str_char) && flag == false)
					flag = true;	
			} 
			if (flag == true)
			{
				word_count++;
				WScript.Echo(word_count + "-ое слово, в которое входит заданная буква \"" + str_char + "\", но она не является первой буквой слова: " + str_text.substr(word_start, word_len)); 
			}
		}
	}
	iter_ind++;
}
WScript.Echo("Количество слов, в которые входит заданная буква \"" + str_char + "\", но она не является первой буквой слова: " + word_count);