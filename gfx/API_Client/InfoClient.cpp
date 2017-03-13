//
// InfoClient.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jul  3 03:22:15 2015 jordan sabbah
// Last update Sun Jul  5 20:21:35 2015 jordan sabbah
//

#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include "InfoClient.hpp"
#include "IGameEngine.hpp"
#include "Window.hpp"

InfoClient::InfoClient(IGameEngine &game)
  : _teamId(0), _game(game), _nbTeam(game.get_teamList().size()), _switch(true), _winner("")
{
  _lvls.fill(-1);
  _font.loadFromFile("gfx/API_GUI/source/FreeSansBold.ttf");
  _number.setFont(_font);
  _number.setCharacterSize(11);
  _number.setColor(sf::Color::White);
  std::vector<std::string> const &list = _game.get_teamList();
  if (!list.empty())
    _teamName.setString(list[_teamId]);
  _teamName.setFont(_font);
  _teamName.setCharacterSize(11);
  _teamName.setColor(sf::Color::White);
  _teamName.setPosition(5, 2);
  _texture.create(645, 145);
  _start = false;
}

InfoClient::~InfoClient(){
}

void	InfoClient::set_winner(std::string const &winner){
  _winner = winner;
}

void	InfoClient::switch_team(){
  _nbTeam = _game.get_teamList().size();
  _teamId = (_teamId == _nbTeam - 1) ? 0 : _teamId + 1;
  std::vector<std::string> const &list = _game.get_teamList();
  if (!list.empty())
    _teamName.setString(list[_teamId]);
  _switch = true;
  _lvls.fill(-1);
}

bool	InfoClient::is_newInfo(std::array<int, 8> const &info) const{
  for (int i = 0; i < 8; ++i){
    if (_lvls[i] != info[i])
      return true;
  }
  return false;
}

std::string	InfoClient::toString(int num) const{
  std::ostringstream oss;
  oss << num;
  return oss.str();
}

void	InfoClient::print_winner(){
  std::string winner("Winner :\n");
  _number.setString(winner + _winner);
  _number.setCharacterSize(22);
  _number.setPosition(454, 47);
  _texture.draw(_number);
  _number.setCharacterSize(11);
}

void	InfoClient::print_info(std::array<int, 8> const &lvls){
  for (int i = 0; i < 8; ++i){
    _lvls[i] = lvls[i];
    _number.setString(toString(lvls[i]));
    _number.setPosition(i % 4 * 60, 63 + i / 4 * 52);
    _texture.draw(_number);
  }
}

void	InfoClient::draw_info(Window &window){
  std::array<int, 8> lvls;
  lvls.fill(0);
  _game.count_playerLvl(_teamId, lvls);
  if (!_start &&!_game.get_teamList().empty() && (_start = true)){
    _teamName.setString((_game.get_teamList())[0]);
    _switch = true;
  }
  if (!is_newInfo(lvls) && !_switch && _winner == ""){
    window << _sprite;
    return ;
  }
  _texture.clear(sf::Color::Transparent);
  _texture.draw(_teamName);
  print_info(lvls);
  if (_winner != "")
    print_winner();
  _switch = false;
  _texture.display();
  _sprite.setTexture(_texture.getTexture());
  _sprite.setPosition(81, 803);
  window << _sprite;
}
