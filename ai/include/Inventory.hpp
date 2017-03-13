//
// Inventory.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 16:44:19 2015 florian hellegouarch
// Last update Sun Jul  5 17:32:33 2015 florian hellegouarch
//

#ifndef INVENTORY_HPP_
# define INVENTORY_HPP_

# include <string>
# include <iostream>
# include <sstream>
# include "ProtocolParser.hpp"

class				Inventory
{
public:
  enum				objectType
    {
      Food = 0,
      Linemate = 1,
      Deraumere = 2,
      Sibur = 3,
      Mendiane = 4,
      Phiras = 5,
      Thystame = 6
    };

  static const int		invSize = 7;
  static const std::string	objectName[Inventory::invSize];

private:
  unsigned char			inv[invSize];

public:
  Inventory();
  ~Inventory();

  void				update(const std::string &msg);
  static bool			isUpdate(const std::string &msg);
  static int			getId(const std::string &str);

  unsigned char			operator[](objectType t) const;
  unsigned char			operator[](int i) const;
};

std::ostream			&operator<<(std::ostream &os, const Inventory &inv);


#endif // !INVENTORY_HPP_
