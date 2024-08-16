var express = require("express"),
    http = require("http"),
    app = express(),
    manufactures = [
        {
            "toolName": "Электрическая дрель Bosch 18V",
            "respPersonFullName": "Иванов Алексей Петрович",
            "issueDate": "2024-05-15",
            "manufacturers": ["Bosch", "Stanley"]
        },
        {
            "toolName": "Отвертка Phillips Craftsman",
            "respPersonFullName": "Петрова Ольга Николаевна",
            "issueDate": "2024-05-10",
            "manufacturers": ["Craftsman", "Bosch"]
        },
        {
            "toolName": "Молоток Stanley 16 унций",
            "respPersonFullName": "Сидоров Евгений Иванович",
            "issueDate": "2024-05-05",
            "manufacturers": ["Stanley", "Makita"]
        },
        {
            "toolName": "Нож Stanley FatMax",
            "respPersonFullName": "Козлов Дмитрий Андреевич",
            "issueDate": "2024-05-03",
            "manufacturers": ["Stanley", "Dewalt"]
        },
        {
            "toolName": "Электролобзик Dewalt",
            "respPersonFullName": "Смирнова Екатерина Сергеевна",
            "issueDate": "2024-04-28",
            "manufacturers": ["Dewalt", "Makita"]
        },
        {
            "toolName": "Шуруповёрт Makita 12V",
            "respPersonFullName": "Иванов Алексей Петрович",
            "issueDate": "2024-04-20",
            "manufacturers": ["Makita", "Craftsman"]
        }
    ]

app.use(express.static(__dirname + "/client"));
http.createServer(app).listen(3000);
app.get("/manufactures.json", function (req, res) {
    res.json(manufactures);
});

app.use(express.urlencoded({ extended: true }));
app.post("/manufactures", function (req, res) {
    console.log("Данные были отправлены на сервер!");
    var newManufacture = req.body;
    console.log(newManufacture);
    manufactures.push(newManufacture);
    res.json({ "message": "Вы размещаетесь на сервере!" });
});