const express = require("express");

const app = express();

app.use(express.urlencoded({ extended: false }));
app.use(express.json());

app.get("/", (req, res) => {
    res.json({ result: 0 });
});

app.post("/calculate", (req, res) => {
    const { value1, value2 } = req.body;

    res
        .status(200)
        .json({
            param1: Number(value1),
            param2: Number(value2),
            result: Number(value1) + Number(value2),
        });
});

app.listen(3000);
