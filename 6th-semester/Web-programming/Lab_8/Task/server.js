const mongoose = require("mongoose");
const express = require("express");
const Schema = mongoose.Schema;
const app = express();
app.use(express.static("client"));
app.use(express.json());

const manufacturerScheme = new Schema({ manufacturer: String, respPersonFullName: String, toolName: String, issueDate: String }, { versionKey: false });
const Manufacture = mongoose.model("Manufacture", manufacturerScheme);
async function main() {
    try {
        await mongoose.connect("mongodb://127.0.0.1:27017/manufacturedb");
        app.listen(3000);
        console.log("Сервер ожидает подключения...");
    }
    catch (err) {
        return console.log(err);
    }
}

app.get("/api/manufactures", async (req, res) => {
    const manufactures = await Manufacture.find({});
    res.send(manufactures);
});
app.get("/api/manufactures/:id", async (req, res) => {
    const id = req.params.id;
    const manufacture = await Manufacture.findById(id);
    if (manufacture) res.send(manufacture);
    else res.sendStatus(404);
});
app.post("/api/manufactures", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const manufacturer = req.body.manufacturer;
    const respPersonFullName = req.body.respPersonFullName;
    const toolName = req.body.toolName;
    const issueDate = req.body.issueDate;
    const manufacture = new Manufacture({ manufacturer: manufacturer, respPersonFullName: respPersonFullName, toolName: toolName, issueDate: issueDate });
    await manufacture.save();
    res.send(manufacture);
});
app.delete("/api/manufactures/:id", async (req, res) => {
    const id = req.params.id;
    const manufacture = await Manufacture.findByIdAndDelete(id);
    if (manufacture) res.send(manufacture);
    else res.sendStatus(404);
});
app.put("/api/manufactures/:id", async (req, res) => {
    if (!req.body) return res.sendStatus(400);
    const id = req.params.id;
    const manufacturer = req.body.manufacturer;
    const respPersonFullName = req.body.respPersonFullName;
    const toolName = req.body.toolName;
    const issueDate = req.body.issueDate;
    const newManufacture = { manufacturer: manufacturer, respPersonFullName: respPersonFullName, toolName: toolName, issueDate: issueDate };
    const manufacture = await Manufacture.findOneAndUpdate({ _id: id }, newManufacture, { new: true });
    if (manufacture) res.send(manufacture);
    else res.sendStatus(404);
});
main();
// прослушиваем прерывание работы программы (ctrl-c)
process.on("SIGINT", async () => {
    await mongoose.disconnect();
    console.log("Приложение завершило работу");
    process.exit();
});