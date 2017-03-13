//
// Player.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Thu Jun 11 23:53:03 2015 jordan sabbah
// Last update Fri Jul  3 03:34:22 2015 jordan sabbah
//

#include "Player.hpp"

Player::Player(int id, int x, int y, Orientation o, int lvl, std::string const &name)
  : _id(id), _team(name)
{
  _posX = x;
  _posY = y;
  _lvl = lvl;
  _orientation = o;
}

Player::Player(Player const &other) : _id(other._id), _team(other._team){
  _posX = other._posX;
  _posY = other._posY;
  _lvl = other._lvl;
  _orientation = other._orientation;
}

Player::~Player(){

}

Player &Player::operator=(Player const &){
  throw std::runtime_error("should not have called operator= on Player");
  return (*this);
}

int	Player::get_posX() const{
  return _posX;
}

int	Player::get_posY() const{
  return _posY;
}

int	Player::get_lvl() const{
  return _lvl;
}

int	Player::get_id() const{
  return _id;
}

Orientation	Player::get_orientation() const{
  return _orientation;
}

std::string const &Player::get_teamName() const{
  return _team;
}

void	Player::lvl_up(){
  _lvl++;
}

void	Player::set_lvl(int lvl){
  _lvl = lvl;
}

void	Player::set_posX(int x){
  _posX = x;
}

void	Player::set_posY(int y){
  _posY = y;
}

void	Player::set_inventory(std::array<int, 7> const &inventory){
  _inventory = inventory;
}

void	Player::turn_right(){
  _orientation = (_orientation > NORTH) ? static_cast<Orientation>(_orientation - 1) : WEST;
}

void	Player::turn_left(){
  _orientation = (_orientation < WEST) ? static_cast<Orientation>(_orientation + 1) : NORTH;
}

void	Player::move(){
  int	tab[] = {1, 1, -1, -1};
  int	delta = tab[_orientation - 1];

  (_orientation % 2 == 0) ? _posX += delta : _posY += delta;
}

bool	Player::is_position(int x, int y){
  return (_posX == x && _posY == y);
}

void	Player::put_toInventory(int res){
  if (res < 0 || res > 7)
    throw Error("invalid ressource to add", "void put_toInventory(int)");
  _inventory[res]++;
}

void	Player::put_outOfInventory(int res){
  if (res < 0 || res > 7)
    throw Error("invalid ressource to add", "void put_toInventory(int)");
  _inventory[res]--;
}
