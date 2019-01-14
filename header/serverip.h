#pragma once
#include <string>

class serverIP {
public:
  std::string ipaddress;
  uint16_t port;
  serverIP(std::string _i, uint16_t _p) : ipaddress(_i), port(_p) {}
};