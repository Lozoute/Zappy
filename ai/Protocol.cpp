//
// Protocol.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 19:54:07 2015 florian hellegouarch
// Last update Sun Jul  5 03:17:22 2015 florian hellegouarch
//

#include "Protocol.hpp"
#include "IaClientException.hpp"
#include "ConnectionException.hpp"

const std::string		Protocol::msgStr[9] =
  {
    "avance",
    "droite",
    "gauche",
    "voir",
    "inventaire",
    "expulse",
    "incantation",
    "fork",
    "connect_nbr"
  };

Protocol::Protocol(const std::string &ip, const std::string &port)
  : sync(0), threadError(false)
{
  socket_fd = socket_init_clt(ip.c_str(), port.c_str());
  if (socket_fd == -1)
    throw IaClientException("can't open socket", "Protocol constructor");

  std::string message = get();
  if (message != "BIENVENUE")
    throw IaClientException(std::string("server sent \"") + message + "\" instead of BIENVENUE", "Protocol constructor");
  std::cout << "connected to server" << std::endl;
}

Protocol::~Protocol()
{
  if (close_socket(socket_fd) == -1)
    throw IaClientException("can't close socket", "Protocol destructor");
}

void				Protocol::init(const std::string &team, int &numClient, int &sizeX, int &sizeY)
{
  send(team);
  std::istringstream		iss1(get());
  std::istringstream		iss2(get());
  if (iss1.str() == "ko" || iss2.str() == "ko")
    throw IaClientException("failed to connect to server (invalid team name / too many players connected ?)", "Protocol::init");
  iss1 >> numClient;
  iss2 >> sizeX >> sizeY;
}

std::string			Protocol::get()
{
  std::ostringstream		oss;
  char				c = get_char(socket_fd);

  while (c != '\n')
    {
      if (c == 0)
	throw IaClientException("connection lost", "Protocol::get");
      if (c == -1)
	throw IaClientException("socket read error", "Protocol::get");
      oss << c;
      c = get_char(socket_fd);
    }
  if (Client::getDebug())
    {
      std::cout << Client::yellow << Client::getPid() << '_';
      std::cout << oss.str() << Client::reset << std::endl;
    }
  return oss.str();
}

void				Protocol::send(const std::string &message)
{
  if (Client::getDebug())
    {
      std::cout << Client::green << Client::getPid() << '_';
      std::cout << message << Client::reset << std::endl;
    }
  if (write_line(socket_fd, message.c_str()) == -1)
    throw IaClientException("socket write error", "Protocol::send");
}

void				Protocol::incSync()
{
  std::lock_guard<std::mutex>	lock(syncMutex);

  if (++sync >= 9)
    throw IaClientException("too many async messages", "Protocol::incSync");
}

void				Protocol::decSync()
{
  std::unique_lock<std::mutex>	lock(syncMutex);

  sync--;
  lock.unlock();
  signal();
}

void				Protocol::waitSync(char maxVal)
{
  std::unique_lock<std::mutex>	lock(syncMutex);
  std::chrono::seconds		limit(Client::getTimeout());
  std::ostringstream		where;

  where << "Protocol::waitSync(" << static_cast<int>(maxVal) << ')';
  while (sync > maxVal && !threadError)
    {
      if (syncCondVar.wait_for(lock, limit)
	  == std::cv_status::timeout)
	throw IaClientException("timeout", where.str());
    }
  if (threadError)
    {
      throw ConnectionException();
    }
}

void				Protocol::errorStop()
{
  threadError = true;
  signal();
}

void				Protocol::signal()
{
  syncCondVar.notify_one();
}

bool				Protocol::parseMove(const std::string &s)
{
  static const std::string	str = "deplacement";

  if (s.length() >= str.length()
      && str == s.substr(0, str.length()))
    return true;
  return false;
}

std::string			Protocol::getMessage(Protocol::serverMessage &type)
{
  static const checkFct		checkUpdate[10] =
    {
      [] (const std::string &s) { return s == "ok"; },
      [] (const std::string &s) { return s == "ko"; },
      &View::isUpdate,
      &Inventory::isUpdate,
      &Broadcast::isBroadcast,
      [] (const std::string &s) { return s == "elevation en cours"; },
      &Level::isUpdate,
      [] (const std::string &s) { return !s.empty() && ProtocolParser::isDigit(s[0]); },
      [] (const std::string &s) { return s == "mort"; },
      &Protocol::parseMove
    };
  std::string			msg = get();

  for (int i = 0; i < 10; i++)
    {
      if (checkUpdate[i](msg))
	{
	  type = (Protocol::serverMessage)i;
	  if (type != Broadcast
	      && type != ElevationOk
	      && type != Dead
	      && type != Moved)
	    decSync();
	  return msg;
	}
    }
  type = Error;
  return msg;
}

void				Protocol::sendMessage(Protocol::clientMessage msg)
{
  incSync();
  send(msgStr[(int)msg]);
}

void				Protocol::take(std::string object)
{
  incSync();
  send("prend " + object);
}

void				Protocol::drop(std::string object)
{
  incSync();
  send("pose " + object);
}

void				Protocol::broadcast(std::string message)
{
  incSync();
  send("broadcast " + message);
}
