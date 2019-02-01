1) create a private key and a certificate request;

see ../authority-crypt/readme.txt for explanation of command line options;
in interactive mode (opened by this command) I set the organization name to
matiTechno-webserver-org and Common Name to localhost, other fields left blank


openssl req -newkey rsa:4096 -keyout server.key -nodes -out server.crt.request


2) create a certificate signed by CA


openssl x509 -req -in server.crt.request -CA ../authority-crypt/auth.crt \
-CAkey ../authority-crypt/auth.key -CAcreateserial -out server.crt


x509              - sign certificate
-req              - certificate request is expected on input instead of certificate
-in               - certificate request filename
-CA               - certificate used for signing
-CAkey            - corresponding private key
-CAcreateserial   - create a file with a serial number if not present (serial number
                        is required to sign a certificate
-out              - filename of a created certificate
