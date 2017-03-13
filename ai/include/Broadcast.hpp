//
// Broadcast.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 21:05:20 2015 florian hellegouarch
// Last update Sun Jul  5 03:20:23 2015 florian hellegouarch
//

#ifndef BROADCAST_HPP_
# define BROADCAST_HPP_

# include <string>
# include <iostream>
# include <sstream>
# include <queue>
# include <mutex>
# include <utility>
# include "IaClientException.hpp"
# include "ProtocolParser.hpp"

class				Broadcast
{
public:
  enum				Direction
    {
      Center = 0,
      Front = 1,
      FLeft = 2,
      Left = 3,
      BLeft = 4,
      Back = 5,
      BRight = 6,
      Right = 7,
      FRright = 8
    };
  enum				MessageType
    {
      NewPlayer = 0,
      StopFork = 1,
      ReadyLv2 = 2,
      ReadyLv3 = 3,
      ReadyLv4 = 4,
      ReadyLv5 = 5,
      ReadyLv6 = 6,
      ReadyLv7 = 7,
      ReadyLv8 = 8,
      Unknown = 9
    };

  class				Message
  {
  public:
    Message();
    Message(Direction d, MessageType t, const std::string &s);
    ~Message();

    Direction			d;
    MessageType			t;
    std::string			s;
  };

private:
  static const int		nbType = 10;
  static const std::string	svrMsgStr;
  static const std::string	messageStr[nbType];

  std::mutex			mutex;
  std::queue<Message>		messages;
  const std::string		&team;

public:
  Broadcast(const std::string &team);
  ~Broadcast();

  static bool			isBroadcast(const std::string &msg);

  void				addMsg(const std::string &msg);
  void				clear();
  int				getNbMessage();
  Message			getNextMessage();
  std::string			getTeamMessage(MessageType t) const;

  static const std::string	&getMessageStr(MessageType t);
};
std::ostream			&operator<<(std::ostream &os, const Broadcast::Message &m);

#endif // !BROADCAST_HPP_
