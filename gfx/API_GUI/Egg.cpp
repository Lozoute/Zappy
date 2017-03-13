//
// Egg.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 20 19:31:48 2015 jordan sabbah
// Last update Sun Jul  5 23:17:09 2015 jordan sabbah
//

#include "Egg.hpp"

sf::Texture	Egg::_texture;
bool		Egg::_textureInit = false;

Egg::Egg(int playerID, int posX, int posY, int delay)
  : _id(-42), _playerId(playerID), _posX(posX), _posY(posY),
    _initSprite(false), _type(FORK), _pos(0, 0), _delay(delay)
{
  for (int i = 0; i < 3; ++i){
    _eggType[i] = sf::IntRect(i * 27, 0, 27, 34);
  }
  _eggType[3] = sf::IntRect(81, 0, 51, 70);
  if (!_textureInit)
    _textureInit = _texture.loadFromFile("gfx/API_GUI/source/my_eggs.png");
}

Egg::~Egg(){
}

Egg::Egg(Egg const &other)
  : _id(other._id), _playerId(other._playerId), _posX(other._posX), _posY(other._posY),
    _initSprite(other._initSprite), _type(other._type), _eggType(other._eggType),
    _pos(other._pos), _delay(other._delay)
{
}

Egg	&Egg::operator=(Egg const &){
  throw Error("should not have called this function", "operator=(Egg const &)");
  return *this;
}

int	Egg::get_posX() const{
  return _posX;
}

int	Egg::get_posY() const{
  return _posY;
}

int	Egg::get_id() const{
  return _id;
}

int	Egg::get_playerId() const{
  return _playerId;
}

void	Egg::hatchEgg(){
  _type = HATCH;
}

void	Egg::newEgg(int id){
  _id = id;
  _type = NEW;
}

void	Egg::deadEgg(){
  _type = DEAD;
}

Egg	&Egg::operator()(std::vector<sf::Vertex> &posVect, sf::IntRect const &size){
  if (_delay <= -60 || (_delay > 0 && _delay--))
    return *this;
  if (!_initSprite){
    sf::Vector2u const &textSize = _texture.getSize();
    _pos.x = size.left + std::rand() % (size.width - textSize.x / 7);
    _pos.y = size.top;
    _initSprite = !_initSprite;
  }
  sf::IntRect const &egg = _eggType[_type];
  int	tab[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_pos.x + egg.width * tab[i],
			  _pos.y + egg.height * tab[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(egg.left + egg.width * tab[i],
			 egg.top + egg.height * tab[(i > 0) ? (i - 1) : 3]);
    posVect.push_back(sf::Vertex(posCoord, posText));
  }
  _delay -= (_type == DEAD) ? 1 : 0;
  return *this;
}


sf::Texture *Egg::get_texture(){
  return &_texture;
}


bool	Egg::is_dead() const{
  return _type == DEAD && _delay <= -60;
}
