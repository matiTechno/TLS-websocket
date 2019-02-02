# TLS-websocket
additional readmes are located in server-crypt and authority-crypt directories  
they describe how to generate and sign certificates with openssl

#### goals of the project
* build a WebSocket server and communicate with both a web browser and a custom client
* learn about TLS / SSL / https / certificates (high-level view)
* enable https in a browser by adding a certificate (authority-crypt/auth.crt) to a CA list
* embed a web server in a source code
* validate with Wireshark if the communication is encrypted (yep, TLS v1.3)

main.cpp - websocket server  
client.cpp - websocket client
```
make
./server &
./client
```
connect from a web browser - https://localhost:1234  
I've only tested firefox - it shows green padlock (indication of a secure connection).

#### problems
* I could not make mongoose client verify a server CN (common name) and fail - it always succeeds

#### useful resources
* https://letsencrypt.org/how-it-works/
* https://gist.github.com/Soarez/9688998
