//
// IGameEngine.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 19:31:06 2015 jordan sabbah
// Last update Sun Jul  5 16:07:34 2015 jordan sabbah
//

#ifndef IGAME_ENGINE_HPP
# define IGAME_ENGINE_HPP

# include <memory>
# include "Map.hpp"
# include "Window.hpp"

class ServerCommand;

class Window;
class IGameEngine{
public:
  virtual ~IGameEngine(){}
  virtual void			update(ServerCommand *) = 0;
  virtual bool			get_end() = 0;
  virtual void			end() = 0;
  virtual void			drawGame(Window &) = 0;
  virtual void			move(Map::MOVE) = 0;
  virtual void			zoom(Map::ZOOM) = 0;
  virtual int			is_moving() const = 0;
  virtual void			count_playerLvl(int, std::array<int, 8> &) = 0;
  virtual std::vector<std::string> const	&get_teamList() const = 0;
  virtual int const		&get_speed() const = 0;
  virtual bool			is_pending() = 0;
  virtual ServerCommand		*get_pending() = 0;
  virtual std::string const	&get_winner() const = 0;
  virtual void			switch_team() = 0;
};

#endif // !IGAME_ENGINE_HPP
