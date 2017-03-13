//
// Broadcast.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 21:06:03 2015 florian hellegouarch
// Last update Sun Jul  5 17:24:41 2015 florian hellegouarch
//

#include "Broadcast.hpp"

const std::string		Broadcast::svrMsgStr = "message";

const std::string		Broadcast::messageStr[Broadcast::nbType] =
  {
    "newPlayer",
    "stopFork",
    "readyLv2",
    "readyLv3",
    "readyLv4",
    "readyLv5",
    "readyLv6",
    "readyLv7",
    "readyLv8",
    "unknown"
  };

Broadcast::Broadcast(const std::string &team)
  : team(team)
{ }

Broadcast::~Broadcast()
{ }

Broadcast::Message::Message()
{
  d = Center;
  t = Unknown;
  s = "";
}

Broadcast::Message::Message(Direction d, MessageType t, const std::string &s)
  : d(d), t(t), s(s)
{ }

Broadcast::Message::~Message()
{ }

bool				Broadcast::isBroadcast(const std::string &msg)
{
  std::istringstream		iss(msg);

  if (!iss.good())
    return false;
  std::string			s;
  iss >> s;
  if (s != svrMsgStr)
    return false;
  int				n;
  if (!iss.good() || !ProtocolParser::isDigit(iss.peek()))
    iss >> n;
  if (!iss.good() || iss.get() != ',')
    return false;
  return true;
}

void				Broadcast::addMsg(const std::string &msg)
{
  std::lock_guard<std::mutex>	lock(mutex);
  std::istringstream		iss(msg);

  std::string			message;
  int				dir;
  iss >> message;
  iss >> dir;
  iss.get();
  if (!iss.good())
    return ;
  iss >> message;
  if (message != team)
    return ;
  while (iss.good() && iss.peek() == ' ')
    iss.get();
  std::getline(iss, message);
  Broadcast::MessageType	type = Unknown;
  for (int i = 0; i < nbType - 1; i++)
    {
      if (message.length() >= messageStr[i].length()
	  && message.substr(0, messageStr[i].length()) == messageStr[i])
	{
	  type = static_cast<MessageType>(i);
	  break ;
	}
    }
  if (type != Unknown)
    messages.push(Broadcast::Message(static_cast<Direction>(dir), type, msg));
}

void				Broadcast::clear()
{
  while (messages.size())
    messages.pop();
}

int				Broadcast::getNbMessage()
{
  std::lock_guard<std::mutex>	lock(mutex);

  return messages.size();
}

Broadcast::Message		Broadcast::getNextMessage()
{
  std::lock_guard<std::mutex>	lock(mutex);

  if (messages.size() == 0)
    throw IaClientException("empty message queue", "Broadcast::getNextMessage");
  Message m = messages.front();
  messages.pop();
  return m;
}

std::string			Broadcast::getTeamMessage(MessageType t) const
{
  return team + ' ' + messageStr[t];
}

const std::string		&Broadcast::getMessageStr(MessageType t)
{
  return messageStr[t];
}

std::ostream			&operator<<(std::ostream &os, const Broadcast::Message &m)
{
  os << m.s << " (" << Broadcast::getMessageStr(m.t) << ") " << m.d;
  return os;
}
