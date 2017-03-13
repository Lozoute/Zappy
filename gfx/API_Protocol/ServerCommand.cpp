//
// ServerCommand.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 01:48:50 2015 jordan sabbah
// Last update Sun Jul  5 00:28:18 2015 jordan sabbah
//

#include "ServerCommand.hpp"

ServerCommand::ServerCommand(){
}

ServerCommand::ServerCommand(std::string const &data) : _info(data){
  std::size_t pos = 0;
  if ((pos = data.find_first_of(" \n", pos)) == std::string::npos)
    throw Error("invalid argument", "ServerCommand(std::string const &)");
  _command = find_command(data.substr(0, pos));
  while (pos < data.size() - 1 && pos != std::string::npos){
    std::size_t next_pos = data.find_first_of(' ', pos + 1);
    _params.push_back(data.substr(pos + 1, next_pos - pos - 1));
    pos = next_pos;
  }
  if (!check_paramsNumber(_command, _params.size()))
    throw Error("invalid paramaters number", "ServerCommand(std::string const &)");
}

void	ServerCommand::set_info(std::string const &data){
  _info = data;
  std::size_t pos = 0;
  if ((pos = data.find_first_of(" \n", pos)) == std::string::npos)
    throw Error("invalid argument", "set_info(std::string const &)");
  _command = find_command(data.substr(0, pos));
  while (pos < data.size() - 1 && pos != std::string::npos){
    std::size_t next_pos = data.find_first_of(' ', pos + 1);
    _params.push_back(data.substr(pos + 1, next_pos - pos - 1));
    pos = next_pos;
  }
  if (!check_paramsNumber(_command, _params.size()))
    throw Error("invalid paramaters number", "set_info(std::string const &)");
}

IServerCommand::Command		ServerCommand::find_command(std::string const &param){
  std::array<char const *, 26> tab = {"BIENVENUE", "msz", "bct", "tna", "pnw", "ppo", "plv",
				      "pin", "pex", "pbc", "pic", "pie", "pfk", "pdr", "pgt",
				      "pdi", "enw", "eht", "ebo", "edi", "sgt", "seg", "smg", "suc",
				      "sbp", "sst"};
  int i = 0;
  for (std::array<char const *, 26>::iterator it = tab.begin(); it != tab.end(); ++it){
    if (param == *it)
      return static_cast<Command>(i);
    ++i;
  }
  return SUC;
}

bool		ServerCommand::check_paramsNumber(Command command, int number) const{
  std::array<int, 26> tab = {0, 2, 9, 1, 6, 4, 2, 10, -1, -1, -1, 3,
			     1, 2, 2, 1, 4, 1, 1, 1, 1, 1, -1, 0, 0, 1};

  if (tab[command] != -1 && tab[command] != number)
    return false;
  return true;
}

ServerCommand::ServerCommand(ServerCommand const &other){
  _info = other._info;
  _command = other._command;
  _params = other._params;
  _response = other._response;
}

ServerCommand &ServerCommand::operator=(ServerCommand const &other){
  _info = other._info;
  _command = other._command;
  _params = other._params;
  _response = other._response;
  return *this;
}

std::vector<std::string> const &ServerCommand::get_params() const{
  return _params;
}

IServerCommand::Command ServerCommand::get_command() const{
  return _command;
}

std::string const  &ServerCommand::get_response() const{
  return _response;
}

std::string const &ServerCommand::get_info() const{
  return _info;
}

int		ServerCommand::to_Int(std::string const &param) const{
  std::istringstream	iss(param);

  int ret;
  iss >> ret;
  return ret;
}

Orientation	ServerCommand::to_Orientation(std::string const &param) const{
  std::istringstream	iss(param);

  int ret;
  iss >> ret;
  return static_cast<Orientation>(ret);
}

std::string const	&ServerCommand::to_String(std::string const &param) const{
  return param;
}

extern "C"
{
  ServerCommand *get_ServerCommand(std::string const &data){
    return new ServerCommand(data);
  }
  ServerCommand *get_Command(){
    return new ServerCommand;
  }
}
