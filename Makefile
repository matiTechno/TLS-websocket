all: client
	g++ -std=c++14 -Wall -Wextra -g -I. main.cpp mongoose.c -o server \
            -lssl -lcrypto -DMG_ENABLE_SSL

.PHONY: client
client:
	g++ -std=c++14 -Wall -Wextra -g -I. client.cpp mongoose.c -o client \
            -lssl -lcrypto -DMG_ENABLE_SSL
