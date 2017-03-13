//
// IProtocol.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Mon Jun 22 14:46:24 2015 jordan sabbah
// Last update Sat Jul  4 14:49:49 2015 jordan sabbah
//

#ifndef IPROTOCOL_HPP_
# define IPROTOCOL_HPP_

# include "IServerCommand.hpp"
# include "Error.hpp"
# include <memory>
# include <string>

class ServerCommand;

class IProtocol {
public:
  virtual ~IProtocol(){}
  virtual bool					connect(int, std::string const &) = 0;
  virtual ServerCommand				*poll() = 0;
  virtual bool					send(ServerCommand *) = 0;
};

# endif // !IPROTOCOL_HPP_
