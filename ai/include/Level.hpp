//
// Level.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 18:52:42 2015 florian hellegouarch
// Last update Sun Jul  5 03:21:42 2015 florian hellegouarch
//

#ifndef LEVEL_HPP_
# define LEVEL_HPP_

# include <string>
# include <sstream>
# include "ProtocolParser.hpp"

class				Level
{
private:
  int				lv;

public:
  Level();
  ~Level();

  static const std::string	levelUpStr;

  int				getLevel() const;
  void				update(const std::string &msg);
  static bool			isUpdate(const std::string &msg);
};

#endif // !LEVEL_HPP_
