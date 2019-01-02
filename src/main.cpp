#include "tcp_handler.h"

int main(){
  Radium::TCPHandler tcp_handler(3000);
  tcp_handler.handle(); // start
}