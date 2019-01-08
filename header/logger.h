
#include <string>
#include <iostream>
#include <ctime>
#include <sys/socket.h>
#include <arpa/inet.h>

void logging(struct sockaddr_in* clientInfo){
  auto setFormat = [](int value){
    return value < 10 ? "0" + std::to_string(value) : std::to_string(value);
  };

  std::time_t t = std::time(0);   // get time now
  std::tm* currentTime = std::localtime(&t);
  std::string ipAddress = inet_ntoa(clientInfo->sin_addr);
  
  std::cout << "[" << (currentTime->tm_year + 1900) << '-' 
            << setFormat(currentTime->tm_mon + 1) << '-'
            << setFormat(currentTime->tm_mday) << ' '
            << setFormat(currentTime->tm_hour) << ':'
            << setFormat(currentTime->tm_min) << ':'
            << setFormat(currentTime->tm_sec) << "] "
            << ipAddress << "\n";
}
