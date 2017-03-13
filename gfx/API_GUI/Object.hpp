//
// Object.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 13 21:25:55 2015 jordan sabbah
// Last update Wed Jul  1 21:59:03 2015 jordan sabbah
//

#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <cstdlib>
# include <ctime>
# include "Error.hpp"

class Object{
public:
    enum Type{
    Food,
    Linemate,
    Deraumiere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame
  };
protected:
  Type	const			_name;
  int				_quantity;
  static sf::Texture		_texture;
  static bool			_init;
  sf::Vector2f			_position;
  bool				_initSprite;
public:
  Object(Type name);
  Object(Type name, int quantity);
  ~Object();
  Object(Object const &);
  Object			&operator=(Object const &);
  int				get_quantity() const;
  Object::Type			get_type() const;
  void				update_quantity(int);
  Object			&operator()(std::vector<sf::Vertex> &, sf::IntRect const &);
  static sf::Texture		*get_texture();
};

#endif // !OBJECT_HPP_
