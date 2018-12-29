#include "tcp_handler.h"
#include "algorithm.h"

int main(){
  Radium::TCPHandler* tcp_handler(new Radium::TCPHandler());
  tcp_handler->handleClient();
  delete tcp_handler;
}