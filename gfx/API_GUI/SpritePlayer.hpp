//
// SpritePlayer.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 12 11:05:17 2015 jordan sabbah
// Last update Sun Jul  5 17:27:06 2015 jordan sabbah
//

#ifndef SPRITEPLAYER_HPP_
# define SPRITEPLAYER_HPP_

# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <array>
# include <deque>
# include "Player.hpp"
# include "Broadcast.hpp"


class Map;

class SpritePlayer : public Player{
protected:
  std::string const			_file = "gfx/API_GUI/source/my_chars.png";
  // std::string const			_file = "API_GUI/source/zappy_theme_char.png";
  static sf::Texture			_texture;
  static bool				_textureInit;
  std::array<sf::IntRect, 12>		_teamSprites;
  std::deque<sf::Vertex>		_toDraw;
  sf::Vector2f				_pos;
  sf::Vector2f				_unit;
  Broadcast				_broadcast;
private:
  SpritePlayer(SpritePlayer const &);
  SpritePlayer				&operator=(SpritePlayer const &);
  void					turnSprite(Orientation o);
  void					moveSprite(int, int, class Map const &);
public:
  SpritePlayer(int id, int x, int y, Orientation o,
	       int lvl, std::string const &name, class Map const &);
  ~SpritePlayer();
  sf::Vertex const			&get_toDraw();
  void				        update_toDraw();
  void					moveSprite();
  void					sendInstruction(int x, int y,
							Orientation o, class Map const &);
  void					broadcast(std::string const &);
  void					expulse();
  int					get_toDrawSize() const;
  virtual void			        set_lvl(int);
  SpritePlayer				&operator>>(std::vector<sf::Vertex> &);
  SpritePlayer				&operator()(std::vector<sf::Vertex> &, std::vector<sf::Vertex> &);
  void					put_posPlayer(sf::Vector2f const &, sf::IntRect const &);
  static sf::Texture			*get_texture();
  int					is_action() const;
};

#endif // !SPRITEPLAYER_HPP_
