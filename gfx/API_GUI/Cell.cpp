//
// Cell.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 13 01:13:59 2015 jordan sabbah
// Last update Sun Jul  5 08:45:28 2015 jordan sabbah
//

#include "Cell.hpp"

sf::Texture	Cell::_texture;
bool		Cell::_init = false;

Cell::Cell()
  : _posX(0), _posY(0),
    _inventory({Object(Object::Type::Food), Object(Object::Type::Linemate),
	  Object(Object::Type::Deraumiere), Object(Object::Type::Sibur),
	  Object(Object::Type::Mendiane), Object(Object::Type::Phiras),
	  Object(Object::Type::Thystame)}),
    _size(65, 64)
{
  std::srand(std::time(NULL));
  if (!_init)
    _init = _texture.loadFromFile("gfx/API_GUI/source/cell.png");
}

Cell::Cell(int x, int y)
  : _inventory({Object(Object::Type::Food), Object(Object::Type::Linemate),
	Object(Object::Type::Deraumiere), Object(Object::Type::Sibur),
	Object(Object::Type::Mendiane), Object(Object::Type::Phiras),
	Object(Object::Type::Thystame)}), _size(65, 64)
{
  if (!_init)
    _init = _texture.loadFromFile("gfx/API_GUI/source/cell.png");
  std::srand(std::time(NULL));
  set_pos(x, y);
}

void	Cell::set_pos(int x, int y){
  _posX = x;
  _posY = y;
  int	nb = std::rand() %  200;
  int	tab[] = {50, 80, 90, 190};
  _id = 2;
  for (int i = 0; i < 4; ++i){
    if (nb > tab[i])
      _id = i;
  }
  _winPos = sf::Vector2u(_posX * _size.x,
  			 _posY * _size.y);
}

Cell::Cell(Cell const &other)
  : _inventory({Object(Object::Type::Food), Object(Object::Type::Linemate),
	Object(Object::Type::Deraumiere), Object(Object::Type::Sibur),
	Object(Object::Type::Mendiane), Object(Object::Type::Phiras),
	Object(Object::Type::Thystame)}),
    _size(65, 64)
{
  for (int i = 0; i < 7; ++i)
    _inventory[i].update_quantity(other._inventory[i].get_quantity());
  _id = other._id;
  set_pos(other._posX, other._posY);
  _winPos = other._winPos;
}

Cell &Cell::operator=(Cell const &other){
  for (int i = 0; i < 7; ++i)
    _inventory[i].update_quantity(other._inventory[i].get_quantity());
  _id = other._id;
  set_pos(other._posX, other._posY);
  _winPos = other._winPos;
  return (*this);
}

Cell:: ~Cell(){
}

sf::Vector2u const	&Cell::get_winPos() const{
  return _winPos;
}

int	Cell::get_posX() const{
  return _posX;
}

int	Cell::get_posY() const{
  return _posY;
}

sf::Vector2u const Cell::get_textureSize() const{
  return _size;
}

sf::Texture	*Cell::get_texture(){
  return &_texture;
}

void	Cell::get_cell(std::vector<sf::Vertex> &spriteCell){
  int	tab[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_winPos.x + _size.x * tab[i],
			  _winPos.y + _size.y * tab[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(_id * _size.x + _size.x * tab[i],
			 _size.y * tab[(i > 0) ? (i - 1) : 3]);
    spriteCell.push_back(sf::Vertex(posCoord, posText));
  }
}

void	Cell::get_inventory(std::vector<sf::Vertex> &spriteObj){
  sf::IntRect rect(_winPos.x, _winPos.y, _size.x, _size.y);
  for (std::array<Object, 7>::iterator it = _inventory.begin(); it != _inventory.end(); ++it){
    (*it)(spriteObj, rect);
  }
}

Cell	&Cell::operator()(std::vector<sf::Vertex> &spriteCell, std::vector<sf::Vertex> &spriteObj){
  int	tab[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_winPos.x + _size.x * tab[i],
			  _winPos.y + _size.y * tab[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(_id * _size.x + _size.x * tab[i],
			 _size.y * tab[(i > 0) ? (i - 1) : 3]);
    spriteCell.push_back(sf::Vertex(posCoord, posText));
  }
  sf::IntRect rect(_winPos.x, _winPos.y, _size.x, _size.y);
  for (std::array<Object, 7>::iterator it = _inventory.begin(); it != _inventory.end(); ++it){
    (*it)(spriteObj, rect);
  }
  return *this;
}

std::ostream	&operator<<(std::ostream &os, Cell const &cell){
  os << "cell(" << cell.get_posX() << ", " << cell.get_posY() << ")";
  return os;
}

void		Cell::update_object(Object::Type type, int value){
  if (type > 6 || type < 0)
    throw Error("invalid type argument", "update_object");
  _inventory[type].update_quantity(value);
}

void		Cell::update_inventory(std::array<int, 7> const &inventory){
  int		i = 0;
  for (std::array<Object, 7>::iterator it = _inventory.begin(); it != _inventory.end(); ++it){
    it->update_quantity(inventory[i]);
    i++;
  }
}
