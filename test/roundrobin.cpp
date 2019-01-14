#include <iostream>
#include <array>
#include <fstream>
#include <cstdlib>

int main(void) {
  std::array<char*, 2> ipaddress = {
    "192.168.0.1:3000",
    "192.168.0.1:3001"
  };

  while(true){
    std::ifstream ifs("tmp.txt");
    if(!ifs.is_open()) {
      std::ofstream ofs("tmp.txt");
      ofs << 0 << std::endl;
    }
    std::string dest;
    ifs >> dest;
    
    int dest_i = std::atoi(dest.c_str());
    int next = dest_i >= ipaddress.size() - 1 ? 0 : ++dest_i;
    std::cout << next << std::endl;
    std::ofstream ofs("tmp.txt");
    ofs << next;
  }
}