//—оздание объекта дл€ работы с Microsoft Word.
var wdApp = new ActiveXObject("Word.Application"); 

//или 
//var wdApp = WScript.CreateObject(УWord.ApplicationФ); 

//”становка свойства Visible созданного объекта в True, чтобы приложение стало видимым.
wdApp.Visible = true; 

//ќткрытие существующего рабочего документа (дл€ Microsoft Word).
wdApp.Documents.Open("D:\\ ј»\\ќперационные системы\\Ћабораторные работы\\Lab_3\\mydoc.docx");