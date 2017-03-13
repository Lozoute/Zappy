//
// ProtocolParser.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Fri Jun 19 21:32:58 2015 florian hellegouarch
// Last update Sun Jul  5 17:28:56 2015 florian hellegouarch
//

#include "ProtocolParser.hpp"

std::string			ProtocolParser::removeChars(const std::string &chars,
							    const std::string &str)
{
  char				c;
  std::istringstream		iss(str);
  std::ostringstream		oss;

  c = iss.get();
  while (iss.good())
    {
      if (chars.find(c) == std::string::npos)
	oss << c;
      c = iss.get();
    }
  return oss.str();
}

std::string			ProtocolParser::replaceChars(const std::string &str,
							     char from, char to)
{
  std::ostringstream		oss("");

  for (char c : str)
    {
      if (c == from)
	oss << to;
      else
	oss << c;
    }
  return oss.str();
}

bool				ProtocolParser::isDigit(char c)
{
  return c >= '0' && c <= '9';
}
