//
// ProtocolParser.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Fri Jun 19 21:31:57 2015 florian hellegouarch
// Last update Sun Jul  5 17:28:55 2015 florian hellegouarch
//

#ifndef PROTOCOL_PARSER_HPP_
# define PROTOCOL_PARSER_HPP_

# include <string>
# include <sstream>
# include <vector>

class					ProtocolParser
{
public:
  static bool				isDigit(char c);
  static std::string			removeChars(const std::string &chars,
						    const std::string &str);
  static std::string			replaceChars(const std::string &str,
						     char from, char to);
};

#endif // !PROTOCOL_PARSER_HHP_
