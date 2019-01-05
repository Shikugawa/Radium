#pragma once
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class TCPServer {
public:
  TCPServer(uint16_t serverPort);
  ~TCPServer();
  int acceptHandler();
  std::string receiveMessage(int clientSocket);
  void sendMessage(int clientSocket, std::string message);
private:
  int servSocket;
  void createSocketBind(sockaddr_in* serverAddress);
  // void createSocketBind(sockaddr_in* serverAddress);
};