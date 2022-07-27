socket.on("message", (message) => {
    console.log(message);
});

const h1 = document.querySelector("h1");
h1.addEventListener("click", () => {
    socket.emit("new click");
});

socket.on("clicked", (number) => {
    const paragraph = document
        .createElement("p")
        .appendChild(document.createTextNode("Oh my god, you're number " + number));
    document.body.appendChild(paragraph);
    document.body.appendChild(document.createElement("br"));
});

socket.on("new notification", () => {
    const notifications = document.querySelector("#notifications");
    notifications.prepend(
        document
            .createElement("p")
            .appendChild(document.createTextNode("New notification"))
    );
});
