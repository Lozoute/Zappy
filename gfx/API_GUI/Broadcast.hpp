//
// Broadcast.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 01:55:23 2015 jordan sabbah
// Last update Sun Jul  5 08:46:05 2015 jordan sabbah
//

#ifndef BROADCAST_HPP_
# define BROADCAST_HPP_

# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <string>
# include "Error.hpp"

class Broadcast{
private:
  std::string const	_file = "gfx/API_GUI/source/broadcast.png";
  static sf::Texture	_texture;
  static bool		_textureInit;
  int			_counter;
  std::string		_msg;
  bool			_ready;
  sf::Vector2u		_size;
  int			_delay;
  Broadcast		&operator=(Broadcast const &);
public:
  Broadcast();
  Broadcast(Broadcast const &);
  ~Broadcast();
  void			set_msg(std::string const &, int);
  Broadcast		&operator()(std::vector<sf::Vertex> &, sf::IntRect const &);
  int			get_count() const;
  static sf::Texture	*get_texture();
};

#endif // !BROADCAST_HPP_
