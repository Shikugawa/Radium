#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <fstream>
#include "serverip.h"

namespace Radium {
  class Algorithm {
  public:
    static serverIP* roundRobin(const std::vector<serverIP*>& server) {
      std::ifstream ifs("tmp.txt");
      if(!ifs.is_open()) {
        std::ofstream ofs("tmp.txt");
        ofs << 0 << std::endl;
      }
      std::string dest;
      ifs >> dest;
        
      int dest_i = std::atoi(dest.c_str());
      int next = dest_i >= server.size() - 1 ? 0 : ++dest_i;
      std::ofstream ofs("tmp.txt");
      ofs << next;

      return server[next];
    }
  }; // Algorithm
} // Radium