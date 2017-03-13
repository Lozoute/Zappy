//
// Window.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 12:25:32 2015 jordan sabbah
// Last update Sat Jul  4 05:00:10 2015 jordan sabbah
//

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

# include <iostream>
# include <string>
# include <utility>
# include <SFML/Graphics/Vertex.hpp>
# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Texture.hpp>
# include <SFML/Window/Event.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/System.hpp>
# include "Error.hpp"
# include "API_Mutex_C.hpp"

class Window{
public:
  enum Event{
    Left,
    Right,
    Up,
    Down,
    WheelUp,
    WheelDown,
    Switch,
    None,
    Close
  };
private:
  sf::RenderWindow	_window;
  int			_sizeX;
  int			_sizeY;
  std::string const	_name;
  sf::Texture		_texture;
  sf::Sprite		_sprite;
  bool			_quit;
  Mutex			_mutex;
  void			draw(sf::Sprite const &);
  bool			is_wheel(sf::Event &);
  bool			is_escp(sf::Event &);
  bool			is_pressed(sf::Event &);
public:
  Window(Window const &);
  Window &operator=(Window const &);
  Window(int sizeX = 1024, int sizeY = 972, std::string const &name = "zappy - Graphical Client");
  ~Window();
  void			clear();
  void			display();
  Event			event_handler();
  bool			is_quit();
  void			quit();
  Window		&operator<<(sf::Sprite const &);
  Window		&operator<<(sf::Text const &);
};


#endif // !WINDOW_HPP_
