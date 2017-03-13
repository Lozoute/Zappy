//
// Player.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 17:59:07 2015 florian hellegouarch
// Last update Sun Jul  5 19:50:50 2015 florian hellegouarch
//

#include "Player.hpp"

const Player::Action	Player::actions[10] =
  {
    NULL, NULL,
    &Player::start,
    &Player::level1,
    &Player::level2_7,
    &Player::waitPlayer,
    &Player::findPlayer,
    &Player::waitLeave,
    &Player::currentLevel,
    &Player::forkBomb
  };

const std::string	Player::ressources[8] =
  {
    "joueur", "linemate", "deraumere",
    "sibur", "mendiane", "phiras",
    "thystame", "nourriture"
  };

const unsigned char	Player::elevation[7][7] =
  {
    { 1, 1, 0, 0, 0, 0, 0 },
    { 2, 1, 1, 1, 0, 0, 0 },
    { 2, 2, 0, 1, 0, 2, 0 },
    { 4, 1, 1, 2, 0, 1, 0 },
    { 4, 1, 2, 1, 3, 0, 0 },
    { 6, 1, 2, 3, 0, 1, 0 },
    { 6, 2, 2, 2, 2, 2, 1 }
  };

Player::Player(const std::string &ip, const std::string &port, const std::string &team)
  : p(ip, port), broadcast(team), team(team), teamSizeLimit(Client::getMinPlayers())
{
  int				numPlayer;

  pathActions[0] = [&] () { p.take(ressources[Food]); };
  pathActions[1] = [&] () { p.take(ressources[Linemate]); };
  pathActions[2] = [&] () { p.take(ressources[Deraumere]); };
  pathActions[3] = [&] () { p.take(ressources[Sibur]); };
  pathActions[4] = [&] () { p.take(ressources[Mendiane]); };
  pathActions[5] = [&] () { p.take(ressources[Phiras]); };
  pathActions[6] = [&] () { p.take(ressources[Thystame]); };
  pathActions[7] = [&] () { p.sendMessage(Protocol::Incantation); };
  pathActions[8] = [&] () { p.sendMessage(Protocol::Forward); };
  pathActions[9] = [&] () { p.sendMessage(Protocol::Left); };
  pathActions[10] = [&] () { p.sendMessage(Protocol::Right); };

  Random::init();
  p.init(team, numPlayer, sizeX, sizeY);
  std::cout << "map size: " << sizeX << ' ' << sizeY << std::endl;
  foodReserveLvl = (sizeX + sizeY) / 2;
  foodReserveLvl = foodReserveLvl > 5 ? foodReserveLvl : 5;
  eggReady = numPlayer > 0;
  readThreadEnd = false;
  readThread = std::thread(readMsgTh, this);
  if (!eggReady)
    std::cout << "team full" << std::endl;
}

Player::~Player()
{
  readThreadEnd = true;
  readThread.join();
}

Player::PlayerReturn	Player::play()
{
  PlayerState		state = Start;

  if (Player::forkOnStart && forkPlayer())
    return Fork;
  while (state > End)
    state = (this->*actions[state])();
  if (state == EndFork)
    return Fork;
  return GameEnd;
}

Player::PlayerState	Player::start()
{
  int			teamSize = 1;

  p.broadcast(broadcast.getTeamMessage(Broadcast::NewPlayer));
  updateRessourcesNeededFood();
  while (teamSize < teamSizeLimit)
    {
      int		n = Random::getInt() % 3 + 1;

      for (int i = 0; i < n; i++)
	{
	  char		updateNb = view.getUpdateNb();

	  p.sendMessage(Protocol::SeeClt);
	  waitSync(0);
	  view.waitUpdate(updateNb);
	  View::Path	path = view.getPath(ressourcesNeeded);
	  doPathActions(path, 5);
	}

      p.sendMessage(Protocol::TeamSlotsClt);
      waitSync(0);
      while (broadcast.getNbMessage() > 0)
	{
	  Broadcast::Message m = broadcast.getNextMessage();

	  if (m.t == Broadcast::NewPlayer)
	    teamSize++;
	  else if (m.t == Broadcast::StopFork)
	    teamSize = teamSizeLimit;
	}	  

      if (teamSize < teamSizeLimit)
	{
	  p.sendMessage(Protocol::TeamSlotsClt);
	  if (!eggReady)
	    p.sendMessage(Protocol::Fork);
	  else if (forkPlayer())
	    return EndFork;
	}
    }
  p.broadcast(broadcast.getTeamMessage(Broadcast::StopFork));
  return CurrentLevel;
}

Player::PlayerState	Player::level1()
{
  targetFoodReserve = 15;
  waitSync(0);
  while (level.getLevel() == 1)
    {
      char		updateNb = view.getUpdateNb();

      waitSync(0);
      p.sendMessage(Protocol::InventoryClt);
      p.sendMessage(Protocol::SeeClt);
      waitSync(0);
      updateRessourcesNeeded();
      view.waitUpdate(updateNb);
      if (checkRessources())
	{
	  emptySquare();
	  dropRessources();
	  waitSync(0);
	  p.sendMessage(Protocol::Incantation);
	  waitSync(0);
	}
      else
	{
	  View::Path	path = view.getPath(ressourcesNeeded);
	  doPathActions(path, 7);
	}
    }
  return CurrentLevel;
}

Player::PlayerState	Player::level2_7()
{
  int			lvl = level.getLevel();

  targetFoodReserve = foodReserveLvl * lvl;
  while (true)
    {
      while (broadcast.getNbMessage() > 0)
	{
	  Broadcast::Message m = broadcast.getNextMessage();

	  if (m.t == Broadcast::ReadyLv2 - 1 + lvl)
	    {
	      moveDirection(m.d);
	      return FindPlayer;
	    }
	}	  
      waitSync(0);
      p.sendMessage(Protocol::InventoryClt);
      char		updateNb = view.getUpdateNb();
      p.sendMessage(Protocol::SeeClt);
      waitSync(1);
      updateRessourcesNeeded();
      view.waitUpdate(updateNb);
      if (checkRessources())
	return WaitPlayer;
      else
	{
	  dropExtraRessources();
	  View::Path	path = view.getPath(ressourcesNeeded);
	  doPathActions(path, 7);
	  if (Random::getInt() % 25 == 0)
	    {
	      if (Random::getBool())
		p.sendMessage(Protocol::Left);
	      else
		p.sendMessage(Protocol::Right);
	    }
	}
    }
  return End;
}

Player::PlayerState		Player::waitPlayer()
{
  int				lvl = level.getLevel();
  Broadcast::MessageType	type = static_cast<Broadcast::MessageType>
    (Broadcast::ReadyLv2 - 1 + lvl);
  std::string			msg = broadcast.getTeamMessage(type);
  int				lim = lvl * foodReserveLvl * 5;

  if (lvl == 8)
    return CurrentLevel;
  int				neededPlayers = elevation[lvl - 1][OtherPlayer];
  while (lim-- && level.getLevel() == lvl)
    {
      char			updateNb = view.getUpdateNb();

      while (broadcast.getNbMessage())
	{
	  Broadcast::Message m = broadcast.getNextMessage();

	  if (m.t == type)
	    {
	      if (Random::getInt() % 3 == 0)
		{
		  moveDirection(m.d);
		  return FindPlayer;
		}
	      broadcast.clear();
	    }
	}
      waitSync(1);
      p.sendMessage(Protocol::SeeClt);
      p.broadcast(msg);
      p.broadcast(msg);
      waitSync(0);
      view.waitUpdate(updateNb);
      if (view.getCurrentSquare()[View::Player] >= neededPlayers)
	{
	  updateNb = view.getUpdateNb();
	  p.sendMessage(Protocol::SeeClt);
	  waitSync(0);
	  view.waitUpdate(updateNb);
	  int			nbPlayer = view.getCurrentSquare()[View::Player];
	  if (nbPlayer == neededPlayers)
	    {
	      emptySquare();
	      dropRessources();
	      waitSync(0);
	      p.sendMessage(Protocol::Incantation);
	      waitSync(0);
	      return CurrentLevel;
	    }
	  else if (nbPlayer > neededPlayers)
	    p.sendMessage(Protocol::Expulse);
	} 
    }
  return Start;
}

Player::PlayerState		Player::findPlayer()
{
  bool				newMessage;
  int				lvl = level.getLevel();
  Broadcast::MessageType	type = static_cast<Broadcast::MessageType>
    (Broadcast::ReadyLv2 - 1 + lvl);
  Broadcast::Direction		lastDir = Broadcast::Center;
  int				lim = 2;
  int				maxMove = 2;

  waitSync(1);
  while (lim--)
    {
      Broadcast::Message	m;
      int			nbMove = 0;
      newMessage = false;
      waitSync(0);
      while (broadcast.getNbMessage())
	{
	  Broadcast::Message m2 = broadcast.getNextMessage();

	  if (m2.t == type)
	    {
	      if (m2.d == Broadcast::Center)
		return WaitLeave;
	      newMessage = true;
	      m = m2;
	      
	    }
	}
      if (newMessage)
	{
	  if (m.d != lastDir)
	    {
	      lastDir = m.d;
	      if (maxMove < 6)
		maxMove += 3;
	    }
	  else if (maxMove > 2)
	    maxMove--;
	  nbMove = moveDirection(m.d);
	  lim = 2;
	}
      else
	{
	  p.sendMessage(Protocol::Forward);
	  nbMove++;
	}
      for (int i = nbMove; i < maxMove; i++)
	p.take(ressources[Food]);
    }
  return CurrentLevel;
}

Player::PlayerState	Player::waitLeave()
{
  char			updateNb = view.getUpdateNb();
  int			lim = 3 * waitLimit; 
  int			lvl = level.getLevel();

  waitSync(1);
  p.sendMessage(Protocol::SeeClt);
  view.waitUpdate(updateNb);
  int			n = view.getCurrentSquare()[View::Player];
  if (n == 1 || lvl > 7 || n > elevation[lvl - 1][OtherPlayer])
    return CurrentLevel;
  while (lim-- && view.getCurrentSquare()[View::Player] >= n)
    {
      waitSync(1);
      updateNb = view.getUpdateNb();
      p.sendMessage(Protocol::SeeClt);
      p.sendMessage(Protocol::Right);
      view.waitUpdate(updateNb);
      broadcast.clear();
    }
  return CurrentLevel;
}

Player::PlayerState			Player::currentLevel()
{
  static const Player::PlayerState	tab[9] =
    {
      Level1,
      Level2_7,
      Level2_7,
      Level2_7,
      Level2_7,
      Level2_7,
      Level2_7,
      ForkBomb
    };
  int					lvl = level.getLevel() - 1;

  return tab[lvl];
}

Player::PlayerState	Player::forkBomb()
{
  updateRessourcesNeededFood();
  while (true)
    {      
      char		updateNb = view.getUpdateNb();

      waitSync(3);
      p.sendMessage(Protocol::SeeClt);
      p.sendMessage(Protocol::TeamSlotsClt);
      p.sendMessage(Protocol::Fork);
      waitSync(1);
      view.waitUpdate(updateNb);
      View::Path	path = view.getPath(ressourcesNeeded);
      doPathActions(path, 8);
      if (forkPlayer())
       return EndFork;
      broadcast.clear();
    }
  return End;
}

void				Player::updateRessourcesNeeded()
{
  const int			shift = Linemate - View::Linemate;
  const int			shiftInv = Inventory::Linemate - View::Linemate;
  int				n;
  int				lvl = level.getLevel() - 1;

  n = targetFoodReserve - inventory[Inventory::Food];
  if (n < 0)
    n = 0;
  ressourcesNeeded[View::Food] = n;
  ressourcesNeeded[View::Player] = 0;
  if (lvl == 8)
    {
      for (int i = View::Linemate; i <= View::Thystame; i++)
	ressourcesNeeded[i] = 0;
    }
  else
    {
      for (int i = View::Linemate; i <= View::Thystame; i++)
	{
	  n = elevation[lvl][i + shift] - inventory[i + shiftInv];
	  if (n < 0)
	    n = 0;
	  ressourcesNeeded[i] = n;
	}
    }
}

void				Player::updateRessourcesNeededFood()
{
  for (unsigned char &c : ressourcesNeeded)
    c = 0;
  ressourcesNeeded[View::Food] = 99;
}

bool				Player::checkRessources() const
{
  for (unsigned char r : ressourcesNeeded)
    if (r > 0)
      return false;
  return true;
}

void				Player::doPathActions(const View::Path &path, int sync)
{
  waitSync(sync);
  for (View::pathAction a : path)
    {
      pathActions[a]();
      waitSync(sync);
    }
}

int				Player::moveDirection(Broadcast::Direction d)
{
  int				n = 1;

  waitSync(3);
  if (d == Broadcast::Center)
    return 0;
  if (d == Broadcast::Left
      || d == Broadcast::BLeft)
    {
      p.sendMessage(Protocol::Left);
      n = 2;
    }
  else if (d == Broadcast::Right
	   || d == Broadcast::BRight)
    {
      p.sendMessage(Protocol::Right);
      n = 2;
    }
  else if (d == Broadcast::Back)
    {
      p.sendMessage(Protocol::Right);
      p.sendMessage(Protocol::Right);
      n = 3;
    }
  p.sendMessage(Protocol::Forward);
  return n;
}

void				Player::emptySquare()
{
  if (view.getNbSquare() < 1)
    return ;
  const View::Square		&s = view.getSquare(0, 0);
  int				shift = Linemate - View::Linemate;

  for (int i = View::Linemate; i <= View::View::Thystame; i++)
    {
      for (int j = 0; j < s[i]; j++)
	{
	  waitSync(5);
	  p.take(ressources[i + shift]);
	}
    }
}

void				Player::dropRessources()
{  
  int				lvl = level.getLevel() - 1;

  if (lvl < 7)
    {
      for (int i = Linemate; i <= Thystame; i++)
	{
	  for (int j = 0; j < elevation[lvl][i]; j++)
	    {
	      waitSync(5);
	      p.drop(ressources[i]);
	    }
	}
    }
}

void				Player::dropExtraRessources()
{
  int				lvl = level.getLevel() - 1;
  int				shift = Inventory::Linemate - Linemate;

  for (int i = Linemate; i <= Thystame; i++)
    {
      int			n = inventory[i + shift];

      if (lvl < 7)
	n -= elevation[lvl][i];
      for (int j = 0; j < n; j++)
	{
	  waitSync(5);
	  p.drop(ressources[i]);
	}
    }
}

void							Player::readMsg()
{
  const std::function<void (const std::string &)>	update[11] = 
    {
      NULL, // ok
      NULL, // ko
      [this] (const std::string &s) { view.update(s); }, // view
      [this] (const std::string &s) { inventory.update(s); }, // inventory
      [this] (const std::string &s) { broadcast.addMsg(s); }, // broadcast
      NULL, // elevation start
      [this] (const std::string &s) { level.update(s); }, // level up
      [this] (const std::string &s) { eggReady = !s.empty() && s[0] != '0'; }, // team slots
      [this] (const std::string &)
      {
	readThreadEnd = true;
	std::cout << "dead" << std::endl;
      }, // dead
      NULL // moved
    };
  const std::string					msgType[12] =
    {
      "ok",
      "ko",
      "view",
      "inventory",
      "broadcast",
      "elevation",
      "level up",
      "team slots",
      "dead",
      "moved",
      "unknown"
    };

  try
    {
      while (!readThreadEnd)
	{
	  Protocol::serverMessage type;
	  std::string msg = p.getMessage(type);

	  if (Client::getDebug())
	    {
	      std::cout << Client::blue << Client::getPid() << "_message ";
	      std::cout << msgType[type] << Client::reset << std::endl;
	    }
	  if (type != Protocol::Error)
	    {
	      if (update[type])
		update[type](msg);
	    }
	  else
	    throw IaClientException("failed to parse server message: " + msg,
				    "Player::readMsg");
	}
      p.errorStop();
  }
  catch (IaClientException &e)
    {
      p.errorStop();
      throw e;
    }
  catch (std::exception &e)
    {
      p.errorStop();
      throw IaClientException(e.what(), "Player::readMsg");
    }
}

void			Player::waitSync(char n)
{
  p.waitSync(n);
}

void			Player::readMsgTh(Player *p)
{
  try
    {
      p->readMsg();
    }
  catch (IaClientException &e)
    {
      e.showError();
    }
}

bool			Player::forkPlayer()
{
  if (eggReady)
    {
      eggReady = false;
      return Fork::fork() == Fork::Child;
    }
  return false;
}
