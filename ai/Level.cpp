//
// Level.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 18:53:57 2015 florian hellegouarch
// Last update Sun Jul  5 03:16:32 2015 florian hellegouarch
//

#include "Level.hpp"

const std::string	Level::levelUpStr = "niveau actuel : ";

Level::Level()
{
  lv = 1;
}

Level::~Level()
{ }

int			Level::getLevel() const
{
  return lv;
}

void			Level::update(const std::string &msg)
{
  std::istringstream	iss(msg);

  while (iss.good())
    {
      if (ProtocolParser::isDigit(iss.peek()))
	{
	  iss >> lv;
	  return ;
	}
      iss.get();
    }
}

bool			Level::isUpdate(const std::string &msg)
{
  if (msg.length() >= levelUpStr.length())
    {
      std::string substr = msg.substr(0, levelUpStr.length());
      return substr == levelUpStr;
    }
  return (false);
}
