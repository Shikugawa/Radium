#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_server.h"
#include "tcp_client.h"

namespace Radium {
  class TCPHandler {
  public:
    uint16_t radiumPort;
    TCPHandler(uint16_t radiumPort); 
    void handle();
  private:
    TCPServer* radiumServer;
    
  }; // TCPHandler
} // Radium