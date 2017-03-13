//
// GameEngine.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Mon Jun 15 22:12:04 2015 jordan sabbah
// Last update Sun Jul  5 23:16:43 2015 jordan sabbah
//

#include "Egg.hpp"
#include "SpritePlayer.hpp"
#include "ScopedLock.hpp"
#include "API_Mutex.hpp"
#include "API_Thread.hpp"
#include "GameEngine.hpp"
#include "ServerCommand.hpp"

int	GameEngine::_speed = 100;

bool GameEngine::get_end(){
  ScopedLock	lock(_mutex);
  return _end;
}
void	GameEngine::end(){
  ScopedLock	lock(_mutex);
  _end = true;
}

GameEngine::GameEngine()
  : _init(false), _end(false), _endSprite(NULL)
{
  _moving = 0;
  _selectTeam = 0;
  std::srand(std::time(NULL));
  _team.push_back("");
}

GameEngine::GameEngine(int x, int y)
  :_init(true), _map(x, y), _end(false), _endSprite(NULL)
{
  _moving = 0;
  _selectTeam = 0;
  std::srand(std::time(NULL));
  _team.push_back("");
}

GameEngine::~GameEngine(){
  if (_endSprite)
    delete _endSprite;
}

GameEngine::GameEngine(GameEngine const &)
  :_init(true), _map(10, 10), _end(false), _endSprite(NULL)
{
  std::srand(std::time(NULL));
  throw Error("should not have called this function", "GameEngine(GameEngine const &)");
}

GameEngine &GameEngine::operator=(GameEngine const &){
  throw Error("should not have called this function", "GameEngine &operator=(GameEngine const &)");
}

void		GameEngine::clear_players(){
  ScopedLock	lock(_mutex);
  for (std::list<SpritePlayer *>::iterator it =_players.begin(); it != _players.end(); ++it){
    delete *it;
  }
  _players.clear();
}

void		GameEngine::clear_teams(){
  ScopedLock	lock(_mutex);
  _team.clear();
}

SpritePlayer	*GameEngine::find_player(int id){
  ScopedLock	lock(_mutex);
  for (std::list<SpritePlayer *>::iterator it = _players.begin(); it != _players.end(); ++it){
    if ((*it)->get_id() == id)
      return *it;
  }
  return NULL;
}

Egg	*GameEngine::find_egg(int id){
  ScopedLock	lock(_mutex);
  for (std::list<Egg *>::iterator it = _eggs.begin(); it != _eggs.end(); ++it){
    if ((*it)->get_id() == id)
      return *it;
  }
  return NULL;
}

void	GameEngine::delete_player(int id){
  ScopedLock	lock(_mutex);
  for (std::list<SpritePlayer *>::iterator it =_players.begin(); it != _players.end(); ++it){
    if ((*it)->get_id() == id){
      delete *it;
      _players.erase(it);
      return ;
    }
  }
}

void	GameEngine::delete_egg(int id){
  ScopedLock	lock(_mutex);
  for (std::list<Egg *>::iterator it =_eggs.begin(); it != _eggs.end(); ++it){
    if ((*it)->get_id() == id){
      delete *it;
      _eggs.erase(it);
      return ;
    }
  }
}

bool	GameEngine::check_end(Window &_window){
  if (_end){
    if (!_endSprite){
      _endTexture.loadFromFile("gfx/API_GUI/source/my_gameover.png");
      _endSprite = new sf::Sprite(_endTexture);
      _endSprite->setPosition(110, 170);
    }
    _window << *_endSprite;
    return false;
  }
  if(!_map.is_init())
    return false;
  return true;
}

void	GameEngine::drawGame(Window &_window){
  ScopedLock	lock(_mutex);
  if (!check_end(_window))
    return ;
  _map.redraw();
  sf::RenderStates states(Egg::get_texture());
  for (std::list<Egg *>::iterator it = _eggs.begin(); it != _eggs.end(); ++it)
    _map(*(*it), _spriteQueue);
  _map(_spriteQueue, states);
  _spriteQueue.clear();
  for (std::list<SpritePlayer *>::iterator it = _players.begin(); it != _players.end(); ++it)
    if (_team[_selectTeam] == (*it)->get_teamName())
      (**it)(_spriteQueue, _spriteQueueMsg);
  states.texture = SpritePlayer::get_texture();
  states.blendMode = sf::BlendAdd;
  _map(_spriteQueue, states);
  _spriteQueue.clear();
  for (std::list<SpritePlayer *>::iterator it = _players.begin(); it != _players.end(); ++it)
    if (_team[_selectTeam] != (*it)->get_teamName())
      (**it)(_spriteQueue, _spriteQueueMsg);
  states.blendMode = sf::BlendAlpha;
  _map(_spriteQueue, states);
  states.texture = Broadcast::get_texture();
  _map(_spriteQueueMsg, states);
  _map >> _window;
  _spriteQueue.clear();
  _spriteQueueMsg.clear();
}

void	GameEngine::bjr(ServerCommand *){
  std::cerr << "should not receive BIENVENUE command in GameEngine" << std::endl;
}

void	GameEngine::msz(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 2)
    throw Error("msz command missing argument", "GameEngine::msz(ServerCommand const *&)");
  int x = command->to_Int(params[0]);
  int y = command->to_Int(params[1]);
  if (x < 0 || y < 0)
    throw Error("Invalid Map size, (x > 0, y > 0)", "GameEngine::msz(ServerCommand const *&)");
  if (_init)
    return ;
  _map.init(x, y);
}

void	GameEngine::sgt(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("sgt command missing argument", "GameEngine::sgt(ServerCommand const *&)");
  if ((_speed = command->to_Int(params[0])) <= 100)
    return ;
  ServerCommand *task = new ServerCommand;
  task->set_info("sst 100\n");
  _queue.put(task);
}

void	GameEngine::bct(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 9)
    throw Error("bct command missing argument", "GameEngine::bct(ServerCommand const *&)");
  int x = command->to_Int(params[0]);
  int y = command->to_Int(params[1]);
  std::array<int, 7> inventory ={command->to_Int(params[2]), command->to_Int(params[3]),
				 command->to_Int(params[4]), command->to_Int(params[5]),
				 command->to_Int(params[6]), command->to_Int(params[7]),
				 command->to_Int(params[8])};
  if (x < 0 || y < 0)
    throw Error("Invalid Map size, (x > 0, y > 0)", "GameEngine::bct(ServerCommand const *&)");
  for (std::array<int, 7>::const_iterator it = inventory.begin(); it != inventory.end(); ++it){
    if (*it < 0)
      throw Error("Invalid inventory argument, can't be < 0", "GameEngine::bct(ServerCommand)");
  }
  _map.update_cell(x, y, inventory);
}

void    GameEngine::tna(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("tna command missing team name", "GameEngine::tna(ServerCommand *&)");
  std::string const &name = command->to_String(params[0]);
  ScopedLock	lock(_mutex);
  _team.push_back(name);
}

void	GameEngine::pnw(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 6)
    throw Error("pnw command missing arguments", "GameEngine::pnw(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int x = command->to_Int(params[1]);
  int y = command->to_Int(params[2]);
  if (x < 0 || y < 0)
    throw Error("invalid player coord, can't be < 0", "GameEngine::pnw(ServerCommand *&)");
  Orientation O = static_cast<Orientation>(command->to_Int(params[3]));
  int L = command->to_Int(params[4]);
  std::string const &name = command->to_String(params[5]);
  ScopedLock	lock(_mutex);
  _players.push_back(new SpritePlayer(id, x, y, O, L, name, _map));
}

void	GameEngine::ppo(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 4)
    throw Error("pnw command missing arguments", "GameEngine::pnw(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int x = command->to_Int(params[1]);
  int y = command->to_Int(params[2]);
  if (x < 0 || y < 0)
    throw Error("invalid player coord, can't be < 0", "GameEngine::pnw(ServerCommand *&)");
  Orientation O = static_cast<Orientation>(command->to_Int(params[3]));
  SpritePlayer *player = find_player(id);
  if (player)
    player->sendInstruction(x, y, O, _map);
}

void	GameEngine::pgt(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 2)
    throw Error("pgt command missing arguments", "GameEngine::pgt(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int res = command->to_Int(params[1]);
  if (res < 0 || res > 7)
    throw Error("invalid ressource to add", "GameEngine::pgt(IServerCommand)");
  SpritePlayer *player = find_player(id);
  if (player)
    player->put_toInventory(res);
}

void	GameEngine::pdr(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 2)
    throw Error("pdr command missing arguments", "GameEngine::pdr(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int res = command->to_Int(params[1]);
  if (res < 0 || res > 7)
    throw Error("invalid ressource to add", "GameEngine::pdr(IServerCommand)");
  SpritePlayer *player = find_player(id);
  if (player)
    player->put_outOfInventory(res);
}

void	GameEngine::pin(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 10)
    throw Error("pin command missing arguments", "GameEngine::pin(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int x = command->to_Int(params[1]);
  int y = command->to_Int(params[2]);
  std::array<int, 7> inventory = {command->to_Int(params[3]), command->to_Int(params[4]),
				  command->to_Int(params[5]), command->to_Int(params[6]),
				  command->to_Int(params[7]), command->to_Int(params[8]),
				  command->to_Int(params[9])};
  if (x < 0 || y < 0)
    throw Error("Invalid Map size, (x > 0, y > 0)", "GameEngine::bct(ServerCommand const *&)");
  SpritePlayer *player = find_player(id);
  if (player){
    player->set_posX(x);
    player->set_posY(y);
    player->set_inventory(inventory);
  }
}


void	GameEngine::pdi(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("pdr command missing arguments", "GameEngine::pdr(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  delete_player(id);
}

void	GameEngine::plv(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 2)
    throw Error("plv command missing arguments", "GameEngine::plv(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int lvl = command->to_Int(params[1]);
  SpritePlayer *player = find_player(id);
  if (player)
    player->set_lvl(lvl);
}

void	GameEngine::seg(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("seg command missing arguments", "GameEngine::seg(ServerCommand *&)");
  _winner = command->to_String(params[0]);
  clear_players();
  clear_teams();
  if (_end)
    return ;
  _end = true;
  _endTexture.loadFromFile("gfx/API_GUI/source/my_gameover.png");
  _endSprite = new sf::Sprite(_endTexture);
  _endSprite->setPosition(110, 170);
}

void	GameEngine::pfk(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("enw command missing arguments", "GameEngine::enw(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  SpritePlayer *player = find_player(id);
  if (player){
    int x = player->get_posX();
    int y = player->get_posY();
    ScopedLock	lock(_mutex);
    _eggs.push_back(new Egg(id, x, y, player->get_toDrawSize() / 4));
  }
}

void	GameEngine::enw(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 4)
    throw Error("enw command missing arguments", "GameEngine::enw(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  int playerId = command->to_Int(params[1]);
  int x = command->to_Int(params[2]);
  int y = command->to_Int(params[3]);
  if (x < 0 || y < 0)
    throw Error("invalid egg coord, can't be < 0", "GameEngine::enw(ServerCommand *&)");
  ScopedLock	lock(_mutex);
  for (std::list<Egg *>::iterator it = _eggs.begin(); it != _eggs.end(); ++it){
    if ((*it)->get_playerId() == playerId && (*it)->get_posX() == x && (*it)->get_posY() == y)
      (*it)->newEgg(id);
  }
}

void	GameEngine::eht(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("eht command missing egg id", "GameEngine::eht(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  Egg *egg = find_egg(id);
  if (egg)
    egg->hatchEgg();
}

void	GameEngine::ebo(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("eht command missing egg id", "GameEngine::eht(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  delete_egg(id);
}

void	GameEngine::edi(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 1)
    throw Error("eht command missing egg id", "GameEngine::eht(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  delete_egg(id);
}

void	GameEngine::pbc(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  if (params.size() < 2)
    throw Error("pbc missing arguments", "GameEngine::pbc(ServerCommand *&)");
  int id = command->to_Int(params[0]);
  std::string const &msg = command->to_String(params[1]);
  SpritePlayer *player = find_player(id);
  if (player)
    player->broadcast(msg);
}

void	GameEngine::pex(ServerCommand *command){
  std::vector<std::string> const &params = command->get_params();
  int id = command->to_Int(params[0]);
  SpritePlayer *player = find_player(id);
  if (player)
    player->expulse();
}

void	GameEngine::suc(ServerCommand *){
}

void	GameEngine::sbp(ServerCommand *){
}

void	GameEngine::smg(ServerCommand *){
}

//2 DERNIERES ANIMATIONS A CODER
void	GameEngine::pic(ServerCommand *){
  // std::cout << "pic(ServerCommand *) a coder" << std::endl;
}

void	GameEngine::pie(ServerCommand *){
  // std::cout << "pie(ServerCommand *) a coder" << std::endl;
}
//

void	GameEngine::move(Map::MOVE mvt){
  _map.move(mvt);
}

void	GameEngine::zoom(Map::ZOOM type){
  _map.zoom(type);
}

void    GameEngine::update(ServerCommand *command){
  Sptr tab[] = {
    &GameEngine::bjr, &GameEngine::msz, &GameEngine::bct, &GameEngine::tna,
    &GameEngine::pnw, &GameEngine::ppo, &GameEngine::plv, &GameEngine::pin,
    &GameEngine::pex, &GameEngine::pbc, &GameEngine::pic, &GameEngine::pie,
    &GameEngine::pfk, &GameEngine::pdr, &GameEngine::pgt, &GameEngine::pdi,
    &GameEngine::enw, &GameEngine::eht, &GameEngine::ebo, &GameEngine::edi,
    &GameEngine::sgt, &GameEngine::seg, &GameEngine::smg, &GameEngine::suc,
    &GameEngine::sbp};

  return (this->*tab[command->get_command()])(command);
}

int	GameEngine::is_moving() const{
  return _moving;
}

std::vector<std::string> const	&GameEngine::get_teamList() const{
  return _team;
}

void	GameEngine::count_playerLvl(int	teamId, std::array<int, 8> &lvls){
  ScopedLock lock(_mutex);
  if (_team.empty())
    return ;
  std::string const &name = _team[teamId];

  for (std::list<SpritePlayer *>::const_iterator it = _players.begin();
       it != _players.end(); ++it)
    {
      if ((*it)->get_teamName() == name)
	lvls[(*it)->get_lvl() - 1]++;
    }
}

int const	&GameEngine::get_speed() const{
  return _speed;
}

int const	&GameEngine::speed_game(){
  return _speed;
}

bool		GameEngine::is_pending(){
  return !_queue.empty();
}

ServerCommand		*GameEngine::get_pending(){
  return _queue.get();
}

std::string const	&GameEngine::get_winner() const{
  return _winner;
}

void	GameEngine::switch_team(){
  int	nbTeams = _team.size();
  if (!nbTeams)
    return ;
  _selectTeam = (_selectTeam == nbTeams - 1) ? 0 : _selectTeam + 1;
}

extern "C"
{
  IGameEngine	*__API_Load__(){
  return (new GameEngine);
  }
  IGameEngine	*get_engineXY(int x, int y){
    return (new GameEngine(x, y));
  }
}
