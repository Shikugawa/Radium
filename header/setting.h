#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <picojson/picojson.h>
#include "header/serverip.h"

std::vector<serverIP*> getSettings(){
  std::ifstream ifs("settings.json");
  if (ifs.fail()) {
    throw std::runtime_error("failed to read setting file");
  }
  
  const std::string dest((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  ifs.close();
  picojson::value v;
  const std::string err = picojson::parse(v, dest);
  if (err.empty() == false) {
    throw std::runtime_error(err);
  }

  picojson::object& obj = v.get<picojson::object>();
  picojson::array& servers = obj["servers"].get<picojson::array>();
  std::vector<serverIP*> server;

  for(auto& serv: servers){
    picojson::object& obj2 = serv.get<picojson::object>();
    server.emplace_back(new serverIP(
      obj2["host"].get<std::string>(),
      std::stoi(obj2["port"].get<std::string>())
    ));
  }
  
  return server;
}
