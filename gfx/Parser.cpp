//
// Parser.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jul  4 01:26:43 2015 jordan sabbah
// Last update Sat Jul  4 01:57:11 2015 jordan sabbah
//

#include "Parser.hpp"
#include <sstream>
#include "Error.hpp"
#include <iostream>

Parser::Parser(int ac, char **av){
  for (int i = 0; i < ac; ++i){
    _args.push_back(av[i]);
  }
}

Parser::~Parser(){
  _args.clear();
}

int	Parser::get_port(){
  for (std::vector<std::string>::iterator it = _args.begin();
       it != _args.end(); ++it)
    {
      if ((*it) == "-p" && it + 1 != _args.end()){
	std::istringstream iss(*(it + 1));
	iss >> _port;
	if (iss.fail())
	  throw Error("port must be a number", "get_port");
	return _port;
      }
    }
  throw Error("./zappy-gfx -p port [-h host]", "void Parser::find_port()");
  return _port;
}

std::string const 	&Parser::get_host(){
  for (std::vector<std::string>::iterator it = _args.begin();
       it != _args.end(); ++it)
    {
      if ((*it) == "-h" && it + 1 != _args.end()){
	std::istringstream iss(*(it + 1));
	iss >> _host;
	if (iss.fail())
	  throw Error("host must be a vaild string", "get_host");
	return _host;
      }
    }
  _host = "127.0.0.1";
  return _host;
}
