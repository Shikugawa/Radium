#include "tcp_handler.h"
#include "algorithm.h"
#include <string>

int main(){
  Radium::TCPHandler* tcp_handler(new Radium::TCPHandler());

  while(true){
    tcp_handler->handleClient();
  }
  
  delete tcp_handler;
}