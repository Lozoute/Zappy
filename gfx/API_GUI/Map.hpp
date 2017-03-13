//
// Map.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 13 11:02:45 2015 jordan sabbah
// Last update Sat Jul  4 04:19:54 2015 jordan sabbah
//

#ifndef MAP_HPP_
# define MAP_HPP_

# include <SFML/Graphics/RenderTexture.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <vector>
# include <cmath>
# include "Cell.hpp"
# include "API_Mutex_C.hpp"

class Egg;
class SpritePlayer;
class Window;

class Map{
public:
  enum MOVE{
    Left,
    Right,
    Up,
    Down
  };
  enum ZOOM{
    In,
    Out
  };
private:
  typedef void			(Map::*fptr)();
  int				_sizeX;
  int				_sizeY;
  std::vector<Cell>		_map;
  std::vector<sf::Vertex>	_spriteCell;
  std::vector<sf::Vertex>	_spriteObj;
  sf::RenderTexture		_texture;
  sf::Sprite			_sprite;
  sf::IntRect			_view;
  sf::Vector2f			_scale;
  sf::Vector2f			_origin;
  Mutex				_mutex;
  void				set_view();
  void				set_sprite();
  void				move_left();
  void				move_right();
  void				move_up();
  void				move_down();
  void				zoomIn();
  void				zoomOut();
  void				check_init() const;
  Map(Map const &);
  Map				&operator=(Map const &);
public:
  Map();
  Map(int, int);
  ~Map();
  void				init(int, int);
  int				get_sizeX() const;
  int				get_sizeY() const;
  sf::Vector2f const		get_pos(int, int) const;
  sf::Vector2f const		get_unitCell() const;
  void				draw(sf::RenderWindow &);
  void				move(MOVE);
  void				zoom(ZOOM);
  void				redraw();
  void				update_cell(int, int, std::array<int, 7> const &);
  bool				is_init() const;
  Map				&operator()(Egg &, std::vector<sf::Vertex> &);
  Map				&operator()(std::vector<sf::Vertex> const &, sf::RenderStates const &);
  Map				&operator>>(sf::RenderWindow &);
  Map				&operator>>(Window &);
};

#endif // !MAP_HPP_
