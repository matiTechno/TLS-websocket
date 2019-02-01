openssl req -x509 -newkey rsa:4096 -nodes -keyout auth.key -out auth.crt -days 1000

in the interactive mode (started by the above command)
I set the organization name to matiTechno-CA-org and rest of the fields left blank
(you have to enter '.' to not use a default value if present)

req                   - create certificate / certificate request
-x509                 - create self signed certificate
-newkey rsa:4096      - create new private key
-nodes                - don't encrypt private key
-keyout               - filename to write private key
-out                  - filename to write certificate
-days                 - numbers of days the certificate is valid

add auth.crt to your browser CA (certificate authority) list
use auth.key to sign a certificate request (see ../server-crypt/readme.txt)

auth.srl contains a serial number used to sign the server certificate request
(this file was generated automatically)
