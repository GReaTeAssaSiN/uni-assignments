//�������� ������� ��� ������ � Microsoft Excel. 
var xlApp = new ActiveXObject("Excel.Application");

//���  
//var xlApp = WScript.CreateObject(�Excel.Application�);

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������. 
xlApp.Visible = true;

//�������� ������������ ������� ����� (��� Microsoft Excel). 
xlApp.Workbooks.Open("D:\\���\\������������ �������\\������������ ������\\Lab_3\\salary.xlsx");