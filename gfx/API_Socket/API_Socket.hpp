//
// API_Socket.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun  6 23:37:19 2015 jordan sabbah
// Last update Fri Jun 19 00:06:18 2015 jordan sabbah
//


#ifndef API_SOCKET_HPP_
# define API_SOCKET_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <memory>

enum Mode{
  SERVER,
  CLIENT,
};

class ISocket{
public:
  virtual ~ISocket(){}
  virtual void		Init(int) = 0;
  virtual void		Init(int, const std::string &) = 0;
  virtual ISocket	*Accept() = 0;

  virtual std::size_t	Send(const void *, std::size_t) = 0;
  virtual std::size_t	Receive(void *, std::size_t) = 0;

  virtual int		Poll(std::vector<ISocket *> &, std::vector<ISocket *> &) = 0;
  virtual bool		IsReadable() const = 0;
  virtual bool		IsWritable() const = 0;

  virtual Mode		GetMode() const = 0;
};

# if defined(WIN32) || defined (_WIN32)
  //  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# elif defined(linux) || defined (__unix__)
  //  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# else
  //  do nothing and hope for the best?
# define EXPORT
# define IMPORT
# pragma warning Unknown dynamic link import/export semantics.
# endif

#endif /* !API_SOCKET_HPP_ */
