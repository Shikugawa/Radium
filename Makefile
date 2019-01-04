CC = g++
CFLAGS = -std=c++17 -g -Wall -Wextra

build: tcp_handler.cpp tcp_client.o tcp_server.o
	$(CC) $(CFLAGS) -o radium tcp_client.o tcp_server.o tcp_handler.cpp -lncurses

tcp_client.o: tcp_client.cpp
	$(CC) $(CFLAGS) -c tcp_client.cpp

tcp_server.o: tcp_server.cpp
	$(CC) $(CFLAGS) -c tcp_server.cpp

clean:
	$(RM) *.o
