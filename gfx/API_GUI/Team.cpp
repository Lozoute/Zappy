//
// Team.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun 16 13:29:53 2015 jordan sabbah
// Last update Mon Jun 22 21:42:08 2015 jordan sabbah
//

# include "Team.hpp"

std::array<std::pair<std::string, int>, 4>	Team::_names;

Team::Team(){
  _id = Color::RED;
}

Team::Team(std::string const &name){
  for (std::array<pair, 4>::iterator it = _names.begin(); it != _names.end(); ++it){
    if (it->first == name)
      throw Error("Team already exists with that name", "Team(std::string const &name)");
  }
  int	i = 0;
  for (std::array<pair, 4>::iterator it = _names.begin(); it != _names.end(); ++it){
    if (it->second == 0){
      _names[i].first = name;
      _id = static_cast<Color>(i);
      return ;
    }
    ++i;
  }
  throw Error("too many teams created", "Team(std::string const &name)");
}

Team::Team(Team const &other){
  _id = other._id;
}

Team	&Team::operator=(Team const &){
  throw Error("should not call this function", "Team &operator=(Team const &)");
  return *this;
}

Team::~Team(){
  if (_names[_id].second-- == 0)
    _names[_id].first = "";
}

void	Team::set_id(std::string const &name){
  int	i = 0;
  for (std::array<pair, 4>::iterator it = _names.begin(); it != _names.end(); ++it){
    if (it->first == name){
      it->second++;
      _id = static_cast<Color>(i);
      return ;
    }
  }
  // throw Error("unknown team", "void set_id(std::string const &)");
}

std::string const &Team::get_name() const{
  return _names[_id].first;
}

Team::Color	Team::get_id() const{
  return _id;
}
