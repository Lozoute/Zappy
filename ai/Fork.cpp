//
// Fork.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 16:59:38 2015 florian hellegouarch
// Last update Sun Jul  5 03:16:09 2015 florian hellegouarch
//

#include "Fork.hpp"

Fork::forkProcess	Fork::fork()
{
  int			pid;

  pid = ::fork();
  if (pid < 0)
    throw IaClientException("couldn't fork", "Fork::fork");
  else if (pid > 0)
    return Parent;
  return Child;
}
