//
// Inventory.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 16:45:05 2015 florian hellegouarch
// Last update Sun Jul  5 17:25:51 2015 florian hellegouarch
//

#include "Inventory.hpp"

const std::string		Inventory::objectName[Inventory::invSize] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
  };

Inventory::Inventory()
{
  for (int i = 0; i < Inventory::invSize; i++)
    inv[i] = 0;
}

Inventory::~Inventory()
{ }

void				Inventory::update(const std::string &msg)
{
  std::string			s;
  int				id;
  int				n;

  s = ProtocolParser::replaceChars(ProtocolParser::removeChars("{}", msg), ',', ' ');
  std::istringstream		iss(s);
  while (iss.good())
    {
      iss >> s;
      if ((id = getId(s)) != -1 && iss.good())
	{
	  iss >> n;
	  inv[id] = static_cast<unsigned char>(n);
	}
    }
}

bool				Inventory::isUpdate(const std::string &msg)
{
  std::string			s;
  int				i = 0;

  s = ProtocolParser::replaceChars(ProtocolParser::removeChars("{}", msg), ',', ' ');
  std::istringstream		iss(s);
  while (i < Inventory::invSize && iss.good())
    {
      iss >> s;
      if (!iss.good() || getId(s) == -1)
	return false;
      iss >> s;
      if (s.empty() || !ProtocolParser::isDigit(s[0]))
	  return false;
      i++;
    }
  return true;
}

int				Inventory::getId(const std::string &str)
{
  int				i = 0;

  while (i < Inventory::invSize)
    {
      if (str == objectName[i])
	return i;
      i++;
    }
  return -1;
}

unsigned char			Inventory::operator[](objectType t) const
{
  return inv[static_cast<int>(t)];
}

unsigned char			Inventory::operator[](int i) const
{
  return inv[i];
}

std::ostream			&operator<<(std::ostream &os, const Inventory &inv)
{
  for (int i = 0; i < Inventory::invSize; i++)
    os << Inventory::objectName[i] << ": " << static_cast<int>(inv[i]) << std::endl;
  return os;
}
