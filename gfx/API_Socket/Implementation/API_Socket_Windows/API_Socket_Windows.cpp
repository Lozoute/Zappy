# include "API_Socket_Windows.hpp"

//
// Constructors...
//

Socket::Socket()
  : _read(false), _write(false)
{
  WSAStartup(MAKEWORD(2, 2), &(_wsaData));
}

Socket::Socket(SOCKET sock)
  : _sock(sock), _read(false), _write(false)
{
  _mode = CLIENT;
  WSAStartup(MAKEWORD(2, 2), &(_wsaData));
}

Socket::Socket(const Socket &other)
  : _sock(other._sock), _read(false), _write(false), _mode(other._mode)
{
  WSAStartup(MAKEWORD(2, 2), &(_wsaData));
}

Socket &Socket::operator=(const Socket &other)
{
  if (&other != this)
    {
      _sock = other._sock;
      _this->_read = other._read;
      _write = other._write;
    }
  return (*this);
}

Socket::~Socket()
{
  closesocket(_sock);
  WSACleanup();
}

//
// INIT
//
void	Socket::Init(int port)
{
  SOCKADDR_IN		addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    throw Error("socket() failed", "Socket::Init");
  if ((bind(this->_sock, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr))) == SOCKET_ERROR)
    throw Error("Bind() fail", "Socket::init()");
  if ((listen(this->_sock, SOMAXCONN)) == SOCKET_ERROR)
    throw Error("listen() fail", "Socket::init()");
  _mode = SERVER;
}

void	Socket::Init(int port, const std::string &host)
{
  sockaddr_in		addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host.c_str());
  addr.sin_port = htons(port);
  if ((_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    throw Error("Socket() fail", "Socket::Init()");
  if ((connect(_sock, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr))) == SOCKET_ERROR)
    throw Error("Connect() fail", "Socket::init()");
  _mode = CLIENT;
}

//
// BASIC FUNCTIONS
//
ISocket		*Socket::Accept()
{
  SOCKET	New_client;

  if ((New_client = accept(_sock, NULL, NULL)) == INVALID_SOCKET)
    throw Error("accept() fail", "Socket_Server::accept()");
  return (new Socket(New_client));
}

std::size_t	Socket::Send(const void *data, std::size_t size)
{
  int	res;

  if ((res = send(_sock, static_cast<const char *>(data), size, 0)) == SOCKET_ERROR)
    return (0);
  return (res);
}

std::size_t	Socket::Receive(void *data, std::size_t size)
{
  int		res;

  if ((res = recv(_sock, static_cast<char *>(data), size, 0)) == SOCKET_ERROR)
    return (0);
  return (res);
}

//
// GETTERS
//

bool		Socket::IsReadable() const
{
  return (_read);
}

bool		Socket::IsWritable() const
{
  return (_write);
}

Mode		Socket::GetMode() const
{
  return (_mode);
}

//
// POLL
//

Socket *converter(ISocket *value){
  return dynamic_cast<Socket *>(value);
}

int	Socket::Poll(std::vector<ISocket *> &ReadTAB, std::vector<ISocket *> &WriteTAB)
{
  std::vector<Socket *>			RTab(ReadTAB.size());
  std::vector<Socket *>		        WTab(WriteTAB.size());
  std::vector<Socket *>::iterator	it;
  int					Res;
  int					MaxFd = 0;
  fd_set				ReadSET;
  fd_set				WriteSET;
  struct timeval			Tv = { 2, 0 };

  std::transform(ReadTAB.begin(), ReadTAB.end(), RTab.begin(), converter);
  std::transform(WriteTAB.begin(), WriteTAB.end(), WTab.begin(), converter);

  FD_ZERO(&ReadSET);
  FD_ZERO(&WriteSET);
  for (it = RTab.begin(); it != RTab.end(); ++it)
    FD_SET((*it)->_sock, &ReadSET);
  for (it = WTab.begin(); it != WTab.end(); ++it)
    FD_SET((*it)->_sock, &WriteSET);
  if ((Res = select(MaxFd, &ReadSET, &WriteSET, NULL, &Tv)) == SOCKET_ERROR)
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
