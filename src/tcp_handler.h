#include <sys/socket.h>
#include <arpa/inet.h>

namespace Radium {
  class TCPHandler {
  public:
    TCPHandler(uint8_t serverPort){}
    void handleClient(){}
    void handleServer(){}
    void sendServer(char* buffer){}
    void sendClient(){}
  private:
    struct sockaddr_in serverAddress;
    int serverSocket;
    void bindSocket(){};
    void handleTCPClient(char* buffer);
    void rewriteIPAddr(sockaddr_in& clientAddress){}
  }; // TCPHandler
} // Radium