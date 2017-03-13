//
// Cell.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 13 01:14:03 2015 jordan sabbah
// Last update Wed Jul  1 22:00:39 2015 jordan sabbah
//

#ifndef CELL_HPP_
# define CELL_HPP_

# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <array>
# include <cstdlib>
# include <iostream>
# include "Error.hpp"
# include "Object.hpp"

class Cell {
private:
  int			_posX;
  int			_posY;
  int			_id;
  static sf::Texture	_texture;
  static bool		_init;
  sf::Vector2u		_winPos;
  std::array<Object, 7>	_inventory;
  sf::Vector2u		_size;
public:
  Cell();
  Cell(int, int);
  Cell(Cell const &);
  ~Cell();
  Cell			&operator=(Cell const &);
  void			set_pos(int, int);
  int			get_posX() const;
  int			get_posY() const;
  sf::Vector2u const	&get_winPos() const;
  sf::Vector2u const	get_textureSize() const;
  void			update_object(Object::Type, int);
  void			update_inventory(std::array<int, 7> const &);
  void			get_cell(std::vector<sf::Vertex> &);
  void			get_inventory(std::vector<sf::Vertex> &);
  Cell			&operator()(std::vector<sf::Vertex> &, std::vector<sf::Vertex> &);
  static sf::Texture	*get_texture();
};

std::ostream		&operator<<(std::ostream &, Cell const &);

#endif // !CELL_HPP_
