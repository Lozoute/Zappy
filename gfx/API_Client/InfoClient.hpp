//
// InfoClient.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jul  3 03:22:19 2015 jordan sabbah
// Last update Sun Jul  5 14:12:33 2015 jordan sabbah
//

#ifndef INFOCLIENT_HPP_
# define INFOCLIENT_HPP_

#include <array>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <string>

class Window;
class IGameEngine;

class InfoClient{
private:
  int					_teamId;
  std::array<int, 8>			_lvls;
  IGameEngine				&_game;
  int					_nbTeam;
  sf::Font				_font;
  sf::Text				_number;
  sf::Text				_teamName;
  sf::RenderTexture			_texture;
  sf::Sprite				_sprite;
  bool					_switch;
  bool					_start;
  std::string				_winner;
  std::string				toString(int) const;
  bool					is_newInfo(std::array<int, 8> const &) const;
  void					store_newInfo(std::array<int, 8> const &);
  void					print_info(std::array<int, 8> const &);
  void					print_winner();
public:
  InfoClient(IGameEngine &);
  ~InfoClient();
  void					switch_team();
  void					draw_info(Window &);
  void					set_winner(std::string const &);
};


#endif // !INFOCLIENT_HPP_
