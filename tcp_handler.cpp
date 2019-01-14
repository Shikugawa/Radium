#include <iostream>
#include <string>
#include <vector>
#include "header/tcp_handler.h"
#include "header/tcp_server.h"
#include "header/tcp_client.h"
#include "header/algorithm.h"
#include "serverip.h"

Radium::TCPHandler::TCPHandler(uint16_t radiumPort) {
  Radium::TCPHandler::radiumPort = radiumPort;
  Radium::TCPHandler::radiumServer = new TCPServer(radiumPort);
}

void Radium::TCPHandler::handle(){
  std::vector<serverIP*> server = {
    new serverIP("127.0.0.1", 5000),
    new serverIP("127.0.0.1", 5001)
  };
  serverIP* selectedAddress;

  while(true) {
    std::string serverIP = "127.0.0.1";
    std::cout << "Connecting..." << std::endl;

    // クライアントからの受付
    int clientSocket = Radium::TCPHandler::radiumServer->acceptHandler();
    std::string clientMessage = Radium::TCPHandler::radiumServer->receiveMessage(clientSocket);
    
    // サーバーへの送信
    selectedAddress = Radium::Algorithm::roundRobin(server);  
    TCPClient* radiumClient = new TCPClient();
    radiumClient->connectServer(selectedAddress->port, selectedAddress->ipaddress.c_str());
    radiumClient->sendMessage(clientMessage);

    // サーバーからの受付
    std::string serverMessage = radiumClient->receiveMessage();

    // クライアントへの送信
    Radium::TCPHandler::radiumServer->sendMessage(clientSocket, clientMessage);
    delete radiumClient;
  }
}

int main() {
  Radium::TCPHandler tcp_handler(5555);
  tcp_handler.handle(); // start
}
