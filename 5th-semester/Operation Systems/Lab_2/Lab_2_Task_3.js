//������������� ���������� ������� String ��� ������� ��������� ������.
var str_text = new String(["������ �� ����� ������ � ���, ���� � ���� ���. ������� � ��� , ��� �� �������� � ���, ��� ����."]);
WScript.Echo("�������� �����: " + str_text);
//����������.
var str_char = '�'; //��������� ������� - �������� ������.
var iter_ind = 0; //���������� ��� ��������� �� ��������� ������.
var word_count = 0; //���������� ���������� ���� �� ������� ������.

//�������� �� ��������� ������.
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
			var word_start = iter_ind; //������ ������� ������� ���������������� ����� ��������� ������.
			var word_len = 0; //����� ���������������� ����� ��������� ������.
			var flag = false; //���� ��� ������� ��������� �������� ����� � ����� �� ������ ��������.
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
				WScript.Echo(word_count + "-�� �����, � ������� ������ �������� ����� \"" + str_char + "\", �� ��� �� �������� ������ ������ �����: " + str_text.substr(word_start, word_len)); 
			}
		}
	}
	iter_ind++;
}
WScript.Echo("���������� ����, � ������� ������ �������� ����� \"" + str_char + "\", �� ��� �� �������� ������ ������ �����: " + word_count);