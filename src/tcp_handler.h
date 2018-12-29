#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace Radium {
  class TCPHandler {
  public:
    TCPHandler(){}
    void handleClient(){}
    void handleServer(){}
    void sendServer(){}
    void sendClient(){}
  private:
    std::unique_ptr<sockaddr_in> serverAddress;
    void rewriteIPAddr(sockaddr_in& clientAddress){}
  }; // TCPHandler
} // Radium