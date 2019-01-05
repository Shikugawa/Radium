#include <iostream>
#include <string>
#include <memory>
#include "header/tcp_handler.h"
#include "header/tcp_server.h"
#include "header/tcp_client.h"

Radium::TCPHandler::TCPHandler(uint16_t radiumPort){
  serv = std::make_unique<TCPServer>(radiumPort);
}

void Radium::TCPHandler::handle(){
  while(true) {
    std::string serverIP = "127.0.0.1";

    int clientSocket = Radium::TCPHandler::serv->acceptHandler();
    std::cout << clientSocket << std::endl;
    std::string clientMessage = Radium::TCPHandler::serv->receiveMessage(clientSocket);
    std::unique_ptr<TCPClient> client = std::make_unique<TCPClient>();
    client->connectServer(5000, serverIP.c_str());
    client->sendMessage(clientMessage);
    std::string serverMessage = client->receiveMessage();
    Radium::TCPHandler::serv->sendMessage(clientSocket, serverMessage);
  }
}

int main() {
  Radium::TCPHandler tcp_handler(5555);
  tcp_handler.handle(); // start
}
