all:
	g++ -std=c++14 -Wall -Wextra -g -I. main.cpp mongoose.c -o server \
            -lssl -lcrypto -DMG_ENABLE_SSL
