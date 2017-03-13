//
// GameEngine.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Mon Jun 15 22:12:06 2015 jordan sabbah
// Last update Sun Jul  5 17:39:54 2015 jordan sabbah
//

#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# include <deque>
# include <vector>
# include <list>
# include <stdexcept>
# include <unistd.h>
# include "Map.hpp"
# include "IGameEngine.hpp"
# include "API_Mutex_C.hpp"
# include "SafeQueue.hpp"

class Egg;
class SpritePlayer;

class GameEngine : public IGameEngine{
private:
  typedef void			(SpritePlayer::*fptr)();
  typedef void			(GameEngine::*Sptr)(ServerCommand *);
  std::vector<sf::Vertex>	_spriteQueue;
  std::vector<sf::Vertex>	_spriteQueueMsg;
  std::list<SpritePlayer*>	_players;
  std::list<Egg *>		_eggs;
  std::vector<std::string>	_team;
  bool				_init;
  Map				_map;
  bool				_end;
  Mutex				_mutex;
  int				_moving;
  SafeQueue<ServerCommand *>	_queue;
  sf::Texture			_endTexture;
  sf::Sprite			*_endSprite;
  static int			_speed;
  std::string			_winner;
  int				_selectTeam;
  GameEngine(GameEngine const &);
  GameEngine			&operator=(GameEngine const &);
  SpritePlayer			*find_player(int);
  Egg				*find_egg(int);
  void			        clear_players();
  void				clear_teams();
  void				delete_player(int);
  void				delete_egg(int);
  void			        bjr(ServerCommand *);
  void			        msz(ServerCommand *);
  void			        sgt(ServerCommand *);
  void			        bct(ServerCommand *);
  void			        tna(ServerCommand *);
  void			        pnw(ServerCommand *);
  void			        ppo(ServerCommand *);
  void				pgt(ServerCommand *);
  void			        pdr(ServerCommand *);
  void			        pin(ServerCommand *);
  void				pdi(ServerCommand *);
  void			        pfk(ServerCommand *);
  void				plv(ServerCommand *);
  void				seg(ServerCommand *);
  void			        enw(ServerCommand *);
  void			        eht(ServerCommand *);
  void			        ebo(ServerCommand *);
  void			        edi(ServerCommand *);
  void				suc(ServerCommand *);
  void			        sbp(ServerCommand *);
  void			        smg(ServerCommand *);
  void			        pbc(ServerCommand *);
  void			        pex(ServerCommand *);
  void				pic(ServerCommand *);
  void				pie(ServerCommand *);
  bool				check_end(Window &);
public:
  GameEngine();
  GameEngine(int x, int y);
  ~GameEngine();
  virtual void		        update(ServerCommand *);
  virtual bool			get_end();
  virtual void			drawGame(Window &);
  virtual void			move(Map::MOVE);
  virtual void			zoom(Map::ZOOM);
  virtual void			end();
  virtual int			is_moving() const;
  virtual void			count_playerLvl(int, std::array<int, 8> &);
  virtual std::vector<std::string> const	&get_teamList() const;
  virtual int const		&get_speed() const;
  static int const		&speed_game();
  virtual bool			is_pending();
  virtual ServerCommand		*get_pending();
  virtual std::string const	&get_winner() const;
  virtual void			switch_team();
};

#endif // !GAMEENGINE_HPP_
