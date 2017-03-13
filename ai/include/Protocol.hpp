//
// Protocol.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 17:09:48 2015 florian hellegouarch
// Last update Sun Jul  5 03:22:03 2015 florian hellegouarch
//

#ifndef PROTOCOL_HPP_
# define PROTOCOL_HPP_

# include <string>
# include <sstream>
# include <vector>
# include <mutex>
# include <condition_variable>
# include <chrono>
# include "socket.h"
# include "Client.hpp"
# include "ProtocolParser.hpp"
# include "View.hpp"
# include "Inventory.hpp"
# include "Level.hpp"
# include "Broadcast.hpp"

class				Protocol
{
public:
  enum				serverMessage
    {
      Ok = 0,
      Ko = 1,
      See = 2,
      Inventory = 3,
      Broadcast = 4,
      ElevationStarted = 5,
      ElevationOk = 6,
      TeamSlots = 7,
      Dead = 8,
      Moved = 9,
      Error = 10
    };

  enum				clientMessage
    {
      Forward = 0,
      Right = 1,
      Left = 2,
      SeeClt = 3,
      InventoryClt = 4,
      Expulse = 5,
      Incantation = 6,
      Fork = 7,
      TeamSlotsClt = 8
    };

private:
  typedef bool			(*checkFct)(const std::string &s);

  static const int		buffSize;
  static const std::string	msgStr[9];

  int				socket_fd;
  char				sync;
  std::mutex			syncMutex;
  std::condition_variable	syncCondVar;
  bool				threadError;

  std::string			get();
  void				send(const std::string &message);
  void				incSync();
  void				decSync();
  void				signal();
  static bool			parseMove(const std::string &s);

public:
  Protocol(const std::string &ip, const std::string &port);
  ~Protocol();

  void				init(const std::string &team, int &numClient, int &sizeX, int &sizeY);
  std::string			getMessage(serverMessage &type);
  void				waitSync(char maxVal);
  void				errorStop();

  void				sendMessage(clientMessage msg);
  void				take(std::string object);
  void				drop(std::string object);
  void				broadcast(std::string message);
};

#endif // !PROTOCOL_HPP_
