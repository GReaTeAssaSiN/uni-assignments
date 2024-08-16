//—оздание объекта дл€ работы с Microsoft Excel. 
var xlApp = new ActiveXObject("Excel.Application");

//или  
//var xlApp = WScript.CreateObject(УExcel.ApplicationФ);

//”становка свойства Visible созданного объекта в True, чтобы приложение стало видимым. 
xlApp.Visible = true;

//—оздание новой рабочей книги в Excel с помощью метода Add.
//expression.Add(Template);
xlApp.Workbooks.Add();