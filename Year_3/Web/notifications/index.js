const http = require("http");
const express = require("express");
const { Server } = require("socket.io");
const path = require("path");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.set("view engine", "pug");
app.set("views", path.join(__dirname, "views"));
app.use(express.static("assets"));
app.use((req, res, next) => {
    console.log(`${req.method} ${req.path}`);
    next();
});

var click = 0;

io.on("connection", (socket) => {
    console.log(socket.id);

    io.to(socket.id).emit("message", "hello man, ur now connected");
    socket.emit("message", "there s another user here!");

    socket.on("disconnect", () => {
        console.log("bye, sir");
    });

    socket.on("new click", () => {
        io.to(socket.id).emit("clicked", ++click);
    });

    setInterval(() => {
        io.to(socket.id).emit("new notification");
    }, 1000);
});

app.get("/", (req, res) => {
    ctx = {
        id: 1,
    };
    res.render("index", ctx);
});

server.listen(3000);
