//—оздание объекта дл€ работы с Microsoft Excel. 
var xlApp = new ActiveXObject("Excel.Application");

//или  
//var xlApp = WScript.CreateObject(УExcel.ApplicationФ);

//”становка свойства Visible созданного объекта в True, чтобы приложение стало видимым. 
xlApp.Visible = true;

//ќткрытие существующей рабочей книги (дл€ Microsoft Excel). 
xlApp.Workbooks.Open("D:\\ ј»\\ќперационные системы\\Ћабораторные работы\\Lab_3\\salary.xlsx");