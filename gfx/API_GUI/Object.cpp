//
// Object.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 13 21:30:42 2015 jordan sabbah
// Last update Sun Jul  5 08:45:42 2015 jordan sabbah
//

#include "Object.hpp"

sf::Texture	Object::_texture;
bool		Object::_init = false;

Object::Object(Type name) :_name(name){
  if (!_init)
    _init = _texture.loadFromFile("gfx/API_GUI/source/on_top_map.png");
  _quantity = 0;
  _initSprite = false;
  std::srand(std::time(NULL));
}

Object::Object(Type name, int quantity) : _name(name){
  if (!_init)
    _init = _texture.loadFromFile("gfx/API_GUI/source/on_top_map.png");
  _quantity = quantity;
  _initSprite = false;
  std::srand(std::time(NULL));
}

Object::~Object(){
}

Object &Object::operator=(Object const &other){
  if (_name != other._name)
    return *this;
  _quantity = other._quantity;
  _initSprite = other._initSprite;;
  return *this;
}


Object::Object(Object const &other) : _name(other._name){
  _quantity = other._quantity;
  _initSprite = other._initSprite;
  std::srand(std::time(NULL));
}

int	Object::get_quantity() const{
  return _quantity;
}

Object::Type	Object::get_type() const{
  return _name;
}

void	Object::update_quantity(int update){
  if (update < 0)
    throw Error("invalid quantity argument", "update_quantity(int)");
  if (!_quantity && update)
    _initSprite = false;
  _quantity = update;
}

sf::Texture	*Object::get_texture(){
  return &_texture;
}

Object	&Object::operator()(std::vector<sf::Vertex> &spriteObj, sf::IntRect const &size){
  if (!_quantity)
    return *this;
  sf::IntRect sizeObj(17 * _name, 0, 16, 16);
  if (!_initSprite){
    sf::Vector2u const &textSize = _texture.getSize();
    _position.x = size.left + std::rand() % (size.width - textSize.x / 7);
    _position.y = size.top + std::rand() % (size.height - textSize.y);
    _initSprite = !_initSprite;
  }
  int	tab[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_position.x + sizeObj.width * tab[i],
			  _position.y + sizeObj.height * tab[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(sizeObj.left + sizeObj.width * tab[i],
			 sizeObj.top + sizeObj.height * tab[(i > 0) ? (i - 1) : 3]);
    spriteObj.push_back(sf::Vertex(posCoord, posText));
  }
  return *this;
}
