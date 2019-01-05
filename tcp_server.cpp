#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "header/tcp_server.h"
#define BUFFER_SIZE 2048

std::string concatMessage(std::vector<std::string>& messages);

TCPServer::TCPServer(uint16_t serverPort) {
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(serverPort);

  TCPServer::createSocketBind(&serverAddress);
}

TCPServer::~TCPServer() {
  close(TCPServer::servSocket);
}

int TCPServer::acceptHandler(){
  int clientSocket;
  struct sockaddr_in clientAddress;
  socklen_t clientAddrLength = sizeof(clientAddress);
  if ((clientSocket = accept(TCPServer::servSocket, (struct sockaddr *)&clientAddress, &clientAddrLength)) < 0) {
    throw std::runtime_error("failed to accept");
  }

  return clientSocket;
}

std::string TCPServer::receiveMessage(int clientSocket) {
  std::vector<std::string> messages;
  int recvMessageSize;
  char buffer[BUFFER_SIZE];
  recvMessageSize = recv(clientSocket, buffer, BUFFER_SIZE, 0);

  while(recvMessageSize > 0){
    messages.emplace_back(buffer);

    recvMessageSize = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if(recvMessageSize < 0) {
      throw std::runtime_error("failed to receive from client");
    }
  }

  return [&](){
    std::string s;
    if (!messages.empty()) {
      for (decltype(messages.size()) i = 0; i < messages.size(); ++i)
        s += messages[i];
    }
    return s;
  }();
}

void TCPServer::sendMessage(int clientSocket, std::string message) {
  uint64_t messageSize = strlen(message.c_str());
  
  if(send(clientSocket, message.c_str(), messageSize, 0) < 0) {
    throw std::runtime_error("failed to send backend");
  }
}

void TCPServer::createSocketBind(sockaddr_in* serverAddress) {
  TCPServer::servSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(TCPServer::servSocket < 0) {
    throw std::runtime_error("Failed to create server socket");
  }

  if(bind(TCPServer::servSocket, (struct sockaddr *)serverAddress, sizeof(*serverAddress)) < 0) {
    throw std::runtime_error("Failed to bind");
  }

  if(listen(TCPServer::servSocket, 5) < 0) {
    throw std::runtime_error("failed to listen");
  }
}
