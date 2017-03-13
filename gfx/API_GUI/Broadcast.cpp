//
// Broadcast.cpp for $ in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 01:55:20 2015 jordan sabbah
// Last update Sat Jul  4 04:18:48 2015 jordan sabbah
//

#include "Broadcast.hpp"
#include "GameEngine.hpp"

sf::Texture	Broadcast::_texture;
bool		Broadcast::_textureInit = false;

Broadcast::Broadcast()
  : _counter(0), _ready(false), _delay(0)
{
  if (!_textureInit){
    _textureInit = _texture.loadFromFile(_file.c_str());
    _size = _texture.getSize();
  }
}

Broadcast::Broadcast(Broadcast const &other)
  : _counter(other._counter),  _msg(other._msg),
    _ready(other._ready), _size(other._size), _delay(other._delay)
{
}

Broadcast &Broadcast::operator=(Broadcast const &){
  throw Error("should not have called this function", "Broadcast &operator=(Broadcast &)");
  return *this;
}

Broadcast::~Broadcast(){
}

void	Broadcast::set_msg(std::string const &msg, int delay){
  _msg = msg;
  _ready = true;
  _delay = delay;
}

sf::Texture	*Broadcast::get_texture(){
  return &_texture;
}

Broadcast	&Broadcast::operator()(std::vector<sf::Vertex> &vect, sf::IntRect const &size){
  if (_delay > 0 && _delay--)
    return *this;
  int	coef = 30 - 0.2 * GameEngine::speed_game();
  coef = (coef <= 0) ? 1 : coef;
  if (!_ready || _counter > coef){
    _counter = 0;
    _ready = false;
    return *this;
  }
  int	posX = size.left - 5;
  int	posY = size.top - _size.y;
  int	tab1[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(posX + _size.x * tab1[i],
			  posY + _size.y * tab1[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(_size.x * tab1[i],
			 _size.y * tab1[(i > 0) ? (i - 1) : 3]);
    vect.push_back(sf::Vertex(posCoord, posText));
  }
  _counter++;
  return *this;
}

int	Broadcast::get_count() const{
  return _counter;
}
