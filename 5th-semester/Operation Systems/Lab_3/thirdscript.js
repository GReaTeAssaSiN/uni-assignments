//�������� ������� ��� ������ � Microsoft Word.
var wdApp = new ActiveXObject("Word.Application"); 

//��� 
//var wdApp = WScript.CreateObject(�Word.Application�); 

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������.
wdApp.Visible = true; 

//�������� ������������� �������� ��������� (��� Microsoft Word).
wdApp.Documents.Open("D:\\���\\������������ �������\\������������ ������\\Lab_3\\mydoc.docx");