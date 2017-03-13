//
// Player.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Thu Jun 11 23:52:56 2015 jordan sabbah
// Last update Fri Jul  3 03:35:14 2015 jordan sabbah
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <utility>
# include <stdexcept>
# include <array>
# include "Error.hpp"
# include "Orientation.hpp"

class Player {
protected:
  int		const	_id;
  std::string const	_team;
  int			_posX;
  int			_posY;
  int			_lvl;
  Orientation		_orientation;
  std::array<int, 7>	_inventory;
public:
  Player(int, int, int, Orientation, int , std::string const &);
  virtual ~Player();
  Player(Player const &);
  Player		&operator=(Player const &);
  int			get_id() const;
  int			get_posX() const;
  int			get_posY() const;
  void			set_posX(int);
  void			set_posY(int);
  void			set_inventory(std::array<int, 7> const &);
  int			get_lvl() const;
  void			put_toInventory(int);
  void		        put_outOfInventory(int);
  Orientation		get_orientation() const;
  std::string const	&get_teamName() const;
  void			lvl_up();
  virtual void		set_lvl(int);
  bool			is_position(int, int);
  void			turn_right();
  void			turn_left();
  void			move();
};

#endif // !PLAYER_HPP_
