const express = require("express");
const http = require("http");
const { Server } = require("socket.io");

const app = express();

app.set("view engine", "pug");

const server = http.createServer(app);
const io = new Server(server);

app.get("/", (req, res) => {
    res.render("index");
});

app.get("/chat.js", (req, res) => {
    res.sendFile(__dirname + "/chat.js");
});

io.on("connection", (socket) => {
    console.log("A user is connected");

    socket.on("disconnect", () => {
        console.log("A user is disconnected");
    });

    socket.on("chat message", (message) => {
        io.emit("chat message", message);
    });
});

server.listen(3000, () => {
    console.log("Listening on port 3000");
});
