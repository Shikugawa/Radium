#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>
#include <unistd.h>
#include "header/tcp_handler.h"
#include "header/tcp_server.h"
#include "header/tcp_client.h"
#include "header/algorithm.h"
#include "header/setting.h"
#define BUFFER_SIZE 2048

Radium::TCPHandler::TCPHandler(uint16_t radiumPort) {
  Radium::TCPHandler::radiumPort = radiumPort;
  Radium::TCPHandler::server = getSettings();
  Radium::TCPHandler::radiumServer = new TCPServer(Radium::TCPHandler::radiumPort);
}

void Radium::TCPHandler::handleChild() {
  Radium::TCPHandler::clientSocket = Radium::TCPHandler::radiumServer->acceptHandler();
  std::string clientMessage = Radium::TCPHandler::radiumServer->receiveMessage(clientSocket);
  std::thread thd(&Radium::TCPHandler::handleMaster, this, std::ref(clientMessage));
  thd.detach();
}

void Radium::TCPHandler::handleMaster(std::string& clientMessage) {
  serverIP* selectedAddress = Radium::Algorithm::roundRobin(Radium::TCPHandler::server);  
  TCPClient* radiumClient = new TCPClient();
  radiumClient->connectServer(selectedAddress->port, selectedAddress->ipaddress.c_str());
  radiumClient->sendMessage(clientMessage);
  std::string serverMessage = radiumClient->receiveMessage();
  Radium::TCPHandler::radiumServer->sendMessage(Radium::TCPHandler::clientSocket, clientMessage);
  
  delete radiumClient;
}

int main() {
  Radium::TCPHandler tcp_handler(5555);
  std::cout << "Radium is listening on " << tcp_handler.radiumPort << std::endl;

  while(true) {
    tcp_handler.handleChild();
  }
}
