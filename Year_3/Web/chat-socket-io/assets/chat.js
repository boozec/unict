var form = document.getElementById("form");
var input = document.getElementById("input");
const messages = document.getElementById("messages");

form.addEventListener("submit", function(e) {
    e.preventDefault();
    let value = input.value;
    if (value) {
        if (value[0] == "/") {
            let command = value.split(" ");
            if (command.length == 2 && command[0] == "/user") {
                socket.emit("set user", command[1]);
            } else {
                socket.emit("handle error", "Command not found");
            }
        } else {
            socket.emit("chat message", value);
        }
        input.value = "";
    }
});
socket.on("chat message", (msg) => {
    var item = document.createElement("li");
    item.textContent = msg;
    messages.appendChild(item);
    window.scrollTo(0, document.body.scrollHeight);
});

socket.on("handle error", (msg) => {
    alert(msg);
});

socket.on("set user", (username) => {
    const userBox = document.getElementById("userBox");
    userBox.innerHTML = username;
    alert("Username changed");
});
