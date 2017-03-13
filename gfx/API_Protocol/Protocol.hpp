//
// Protocol.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 20 16:33:34 2015 jordan sabbah
// Last update Sun Jul  5 20:03:32 2015 jordan sabbah
//

#ifndef PROTOCOL_HPP_
# define PROTOCOL_HPP_

# include <sstream>
# include "IProtocol.hpp"
# include "API_Socket_Unix.cpp"

class Protocol : public IProtocol{
private:
  int			const			_maxSize = 10000;
  Socket					_sock;
  std::stringstream				_buffer;
  bool						_overrun;
  ServerCommand					*read_buffer();
public:
  Protocol(std::string const &, int);
  Protocol();
  virtual ~Protocol();
  virtual bool					connect(int, std::string const &);
  virtual ServerCommand				*poll();
  virtual bool					send(ServerCommand *);
};

#endif // !PROTOCOL_HPP_
