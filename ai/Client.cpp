//
// Client.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 18:18:08 2015 florian hellegouarch
// Last update Sun Jul  5 23:08:58 2015 florian hellegouarch
//

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Client.hpp"
#include "Player.hpp"
#include "IaClientException.hpp"

int				Client::timeout = 20;
bool				Client::debug = false;
int				Client::minPlayers = 8;
pid_t				Client::pid = 0;

const std::string		Client::white = "\e[1;37m";
const std::string		Client::red = "\e[1;31m";
const std::string		Client::blue = "\e[1;36m";
const std::string		Client::green = "\e[1;32m";
const std::string		Client::yellow = "\e[1;33m";
const std::string		Client::reset = "\e[0m";

bool				Client::getArg(std::string *args, int ac, char **av)
{
  std::string			flags[5] = { "-h", "-p", "-n", "-t", "-m" };

  for (int i = 1; i < ac; i++)
    {
      int			j;

      if (av[i] == std::string("--debug"))
	{
	  Client::debug = true;
	  continue ;
	}
      for (j = 0; j < 5; j++)
	if (flags[j] == av[i])
	  break ;
      if (j == 5)
	{
	  std::cerr << "unknown option " << av[i] << std::endl;
	  return false;
	}
      else if (i == ac - 1)
	{
	  std::cerr << "missing argument after " << flags[j] << std::endl;
	  return false;
	}
      else
	args[j] = av[++i];
    }
  if (args[3] != "")
    {
      std::istringstream	iss(args[3]);
      iss >> timeout;
    }
  if (args[4] != "")
    {
      std::istringstream	iss(args[4]);
      iss >> minPlayers;
    }
  return true;
}

bool				Client::parseArgs(std::string *args, int ac, char **av)
{
  if (!getArg(args, ac, av) || args[2] == "")
    {
      std::cerr << white << "Usage: " << av[0];
      std::cerr << " -n teamName [-h ip] [-p port] [-t timeout] [-m minPlayers] [--debug]";
      std::cerr << std::endl << reset;
      return false;
    }
  if (args[0] == "")
    args[0] = "127.0.0.1";
  if (args[1] == "")
    args[1] = "4242";
  std::cout << "ip: " << args[0] << " port: " << args[1];
  std::cout << " team: " << args[2] << std::endl;
  return true;
}

void				Client::checkArgs()
{
  if (timeout < 1 || timeout > 3600)
    throw IaClientException("invalid timeout", "Client::checkArgs");
  if (minPlayers < 1 || minPlayers > 64)
    throw IaClientException("invalid minPlayers", "Client::checkArgs");
}

void				Client::start(int ac, char **av)
{
  std::string			args[5];

  if (parseArgs(args, ac, av))
    {
      checkArgs();
      Player::PlayerReturn	ret;
      do
	{
	  pid = ::getpid();
	  Player p(args[0], args[1], args[2]);
	  ret = p.play();
	} while (ret == Player::Fork);
    }
}

int				Client::getTimeout()
{
  return timeout;
}

bool				Client::getDebug()
{
  return debug;
}

void				Client::exit()
{
  IaClientException::showError("Exit");
  ::exit(0);
}

int				Client::getMinPlayers()
{
  return minPlayers;
}

pid_t				Client::getPid()
{
  return Client::pid;
}
