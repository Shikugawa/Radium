#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "header/tcp_client.h"
#define BUFFER_SIZE 32

TCPClient::TCPClient() {
  TCPClient::clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(TCPClient::clientSocket < 0) {
    throw std::runtime_error("Failed to create server socket");
  }
}

TCPClient::~TCPClient() {
  close(TCPClient::clientSocket);
}

void TCPClient::connectServer(uint16_t serverPort, const char* serverIP) {
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr(serverIP);
  serverAddress.sin_port = htons(serverPort);

  if(connect(TCPClient::clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
    throw std::runtime_error("Failed to connect to backend server");
  }
}

std::string TCPClient::receiveMessage() {
  std::vector<std::string> messages;
  int recvMessageSize;
  char buffer[BUFFER_SIZE];
  
  do {
    recvMessageSize = recv(TCPClient::clientSocket, buffer, BUFFER_SIZE, 0);
    if(recvMessageSize < 0) {
      throw std::runtime_error("failed to receive from client");
    }
    messages.emplace_back(buffer);
  } while(recvMessageSize - BUFFER_SIZE > 0);
  
  memset(buffer, 0, BUFFER_SIZE);
  
  return [&](){
    std::string s;
    if (!messages.empty()) {
      for (decltype(messages.size()) i = 0; i < messages.size(); ++i)
        s += messages[i];
    }
    return s;
  }();
}

void TCPClient::sendMessage(std::string message) {
  uint64_t messageSize = strlen(message.c_str());
  
  if(send(TCPClient::clientSocket, message.c_str(), messageSize, 0) < 0) {
    throw std::runtime_error("failed to send backend");
  }
}
