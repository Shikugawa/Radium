#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class TCPServer {
public:
  TCPServer(uint8_t serverPort){}
  ~TCPServer(){}
  int accept(){}
  std::string receiveMessage(int clientSocket){}
  void sendMessage(int clientSocket, std::string message){}
private:
  int socket;
  void createSocketBind(sockaddr_in* serverAddress){}
};