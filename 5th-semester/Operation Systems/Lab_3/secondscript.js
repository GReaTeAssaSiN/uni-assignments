//�������� ������� ��� ������ � Microsoft Word.
var wdApp = new ActiveXObject("Word.Application"); 

//��� 
//var wdApp = WScript.CreateObject(�Word.Application�); 

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������.
wdApp.Visible = true; 

//���������� ������, ������� ��������� � ��������� �������� ���������� � ������� ������ Add.
//expression.Add(Template, NewTemplate, DocumentType, Visible);
wdApp.Documents.Add();
