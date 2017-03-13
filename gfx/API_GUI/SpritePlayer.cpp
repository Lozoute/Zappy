//
// SpritePlayer.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 12 11:05:14 2015 jordan sabbah
// Last update Sun Jul  5 23:18:32 2015 jordan sabbah
//

#include "Map.hpp"
#include "SpritePlayer.hpp"
#include "GameEngine.hpp"

sf::Texture			SpritePlayer::_texture;
bool				SpritePlayer::_textureInit = false;

SpritePlayer::SpritePlayer(int id, int x, int y, Orientation o,
			   int lvl, std::string const &name, Map const &map)
  : Player(id, x, y, o, lvl, name), _unit(map.get_unitCell())
{
  _textureInit = (!_textureInit) ? _texture.loadFromFile(_file.c_str()) : _textureInit;
  for (int i = 0; i < 12; ++i)
    _teamSprites[i] = sf::IntRect((i % 3) * 32 + (_lvl - 1) / 2 * 96,
				  i / 3 * 32, 32, 32);
  sf::Vector2f const &current = map.get_pos(_posX, _posY);
  _pos = sf::Vector2f(current.x + (_unit.x / 3), current.y + (_unit.y / 3));
}

void	SpritePlayer::moveSprite(){
  int	tab[] = {-1, -1, 1, 1};
  int	delta = tab[_orientation - 1];

  if (_orientation % 2 == 0){
    _posX += delta;
    _pos.x += delta * _unit.x;
    return ;
  }
  _posY += delta;
  _pos.y += delta * _unit.y;
}

SpritePlayer::~SpritePlayer(){
}

SpritePlayer::SpritePlayer(SpritePlayer const &other)
  : Player(other)
{
  _teamSprites = other._teamSprites;
}

SpritePlayer	&SpritePlayer::operator=(SpritePlayer const &){
  throw Error("should not have called this function",
	      "SpritePlayer &operator=(SpritePlayer const &)");
  return *this;
}

sf::Vertex const	&SpritePlayer::get_toDraw(){
  int	tab[] = {1, 4, 7, 10};
  if (_toDraw.empty())
    put_posPlayer(_pos, _teamSprites[tab[_orientation - 1]]);
  return _toDraw.front();
}

void			SpritePlayer::update_toDraw(){
  if (_toDraw.empty())
    throw Error("_toDraw is empty, can't pop elem",
		"void update_toDraw()");
  _toDraw.pop_front();
}

sf::Texture	*SpritePlayer::get_texture(){
  return &_texture;
}

void	SpritePlayer::put_posPlayer(sf::Vector2f const &pos, sf::IntRect const &player){
  int	tab[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(pos.x + player.width * tab[i],
			  pos.y + player.height * tab[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(player.left + player.width * tab[i],
			 player.top + player.height * tab[(i > 0) ? (i - 1) : 3]);
    _toDraw.push_back(sf::Vertex(posCoord, posText));
  }
}

void			SpritePlayer::moveSprite(int x, int y, Map const &map){
  float			deltaX = x - _posX;
  float			deltaY = y - _posY;

  float			X, Y;
  int			id;

  int			coef = 30 - 0.2 * GameEngine::speed_game();
  coef = (coef <= 0) ? 1 : coef;

  if (deltaX < -1 || deltaX > 1)
    deltaX /= -map.get_sizeX();
  if (deltaY < -1 || deltaY > 1)
    deltaY /= -map.get_sizeY();
  for (int i = 0; i < coef / 2; ++i){
    X = _pos.x + _unit.x * (deltaX * i / coef);
    Y = _pos.y + _unit.y * (deltaY * i / coef);
    id = i % 3 + (_orientation - 1) * 3;
    put_posPlayer(sf::Vector2f(X, Y), _teamSprites[id]);
  }
  sf::Vector2f next = sf::Vector2f(map.get_pos(x, y).x + _unit.x / 3,
				   map.get_pos(x, y).y + _unit.y / 3);
  for (int i = coef / 2; i >= 0; --i){
    sf::Sprite	pos(_texture);
    X = next.x + _unit.x * (-deltaX * i / coef);
    Y = next.y + _unit.y * (-deltaY * i / coef);
    id = i % 3 + (_orientation - 1) * 3;
    put_posPlayer(sf::Vector2f(X, Y), _teamSprites[id]);
  }
  _pos = next;
  _posX = x;
  _posY = y;
}

void			SpritePlayer::turnSprite(Orientation o){
  int	tab[] = {1, 4, 7, 10};
  _orientation = o;
  put_posPlayer(_pos, _teamSprites[tab[_orientation - 1]]);
}

void		SpritePlayer::sendInstruction(int x, int y,
						      Orientation o, Map const &map)
{
  if (o == _orientation)
    return (moveSprite(x, y, map));
  return (turnSprite(o));
}

void	SpritePlayer::broadcast(std::string const &msg){
  _broadcast.set_msg(msg, _toDraw.size() / 4);
}

void	SpritePlayer::expulse(){
  put_posPlayer(sf::Vector2f(_pos.x, _pos.y + _unit.y / 2), _teamSprites[7]);
  put_posPlayer(_pos, _teamSprites[7]);
}

int	SpritePlayer::get_toDrawSize() const{
   return _toDraw.size();
}

void	SpritePlayer::set_lvl(int new_lvl){
  if (new_lvl > _lvl){
    _lvl = new_lvl;
    for (int i = 0; i < 12; ++i)
      _teamSprites[i] = sf::IntRect((i % 3) * 32 + (_lvl - 1) * 96,
				    i / 3 *  32, 32, 32);
  }
}

SpritePlayer	&SpritePlayer::operator>>(std::vector<sf::Vertex>  &vect){
  int		tab[] = {1, 4, 7, 10};
  int		size = _toDraw.size();

  if (size > 0){
    for (int i = 0; i < 4 && i < size; ++i){
      vect.push_back(_toDraw.front());
      _toDraw.pop_front();
    }
    return *this;
  }
  sf::IntRect const &player= _teamSprites[tab[_orientation - 1]];
  int	tab1[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_pos.x + player.width * tab1[i],
			  _pos.y + player.height * tab1[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(player.left + player.width * tab1[i],
			 player.top + player.height * tab1[(i > 0) ? (i - 1) : 3]);
    vect.push_back(sf::Vertex(posCoord, posText));
  }
  return *this;
}

SpritePlayer	&SpritePlayer::operator()(std::vector<sf::Vertex> &vect, std::vector<sf::Vertex> &vectMsg)
{
  sf::IntRect   square(_pos.x, _pos.y, _teamSprites[_orientation - 1].width,
		       _teamSprites[_orientation - 1].height);
  int		tab[] = {1, 4, 7, 10};
  int		size = _toDraw.size();

  if (size > 0){
    for (int i = 0; i < 4 && i < size; ++i){
      vect.push_back(_toDraw.front());
      _toDraw.pop_front();
      _broadcast(vectMsg, square);
    }
    return *this;
  }
  sf::IntRect const &player= _teamSprites[tab[_orientation - 1]];
  int	tab1[] = {0, 1, 1, 0};
  for (int i = 0; i < 4; i++){
    sf::Vector2f posCoord(_pos.x + player.width * tab1[i],
			  _pos.y + player.height * tab1[(i > 0) ? (i - 1) : 3]);
    sf::Vector2f posText(player.left + player.width * tab1[i],
			 player.top + player.height * tab1[(i > 0) ? (i - 1) : 3]);
    vect.push_back(sf::Vertex(posCoord, posText));
  }
  _broadcast(vectMsg, square);
  return *this;
}


int	SpritePlayer::is_action() const{
  int	nb = _toDraw.size() / 4;
  int	msg = _broadcast.get_count();
  return ((nb < msg) ? msg : nb);
}
