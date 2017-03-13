//
// Random.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 23:15:11 2015 florian hellegouarch
// Last update Sun Jul  5 03:17:39 2015 florian hellegouarch
//

#include "Random.hpp"

void	Random::init()
{
  std::srand(std::time(0));
}

int	Random::getInt()
{
  return std::rand();
}

float	Random::getFloat()
{
  float	x;

  x = std::rand();
  return (x / RAND_MAX);
}

bool	Random::getBool()
{
  return (std::rand() % 2);
}
