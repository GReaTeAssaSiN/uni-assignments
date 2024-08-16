//—оздание объекта дл€ работы с Microsoft Word.
var wdApp = new ActiveXObject("Word.Application"); 

//или 
//var wdApp = WScript.CreateObject(УWord.ApplicationФ); 

//”становка свойства Visible созданного объекта в True, чтобы приложение стало видимым.
wdApp.Visible = true; 

//ƒобавление нового, пустого документа к коллекции открытых документов с помощью метода Add.
//expression.Add(Template, NewTemplate, DocumentType, Visible);
wdApp.Documents.Add();
