#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_client.h"
#define BUFFER_SIZE 2048

std::string concatMessage(std::vector<std::string>& messages){
  std::string s;
  if (!messages.empty()) {
    for (decltype(messages.size()) i = 0; i < messages.size(); ++i)
      s += messages[i];
  }
  return s;
}

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

void TCPClient::sendMessage(std::string message) {
  uint64_t messageSize = strlen(message.c_str());
  
  if(send(TCPClient::clientSocket, message.c_str(), messageSize, 0) < 0) {
    throw std::runtime_error("failed to send backend");
  }
}

std::string TCPClient::receiveMessage() {
  std::vector<std::string> messages;
  char buffer[BUFFER_SIZE];
  int bytesReceved;

  if((bytesReceved = recv(TCPClient::clientSocket, buffer, sizeof(buffer), 0)) < 0){
    throw std::runtime_error("failed to receive from client");
  }

  while(bytesReceved > 0) {
    messages.emplace_back(buffer);

    if((bytesReceved = recv(TCPClient::clientSocket, buffer, sizeof(buffer), 0)) < 0){
      throw std::runtime_error("failed to receive from client");
    }
  }

  return concatMessage(messages);
}
