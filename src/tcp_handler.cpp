#include <string>
#include <memory>
#include "tcp_handler.h"
#include "tcp_server.h"
#include "tcp_client.h"

Radium::TCPHandler::TCPHandler(uint16_t radiumPort){
  serv = std::make_unique<TCPServer>(radiumPort);
}

void Radium::TCPHandler::handle(){
  while(true) {
    std::string serverIP = "127.0.0.1";

    int clientSocket = Radium::TCPHandler::serv->acceptHandler();
    std::string clientMessage = Radium::TCPHandler::serv->receiveMessage(clientSocket);
    std::unique_ptr<TCPClient> client = std::make_unique<TCPClient>();
    client->connectServer(5000, serverIP.c_str());
    client->sendMessage(clientMessage);
    std::string serverMessage = client->receiveMessage();
    Radium::TCPHandler::serv->sendMessage(clientSocket, serverMessage);
  }
}

// std::unique_ptr<sockaddr_in> Radium::TCPHandler::radiumAddress