//
// Parser.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jul  4 01:27:03 2015 jordan sabbah
// Last update Sat Jul  4 01:46:01 2015 jordan sabbah
//

#ifndef PARSER_HPP_
# define PARSER_HPP

# include <vector>
# include <string>

class Parser{
private:
  std::vector<std::string>	_args;
  int				_port;
  std::string			_host;
public:
  Parser(int ac, char **av);
  ~Parser();
  std::string const		&get_host();
  int				get_port();
};

#endif // !PARSER_HPP_
