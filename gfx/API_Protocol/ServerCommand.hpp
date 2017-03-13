//
// ServerCommand.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 01:48:56 2015 jordan sabbah
// Last update Sat Jul  4 15:12:52 2015 jordan sabbah
//

#ifndef SERVERCOMMAND_HPP_
# define SERVERCOMMAND_HPP_

# include <iostream>
# include <sstream>
# include <array>
# include "Error.hpp"
# include "IServerCommand.hpp"

class ServerCommand : public IServerCommand{
public:
  std::string					_info;
  IServerCommand::Command			_command;
  std::vector<std::string>			_params;
  std::string					_response;
  IServerCommand::Command			find_command(std::string const &);
  bool						check_paramsNumber(Command, int) const;
public:
  ServerCommand();
  ServerCommand(std::string const &);
  ServerCommand(ServerCommand const &);
  ServerCommand					&operator=(ServerCommand const &);
  virtual ~ServerCommand(){
    _params.clear();
  }
  virtual void					set_info(std::string const &);
  virtual IServerCommand::Command		get_command() const;
  virtual std::string const			&get_response() const;
  virtual std::vector<std::string> const	&get_params() const;
  virtual int					to_Int(std::string const &) const;
  virtual Orientation				to_Orientation(std::string const &) const;
  virtual std::string	const			&to_String(std::string const &) const;
  virtual std::string const			&get_info() const;
};

#endif // !SERVERCOMMAND_HPP_
