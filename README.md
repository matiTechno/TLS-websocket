# TLS-websocket
additional readmes are located in server-crypt and authority-crypt directories  
they describe how to generate and sign certificates with openssl

#### goals of the project
* build a WebSocket server and communicate with both a web browser and a custom client
* learn about TLS / SSL / https / certificates (high-level view)
* enable https in a browser by adding a certificate (authority-crypt/auth.crt) to a CA list
* enable encrypted connection with a browser by adding server's self-signed certificate as an security exception
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
* I could not make mongoose client verify a server's CN (common name) and fail - it always succeeds

#### useful resources
* https://letsencrypt.org/how-it-works/
* https://gist.github.com/Soarez/9688998
* https://stackoverflow.com/questions/6241991/how-exactly-https-ssl-works (second answer)
* https://stackoverflow.com/questions/589622/how-does-a-root-ca-verify-a-signature
* https://en.wikipedia.org/wiki/X.509

#### my take on explaining https

but first - keys:  
https://en.wikipedia.org/wiki/Public-key_cryptography  
Keys are created in pairs - private and public.  
public key - encrypts data; validates a signature created by a private key  
private key - decrypts data encrytped with a public key; creates signatures  
Private key must be kept secure - known only by the owner, public key can be shared with anyone.
Signatures are used to verify the authenticity of a file (https://en.wikipedia.org/wiki/Digital_signature).

Certificate - file that contains a public key, signature and information about the owner.

Each browser ships with a list of certificates of CAs (e.g. https://letsencrypt.org).
These are used to verify a web servers authenticity.  
When a web browser initiates a connection with a server, the server sends its certificate signed by one of CAs
(signed by CA means that the certificate contains a signature created with a CA private key). The browser validates a
certificate signature with a corresponding CA public key. It also checks if a CN (common name) of the certificate
is the same as the address of the web server. If everything is ok - secure connection is established.

If a web server wants its certificate signed it issues a CSR (certificate signing request) to a chosen CA. It must then
prove that it owns a domain specified in CSR. If everything is ok it receives a signed certificate.  
Important thing to realize is that a web browser trusts CAs to sign only valid requests.
