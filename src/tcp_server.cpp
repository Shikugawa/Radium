#include <string>
#include <vector>
#include <ofstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_server.h"
#define BUFFER_SIZE 2048

std::string concatMessage(std::vector<std::string>& messages){
  std::string s;
  if (!messages.empty()) {
    for (decltype(messages.size()) i = 0; i < messages.size(); ++i)
      s += messages[i];
  }
  return s;
}

TCPServer::TCPServer(uint16_t serverPort) {
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(serverPort);
  TCPServer::createSocketBind(&serverAddress);
}

TCPServer::~TCPServer() {
  close(TCPServer::socket);
}

int accept(){
  int clientSocket;
  struct sockaddr_in clientAddress;

  if (clientSocket = accept(TCPServer::socket, (struct sockaddr *)&clientAddress, &(sizeof(clientAddress))) < 0) {
    throw std::runtime_error("failed to accept");
  }

  return clientSocket;
}

std::string TCPServer::receiveMessage(int clientSocket) {
  std::vector<std::string> messages;
  uint64_t recvMessageSize;
  char buffer[BUFFER_SIZE];
  recvMessageSize = recv(clientSocket, buffer, BUFFER_SIZE);

  while(recvMessageSize > 0){
    if(recvMsgSize = recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
      throw std::runtime_error("failed to receive from client");
    }
    messages.emplace_back(buffer);
  }

  return messages;
}

void TCPServer::sendMessage(int clientSocket, std::string message) {
  uint64_t messageSize = Strlen(static_cast<char*>(message));
  
  if(send(clientSocket, message, messageSize, 0) < 0) {
    throw std::runtime_error("failed to send backend");
  }
}

void TCPServer::createSocketBind(sockaddr_in* serverAddress) {
  if(TCPServer::socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) < 0) {
    throw std::runtime_error("Failed to create server socket");
  }

  if(bind(TCPServer::socket, (struct sockaddr *)serverAddress, sizeof(*serverAddress)) < 0) {
    throw std::runtime_error("Failed to create server socket");
  }

  if(listen(*serverAddress, 5) < 0) {
    throw std::runtime_error("failed to listen");
  }
}
