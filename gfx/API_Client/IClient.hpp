//
// IClient.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 19:08:13 2015 jordan sabbah
// Last update Sat Jul  4 02:13:17 2015 jordan sabbah
//

#ifndef ICLIENT_HPP_
# define ICLIENT_HPP_

# include <string>

class IClient{
public:
  virtual ~IClient(){}
  virtual bool	connect(int, std::string const &) = 0;
  virtual void	display() = 0;
};

#endif // !ICLIENT_HPP_
