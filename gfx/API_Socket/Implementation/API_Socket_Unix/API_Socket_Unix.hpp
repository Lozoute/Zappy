//
// API_Socket_Unix.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Socket/Implementation/API_Socket_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun  6 23:51:29 2015 jordan sabbah
// Last update Wed Jul  1 22:23:05 2015 jordan sabbah
//

#ifndef API_SOCKET_UNIX_HPP_
# define API_SOCKET_WINDOWS_HPP_

# include "API_Socket.hpp"
# include "Error.hpp"

class Socket : public ISocket{
private:
  int					_sock;
  bool					_read;
  bool					_write;
  Mode					_mode;


  void					Bigger(int *,
					       const std::vector<Socket *> &,
					       const std::vector<Socket *> &) const;
public:
  Socket();
  Socket(int);
  Socket(const Socket &);
  Socket				&operator=(const Socket &);
  virtual ~Socket();

  virtual void				Init(int);
  virtual void				Init(int, const std::string &);
  virtual ISocket 			*Accept();

  virtual std::size_t			Send(const void *, std::size_t);
  virtual std::size_t			Receive(void *, std::size_t);

  virtual int				Poll(std::vector<ISocket *> &,
					     std::vector<ISocket *> &);

  virtual bool				IsReadable() const;
  virtual bool				IsWritable() const;

  virtual Mode				GetMode() const;
};

# endif /* !API_SOCKET_UNIX_HPP_ */
