CC = g++
CFLAGS = -std=c++17

build: src/main.cpp tcp_handler.o
	$(CC) $(CFLAGS) -o radium tcp_handler.o src/main.cpp

tcp_handler.o: src/tcp_handler.cpp tcp_client.o tcp_server.o
	$(CC) $(CFLAGS) -c src/tcp_handler.cpp

tcp_client.o: src/tcp_client.cpp
	$(CC) $(CFLAGS) -c src/tcp_client.cpp

tcp_server.o: src/tcp_server.cpp
	$(CC) $(CFLAGS) -c src/tcp_server.cpp

clean:
	$(RM) *.o
	$(RM) radium