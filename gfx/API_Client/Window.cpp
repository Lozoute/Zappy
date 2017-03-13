//
// Window.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 12:25:29 2015 jordan sabbah
// Last update Sun Jul  5 08:47:20 2015 jordan sabbah
//


#include "API_Mutex.hpp"
#include "ScopedLock.hpp"
#include "Window.hpp"

Window::Window(int sizeX, int sizeY, std::string const &name)
  : _window(sf::VideoMode(sizeX, sizeY), name.c_str()),
    _name(name), _quit(false)
{
  _sizeX = sizeX;
  _sizeY = sizeY;
  _window.clear();
  _window.setFramerateLimit(60);
  if (!_texture.loadFromFile("gfx/API_GUI/source/GUI.png"))
    std::cerr << "error openning texture GUI.png" << std::endl;
  _sprite.setTexture(_texture);
  _window.draw(_sprite);
  _window.display();
}

Window::~Window(){
  if (!_window.isOpen())
    throw Error("window should be open", "Window::~Window()");
  _window.close();
}

Window &Window::operator=(Window const &){
  throw Error("this function should not be called upon",
	      "Window &Window::operator=(Window const &)");
  return *this;
}

Window::Window(Window const &other)
  :  _window(sf::VideoMode(other._sizeX, other._sizeY), other._name.c_str()),
     _name(other._name), _quit(false)
{
  _sizeX = other._sizeX;
  _sizeY = other._sizeY;
}

void	Window::draw(sf::Sprite const &sprite){
  try
    {
      _window.draw(sprite);
    }
  catch (std::exception &e)
    {
      throw Error(e.what(), "void Window::draw(sf::Sprite const &)");
    }
}

void	Window::clear(){
  try
    {
      _window.clear();
      _window.draw(_sprite);
    }
  catch (std::exception &e)
    {
      throw Error(e.what(), "void Window::clear()");
    }
}

void	Window::display(){
  try
    {
      _window.display();
    }
  catch (std::exception &e)
    {
      throw Error(e.what(), "void Window::display()");
    }
}

Window::Event	Window::event_handler(){
  sf::Event	event;

  if (!_window.pollEvent(event))
    return None;
  if (is_escp(event) && (_quit = true))
    return Close;
  if (is_wheel(event))
    return (static_cast<Event>(Event::WheelUp + 0.5f - (event.mouseWheel.delta / 2.0f)));
  if (is_pressed(event))
    return (static_cast<Event>(event.key.code - sf::Keyboard::Left));
  if (event.type == sf::Event::KeyPressed && event.key.code >= sf::Keyboard::F1)
    return Window::Event::Switch;
  return (None);
}

Window	&Window::operator<<(sf::Sprite const &sprite){
  _window.draw(sprite);
  return *this;
}

Window	&Window::operator<<(sf::Text const &text){
  _window.draw(text);
  _window.display();
  return *this;
}

bool	Window::is_quit(){
  ScopedLock lock(_mutex);
  return _quit;
}

void	Window::quit(){
  ScopedLock lock(_mutex);
  _quit = true;
}

bool	Window::is_wheel(sf::Event &event){
  return (event.type == sf::Event::MouseWheelMoved);
}

bool	Window::is_escp(sf::Event &event){
  return (event.type == sf::Event::Closed ||
	  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape));
}

bool	Window::is_pressed(sf::Event &event){
  return (event.type == sf::Event::KeyPressed &&
	  event.key.code >= sf::Keyboard::Left &&
	  event.key.code <= sf::Keyboard::Down);
}
