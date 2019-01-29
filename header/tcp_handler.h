#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_server.h"
#include "tcp_client.h"
#include "serverip.h"

namespace Radium {
  class TCPHandler {
  public:
    uint16_t radiumPort;
    int clientSocket;
    std::vector<serverIP*> server;

    TCPHandler(uint16_t radiumPort); 
    void handleMaster(std::string& clientMessage);
    void handleChild();
  private:
    TCPServer* radiumServer;
  }; // TCPHandler
} // Radium