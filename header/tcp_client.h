#pragma once
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class TCPClient {
public:
  TCPClient();
  ~TCPClient();
  void connectServer(uint16_t serverPort, const char* serverIP);
  void sendMessage(std::string message);
  std::string receiveMessage();
private:
  int clientSocket;
};