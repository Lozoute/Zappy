#ifndef API_SOCKET_WINDOWS_HPP_
# define API_SOCKET_WINDOWS_HPP_

# include <algorithm>
# include <Winsock2.h>
# include "API_Socket.hpp"
# include "Error.hpp"

class Socket : public ISocket
{
  WSADATA				_wsaData;
  SOCKET				_sock;
  bool					_read;
  bool					_write;
  Mode					_mode;

public:
  Socket();
  Socket(SOCKET);
  Socket(const Socket &);
  Socket &operator=(const Socket &);
  virtual ~Socket();

  virtual void				Init(int);
  virtual void				Init(int, const std::string &);
  virtual ISocket			*Accept();

  virtual std::size_t			Send(const void *, std::size_t);
  virtual std::size_t			Receive(void *, std::size_t);

  virtual int				Poll(std::vector<ISocket *> &, std::vector<ISocket *> &);
  virtual bool				IsReadable() const;
  virtual bool				IsWritable() const;

  virtual Mode				GetMode() const;
};

# endif /* !API_SOCKET_WINDOWS_HPP_ */
