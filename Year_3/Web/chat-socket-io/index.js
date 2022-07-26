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

app.use(express.static("assets"));

app.get("*", (req, res) => {
    res.render("404");
});

const users = {};

io.on("connection", (socket) => {
    console.log("A user is connected: " + socket.id);
    io.to(socket.id).emit("set user", socket.id);
    users[socket.id] = socket.id;

    socket.on("disconnect", () => {
        console.log("A user is disconnected");
    });

    socket.on("chat message", (message) => {
        socket.broadcast.emit("chat message", message);
    });

    socket.on("handle error", (msg) => {
        io.emit("handle error", msg);
    });

    socket.on("set user", (username) => {
        users[socket.id] = username;
        io.to(socket.id).emit("set user", username);
    });
});

server.listen(3000, () => {
    console.log("Listening on port 3000");
});
