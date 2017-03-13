//
// Protocol.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun  7 17:24:44 2015 jordan sabbah
// Last update Sun Jul  5 20:11:14 2015 jordan sabbah
//

#include <iostream>
#include "API_Socket.hpp"
#include "Protocol.hpp"
#include "ServerCommand.hpp"

Protocol::Protocol(std::string const &host, int port){
  _sock.Init(port, host);
  _overrun = false;
}


Protocol::Protocol(){
  _overrun = false;
}

bool	Protocol::connect(int port, std::string const &host){
  try
    {
      _sock.Init(port, host);
      std::string	bjr("BIENVENUE\n");
      char		*buffer = new char [1024];
      int		len;

      if ((len = _sock.Receive(buffer, 1023)) <= 0)
	throw (Error("can't connect to server", "Protocol::connect(int port, std::string cons t&host)"));
      buffer[len] = 0;
      if (bjr != buffer)
	throw (Error("can't connect to server", "Protocol::connect(int port, std::string cons t&host)"));
      _sock.Send("GRAPHIC\n", 8);
      delete [] buffer;
    }
  catch (Error const &e)
    {
      std::cerr << "invalid connection to server" << std::endl;
      return false;
    }
  return true;
}

Protocol::~Protocol(){
  _buffer.str("");
}

ServerCommand	*Protocol::read_buffer(){
  std::string data;
  std::getline(_buffer, data);
  std::string const &saved = _buffer.str();
  _buffer << saved.substr(data.size() + 1, saved.size() - data.size()- 1);
  _buffer.str(saved.substr(data.size() + 1, saved.size() - data.size()- 1));
  try
    {
      ServerCommand *task = new ServerCommand(data);
      _overrun = (_overrun && _buffer.gcount() > 1023) ? true : false;
      return task;
    }
  catch (Error const &e)
    {
      std::cout << "error = " << std::endl;
    }
  return NULL;
}

ServerCommand	*Protocol::poll(){
  char	*buffer = new char [1024];
  int	len;

  if (_overrun || (_buffer.gcount() > _maxSize && (_overrun = true)))
    return read_buffer();
  while (_buffer.str().find('\n') == std::string::npos)
    {
      if ((len = _sock.Receive(buffer, 1023)) <= 0)
	throw (Error("lost connection to server", "poll()"));
      buffer[len] = 0;
      _buffer << _buffer.str() + buffer;
    }
  delete [] buffer;
  return read_buffer();
}


bool	Protocol::send(ServerCommand *command){
  try
    {
      std::string const &data = command->get_info();
      _sock.Send(data.c_str(), data.size());
    }
  catch (Error const &e)
    {
      std::cerr << "error :" << e.what() << " in " << e.who() << std::endl;
      return false;
    }
  return true;
}
