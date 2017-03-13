//
// Map.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jul  3 01:49:17 2015 jordan sabbah
// Last update Sun Jul  5 23:17:54 2015 jordan sabbah
//

#include "ScopedLock.hpp"
#include "Egg.hpp"
#include "SpritePlayer.hpp"
#include "Window.hpp"
#include "Map.hpp"

Map::Map() : _sizeX(-1), _sizeY(-1), _scale(1, 1), _origin(0, 0)
{
}

Map::Map(Map const &other)
  : _sizeX(other._sizeX), _sizeY(other._sizeY), _map(_sizeX * _sizeY), _scale(other._scale),
    _origin(0, 0)
{
}

Map::Map(int sizeX, int sizeY)
  : _sizeX(sizeX), _sizeY(sizeY), _map(sizeX * sizeY), _scale(1, 1), _origin(0, 0)
{
  init(sizeX, sizeY);
}

Map &Map::operator=(Map const &){
  throw Error("should not have called this function", "operator=(Map const &)");
  return *this;
}

void	Map::init(int x, int y){
  _map = std::vector<Cell>(x * y);
  sf::Vector2u const &size = _map[0].get_textureSize();
  _texture.create(size.x * x, size.y * y);
  for (int i = 0; i < x * y; ++i){
    _map[i].set_pos(i % x, i / x);
    _map[i].get_cell(_spriteCell);
  }
  _texture.display();
  set_view();
  set_sprite();
  _sizeX = x;
  _sizeY = y;
}

void	Map::redraw(){
  check_init();
  _texture.clear();
  sf::RenderStates states(Cell::get_texture());
  this->operator()(_spriteCell, states);
  for (int i = 0; i < _sizeX * _sizeY; ++i)
    _map[i].get_inventory(_spriteObj);
  states.texture = Object::get_texture();
  if (!_spriteObj.empty()){
    this->operator()(_spriteObj, states);
    _spriteObj.clear();
  }
  _texture.display();
  _sprite.setTexture(_texture.getTexture());
  _sprite.setTextureRect(_view);
  _sprite.setOrigin(_origin);
}

void	Map::set_view(){
  float Xmax = _texture.getSize().x * _scale.x;
  float Ymax = _texture.getSize().y * _scale.y;
  float Xmin = 0;
  float Ymin = 0;

  Xmin = (Xmax <= 800) ? 0 : (Xmax - 800) / 2;
  Ymin = (Ymax <= 600) ? 0 : (Ymax - 600) / 2;
  Xmax = (Xmax <= 800) ? Xmax : 800;
  Ymax = (Ymax <= 600) ? Ymax : 600;
  _view.left = Xmin;
  _view.top = Ymin;
  _view.width = Xmax / _scale.x;
  _view.height = Ymax / _scale.y;
}

void	Map::set_sprite(){
  int X = _texture.getSize().x * _scale.x;
  int Y = _texture.getSize().y * _scale.y;

  _sprite.setTexture(_texture.getTexture());
  _sprite.setTextureRect(_view);
  X = (X < 800) ? (800.0f - X) / 2 : 0;
  Y = (Y < 600) ? (600.0f - Y) / 2 : 0;
  _sprite.setPosition(X + 110, Y + 170);
}

Map::~Map(){
}

void	Map::check_init() const{
  if (_sizeX == -1 || _sizeY == -1)
    throw Error("map should be init first", "check_init");
}

int	Map::get_sizeX() const{
  return _sizeX;
}

int	Map::get_sizeY() const{
  return _sizeY;
}

bool	Map::is_init() const{
  return (_sizeX != -1 && _sizeY != -1);
}

sf::Vector2f const	Map::get_pos(int x, int y) const{
  check_init();
  sf::Vector2u const &pos = _map[y * _sizeX + x].get_winPos();
  return sf::Vector2f(pos.x, pos.y);
}

sf::Vector2f const Map::get_unitCell() const{
  check_init();
  sf::Vector2u const &unit = _map[0].get_textureSize();
  return sf::Vector2f(unit.x, unit.y);
}

void    Map::draw(sf::RenderWindow &window){
  check_init();
  window.draw(_sprite);
}

void	Map::move_left(){
  check_init();
  if (_view.left == 0)
    return ;
  _view.left = (_view.left - 10 <= 0) ? 0 : _view.left - 10;
  _sprite.setTextureRect(_view);
}

void	Map::move_right(){
  check_init();
  float x = _texture.getSize().x;
  float maxLeft = x - _view.width;
  if (_view.left == maxLeft)
    return ;
  _view.left = (_view.left + 10 >= maxLeft) ? maxLeft : _view.left + 10;

  _sprite.setTextureRect(_view);
}

void	Map::move_up(){
  check_init();
  if (_view.top == 0)
    return ;
  _view.top = (_view.top - 10 <= 0) ? 0 : _view.top - 10;
  _sprite.setTextureRect(_view);
}

void	Map::move_down(){
  check_init();
  float y = _texture.getSize().y;
  float maxTop = y - _view.height;
  if (_view.top == maxTop)
    return ;
  _view.top = (_view.top + 10 >= maxTop) ? maxTop : _view.top + 10;
  _sprite.setTextureRect(_view);
}

void	Map::move(MOVE move){
  check_init();
  fptr	tab[] = {&Map::move_left, &Map::move_right, &Map::move_up, &Map::move_down};

  if (move < 0 || move > 4)
    throw Error("invalid move", "move(MOVE)()");
  return (this->*tab[move])();
}

void    Map::update_cell(int posX, int posY, std::array<int, 7> const &inventory){
  check_init();
  int index = posY * _sizeX + posX;
  if (index < 0 || index > static_cast<int>(_map.size()))
    throw Error("invalid position", "update_cell(int posX, int posY, std::array<int, 7> const &inventory)");
  _map[index].update_inventory(inventory);
}

Map	&Map::operator>>(sf::RenderWindow &window){
  check_init();
  window.draw(_sprite);
  return *this;
}

Map	&Map::operator>>(Window &window){
  check_init();
  window << _sprite;
  return *this;
}

Map	&Map::operator()(Egg &egg, std::vector<sf::Vertex> &vectPos){
  check_init();
  int index = egg.get_posY() * _sizeX + egg.get_posX();
  sf::Vector2u const &pos = _map[index].get_winPos();
  sf::Vector2u const &size = _map[index].get_textureSize();
  egg(vectPos, sf::IntRect(pos.x, pos.y, size.x, size.y));
  return *this;
}

Map		&Map::operator()(std::vector<sf::Vertex> const &pos, sf::RenderStates const &states){
  if (!pos.empty())
    _texture.draw(&pos[0], pos.size(), sf::Quads, states);
  return *this;
}

void	Map::zoom(ZOOM type){
  return (type == ZOOM::In) ? zoomIn() : zoomOut();
}

void	Map::zoomIn(){
  if (_scale.x + 0.1 > 1 || _scale.y + 0.1 > 1)
    return ;
  _scale.x += 0.1;
  _scale.y += 0.1;
  _sprite.setScale(_scale);
  set_view();
  _sprite.setTextureRect(_view);
  set_sprite();
}

void	Map::zoomOut(){
  if ((_texture.getSize().x * _scale.x < 800.0f &&
       _texture.getSize().y * _scale.y < 600.0f) ||
      _scale.x - 0.1 <= 0 || _scale.y - 0.1 <= 0)
    return ;
  _scale.x -= 0.1;
  _scale.y -= 0.1;
  _sprite.setScale(_scale);
  set_view();
  _sprite.setTextureRect(_view);
  set_sprite();
}
