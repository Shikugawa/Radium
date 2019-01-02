#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tcp_server.h"
#include "tcp_client.h"

namespace Radium {
  class TCPHandler {
  public:
    TCPHandler(uint16_t radiumPort){}
    ~TCPHandler(){}
    void handle(){}
  private:
    std::unique_ptr<TCPServer> serv;
  }; // TCPHandler
} // Radium