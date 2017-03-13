//
// Egg.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 20 19:31:51 2015 jordan sabbah
// Last update Wed Jul  1 21:58:13 2015 jordan sabbah
//

#ifndef EGG_HPP_
# define EGG_HPP_


# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <iostream>
# include "Error.hpp"
# include <vector>
# include <array>

class Egg {
private:
  enum Type{
    FORK,
    NEW,
    HATCH,
    DEAD
  };
  int				_id;
  int				_playerId;
  int				_posX;
  int				_posY;
  static sf::Texture		_texture;
  static bool			_textureInit;
  bool				_initSprite;
  Type				_type;
  std::array<sf::IntRect, 4>	_eggType;
  sf::Vector2f			_pos;
  int				_delay;
  Egg				&operator=(Egg const &);
public:
  Egg(int, int, int, int);
  Egg(Egg const &);
  ~Egg();
  int				get_id() const;
  int				get_playerId() const;
  int				get_posX() const;
  int				get_posY() const;
  void				hatchEgg();
  void				newEgg(int);
  void				deadEgg();
  bool				is_dead() const;
  Egg				&operator()(std::vector<sf::Vertex> &, sf::IntRect const &);
  static sf::Texture		*get_texture();
};

#endif // !EGG_HPP_
