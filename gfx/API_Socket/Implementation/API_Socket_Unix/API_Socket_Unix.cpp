//
// API_Socket_Unix.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Socket/Implementation/API_Socket_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun  6 23:51:36 2015 jordan sabbah
// Last update Sat Jul  4 02:01:39 2015 jordan sabbah
//

#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "API_Socket_Unix.hpp"

Socket::Socket()
  : _read(false), _write(false){

}

Socket::Socket(int sock)
  : _sock(sock), _read(false), _write(false){
  _mode = CLIENT;
}

Socket::Socket(const Socket &other)
  : _sock(other._sock), _read(false), _write(false), _mode(other._mode){

}

Socket	&Socket::operator=(const Socket &other){
  _sock = other._sock;
  _read = other._read;
  _write = other._write;
  _mode = other._mode;
  return (*this);
}

Socket::~Socket(){
  close(_sock);
}

void	Socket::Init(int port){
  sockaddr_in	addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    throw Error("socket() failed", "Socket::Init");
  if ((bind(_sock, reinterpret_cast<const struct sockaddr *>(&addr), sizeof(addr))) == -1)
    throw Error("Bind() fail", "Socket::init()");
  if ((listen(_sock, SOMAXCONN)) == -1)
    throw Error("listen() fail", "Socket::init()");
  _mode = SERVER;
}

void	Socket::Init(int port, const std::string &host)
{
  sockaddr_in	addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host.c_str());
  addr.sin_port = htons(port);
  if ((_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    throw Error("Socket() fail", "Socket::Init()");
  if ((connect(_sock, reinterpret_cast<const struct sockaddr *>(&addr), sizeof(addr))) == -1)
    throw Error("Connect() fail", "Socket::init()");
  _mode = CLIENT;
}

ISocket		*Socket::Accept()
{
  int		New_client;
  socklen_t	len;
  sockaddr_in	addr;

  if ((New_client = accept(_sock, reinterpret_cast<struct sockaddr *>(&addr), &len)) == -1)
    throw Error("accept() fail", "Socket_Server::accept()");
  return (new Socket(New_client));

}

std::size_t	Socket::Send(const void *data, std::size_t size)
{
  int					res;

  if ((res = send(_sock, data, size, 0)) == -1)
    return (0);
  return (res);
}

std::size_t	Socket::Receive(void *data, std::size_t size)
{
  int		res;

  if ((res = recv(_sock, data, size, 0)) == -1)
    return (0);
  return (res);
}

bool		Socket::IsReadable() const{
  return (_read);
}

bool		Socket::IsWritable() const{
  return (_write);
}

Mode		Socket::GetMode() const{
  return (_mode);
}

Socket		*converter(ISocket *ptr){
  return (dynamic_cast<Socket *>(ptr));
}

void		Socket::Bigger(int *MaxFd,
			       const std::vector<Socket *> &ReadTAB,
			       const std::vector<Socket *> &WriteTAB) const
{
  std::vector<Socket *>::const_iterator it;

  for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
    if (*MaxFd < (*it)->_sock)
      *MaxFd = (*it)->_sock;
  for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
    if (*MaxFd < (*it)->_sock)
      *MaxFd = (*it)->_sock;
}

int		Socket::Poll(std::vector<ISocket *> &ReadTAB,
			     std::vector<ISocket *> &WriteTAB)
{
  std::vector<Socket *>::iterator	it;
  int					Res;
  int					MaxFd = 0;
  fd_set				ReadSET;
  fd_set				WriteSET;
  std::vector<Socket *>		        RTab(ReadTAB.size());
  std::vector<Socket *>			WTab(WriteTAB.size());

  FD_ZERO(&ReadSET);
  FD_ZERO(&WriteSET);
  std::transform(ReadTAB.begin(), ReadTAB.end(), RTab.begin(), converter);
  std::transform(WriteTAB.begin(), WriteTAB.end(), WTab.begin(), converter);
  Bigger(&MaxFd, RTab, WTab);
  for (it = RTab.begin(); it != RTab.end(); ++it)
    FD_SET((*it)->_sock, &ReadSET);
  for (it = WTab.begin(); it != WTab.end(); ++it)
    FD_SET((*it)->_sock, &WriteSET);
  if ((Res = select(++MaxFd, &ReadSET, &WriteSET, NULL, NULL)) == -1)
    throw Error("Select Failed", "Socket::Poll");
  for (it = RTab.begin(); it != RTab.end(); ++it)
    (*it)->_read = FD_ISSET((*it)->_sock, &ReadSET);
  for (it = WTab.begin(); it != WTab.end(); ++it)
    (*it)->_write = FD_ISSET((*it)->_sock, &WriteSET);
  return (Res);
}


//
// API GENERATION
//
extern "C" EXPORT ISocket *__API_Load__(void)
{
  return (new Socket);
}
