//
// Player.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 17:57:58 2015 florian hellegouarch
// Last update Sun Jul  5 03:21:52 2015 florian hellegouarch
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <string>
# include <iostream>
# include <thread>
# include <mutex>
# include <queue>
# include <stdexcept>
# include <functional>
# include "Protocol.hpp"
# include "Random.hpp"
# include "Inventory.hpp"
# include "Level.hpp"
# include "View.hpp"
# include "Broadcast.hpp"
# include "Fork.hpp"
# include "IaClientException.hpp"

class					Player
{
public:
  enum					PlayerReturn
    {
      Fork,
      GameEnd
    };

  enum					PlayerState
    {
      EndFork = 0,
      End = 1,
      Start = 2,
      Level1 = 3,
      Level2_7 = 4,
      WaitPlayer = 5,
      FindPlayer = 6,
      WaitLeave = 7,
      CurrentLevel = 8,
      ForkBomb = 9
    };

  enum					PlayerRessources
    {
      OtherPlayer = 0,
      Linemate = 1,
      Deraumere = 2,
      Sibur = 3,
      Mendiane = 4,
      Phiras = 5,
      Thystame = 6,
      Food = 7
    };

private:
  typedef PlayerState			(Player::*Action)();
  typedef void				(*UpdateFct)(const std::string &);
  static const Action			actions[10];
  static const std::string		ressources[8];
  static const unsigned char		elevation[7][7];
  static const bool			forkOnStart = false;
  static const int			waitLimit = 50;

  Protocol				p;
  std::thread				readThread;
  bool					readThreadEnd;
  
  Inventory				inventory;
  Level					level;
  View					view;
  Broadcast				broadcast;
  unsigned char				ressourcesNeeded[View::nbObject];
  std::function<void ()>		pathActions[View::nbAction];
  int					targetFoodReserve;
  int					foodReserveLvl;

  std::string				team;
  int					sizeX;
  int					sizeY;
  bool					eggReady;
  const int				teamSizeLimit;

  PlayerState				start();
  PlayerState				level1();
  PlayerState				level2_7();
  PlayerState				waitPlayer();
  PlayerState				findPlayer();
  PlayerState				waitLeave();
  PlayerState				currentLevel();
  PlayerState				forkBomb();

  bool					forkPlayer();
  void					readMsg();
  void					waitSync(char n);
  void					doPathActions(const View::Path &p, int sync);
  int					moveDirection(Broadcast::Direction d);
  void					emptySquare();
  void					dropRessources();
  void					dropExtraRessources();
  void					updateRessourcesNeeded();
  void					updateRessourcesNeededFood();
  bool					checkRessources() const;

public:
  Player(const std::string &ip, const std::string &port, const std::string &team);
  ~Player();

  PlayerReturn				play();
  static void				readMsgTh(Player *p);
};

#endif // !PLAYER_HPP_
