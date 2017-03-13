//
// Team.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun 16 13:29:56 2015 jordan sabbah
// Last update Sat Jun 20 16:50:13 2015 jordan sabbah
//

#ifndef TEAM_HPP_
# define TEAM_HPP_

# include <string>
# include <array>
# include "Error.hpp"

class Team {
public:
  enum Color {
    RED,
    BLUE,
    GREEN,
    YELLOW
  };
private:
  typedef std::pair<std::string, int>		pair;
  static std::array<pair, 4>			_names;
  Color						_id;
  Team &operator=(Team const &);
  public:
  Team();
  Team(std::string const &name);
  Team(Team const &);
  ~Team();
  Team::Color					get_id() const;
  std::string const				&get_name() const;
  void						set_id(std::string const &);
};

#endif // !TEAM_HPP_
