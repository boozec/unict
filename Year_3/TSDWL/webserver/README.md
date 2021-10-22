# Installazione

Scaricare la tarball:
```
http://git.dcariotti.me/unict/plain/Year_3/TSDWL/webserver/webserver.tar.xz
tar -J -xvf webserver.tar.xz
```

(facoltativo) Creare una cartella per i file del server

Farne la build
```
cmake .
./server
```

Alternativamente a tutto ciò si può scaricare la cartella presente in 
```
http://git.dcariotti.me/unict/tree/Year_3/TSDWL/webserver
```
e farne la build. Ma meglio non scaricare tutti i file presenti sulla repo visto
che non c'entrano né col corso, né con l'esercizio.

# Avvio
Il file `./server` può essere eseguito come
```
./server <port> [root]
```
dove la `<port>` è obbligatoria, mentre la cartella `[root]`, ovvero quella
specificata prima dove saranno i file e che il server andrà ad interrogare, sarà
facoltativa. Di default andrà a cercare dentro una cartella `www` presente nella
cartella corrente.

# Test
Aprire una connessione con `telnet` come
```
telnet <ip> <port>
```

Eseguira una chiamata GET come
```
GET / HTTP/2
[...]


```
Tutti gli altri headers saranno ignorati. Al secondo invio verrà cercato il file
all'interno del server. La path e la versione di HTTP sono chiaramente variabili.

Il responso è completo nel caso di stato 200 o 206, per tutti gli altri sarà una
riga con risposta 404 o 405.

Attualmente il `Content-type` è staticamente a `text/txt`.

Il test può essere fatto anche con client come Insomnia o cURL:
```
curl <ip>:<port>/<path>
```

# Nota
Quando si passa come path la "/" si farà una ricerca al file `index.html`.

---

I numerosi commenti `TODO` e `FIXME` saranno sistemati in seguito.
