#include <exception>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_handler.h"
#define BUF_SIZE 100000

using namespace Radium;

TCPHandler::TCPHandler(uint8_t serverPort){
  TCPHandler::serverAddress.sin_family = AF_INET;
  TCPHandler::serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  TCPHandler::serverAddress.sin_port = htons(serverPort);
  bindSocket();
  
  try {
    listen(TCPHandler::serverSocket, 5);
  }
  catch(std::exception& e) {
    throw std::runtime_error("failed to listen");
  }
}

void TCPHandler::handleClient(){
  struct sockaddr_in clientAddress;
  int clientSocket;
  
  while(true){
    socklen_t clientAddressSize = sizeof(clientAddress);
    try {
      clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    }
    catch(std::exception& e) {
      throw std::runtime_error("failed to accept");
    }

    char buffer[BUF_SIZE];
    int recvMsgSize;
    try {
      recvMsgSize = recv(clientSocket, buffer, sizeof(buffer), 0);
    }
    catch(std::exception& e) {
      throw std::runtime_error("failed to receive from client");
    }

    while(recvMsgSize > 0) {
      handleTCPClient(&buffer[0]);
      handleServer(); // 返答を待ち構える
      sendClient(); // serverAddressを使ってsendClientを実行
    }
  }
}

void TCPHandler::handleServer(){
  
}

void TCPHandler::sendClient(){
  
}

void TCPHandler::sendServer(char* buffer){
  try {
    send(TCPHandler::serverSocket, buffer, strlen(buffer), 0);
  }
  catch(std::exception& e) {
    throw std::runtime_error("failed to send backend");
  }
}

void TCPHandler::rewriteIPAddr(sockaddr_in& clientAddress) {

}

void TCPHandler::handleTCPClient(char* buffer) {
  struct sockaddr_in backendServerAddress;
  backendServerAddress.sin_family = AF_INET;
  backendServerAddress.sin_addr.s_addr = inet_addr("192.168.3.34");
  backendServerAddress.sin_port = htons(3000);

  try {
    connect(TCPHandler::serverSocket, (struct sockaddr *)&(TCPHandler::serverAddress), sizeof(TCPHandler::serverAddress));
  }
  catch(std::exception& e) {
    throw std::runtime_error("Failed to connect to backend server");
  }
  TCPHandler::sendServer(buffer);
  // ここで送り先サーバーを決定し、serverAddressを使ってsendServerを実行
}

void TCPHandler::bindSocket() {
  try {
    TCPHandler::serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  }
  catch(std::exception& e) {
    throw std::runtime_error("Failed to create server socket");
  }

  try {
    bind(TCPHandler::serverSocket, (struct sockaddr *)&(TCPHandler::serverAddress), sizeof(TCPHandler::serverAddress));
  }
  catch(std::exception& e) {
    throw std::runtime_error("Failed to create server socket");
  }
}


// std::unique_ptr<sockaddr_in> Radium::TCPHandler::serverAddress