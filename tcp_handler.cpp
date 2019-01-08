#include <iostream>
#include <string>
#include "header/tcp_handler.h"
#include "header/tcp_server.h"
#include "header/tcp_client.h"

Radium::TCPHandler::TCPHandler(uint16_t radiumPort) {
  Radium::TCPHandler::radiumPort = radiumPort;
  Radium::TCPHandler::radiumServer = new TCPServer(radiumPort);
}

void Radium::TCPHandler::handle(){
  while(true) {
    std::string serverIP = "127.0.0.1";
    std::cout << "Connecting..." << std::endl;

    // クライアントからの受付
    int clientSocket = Radium::TCPHandler::radiumServer->acceptHandler();
    std::string clientMessage = Radium::TCPHandler::radiumServer->receiveMessage(clientSocket);
    
    // サーバーへの送信
    TCPClient* radiumClient = new TCPClient();
    radiumClient->connectServer(5000, serverIP.c_str());
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
