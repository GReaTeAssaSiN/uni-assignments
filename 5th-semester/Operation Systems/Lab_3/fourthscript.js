//�������� ������� ��� ������ � Microsoft Excel. 
var xlApp = new ActiveXObject("Excel.Application");

//���  
//var xlApp = WScript.CreateObject(�Excel.Application�);

//��������� �������� Visible ���������� ������� � True, ����� ���������� ����� �������. 
xlApp.Visible = true;

//�������� ����� ������� ����� � Excel � ������� ������ Add.
//expression.Add(Template);
xlApp.Workbooks.Add();