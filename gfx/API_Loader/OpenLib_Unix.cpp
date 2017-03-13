//
// OpenLib_Unix.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 15:58:50 2015 jordan sabbah
// Last update Wed Jun 10 01:16:35 2015 jordan sabbah
//

#include "OpenLib_Unix.hpp"

OpenLib::OpenLib(std::string const &name)
  : _name(name), _libHandle(NULL)
{
  dlerror();
  if (!(_libHandle = dlopen(name.c_str(), RTLD_LAZY)))
    throw Error(dlerror(), "OpenLib(std::string const &)");
}

OpenLib::~OpenLib(){
  dlclose(_libHandle);
}

bool OpenLib::is_sym(std::string const &name) const{
  for (std::list<pair>::const_iterator it = _syms.begin(); it != _syms.end(); ++it){
    if (it->first == name)
      return true;
  }
  return false;
}

void	*&OpenLib::get_sym(std::string const &name){
  std::list<pair>::iterator it;
  for (it = _syms.begin(); it != _syms.end(); ++it){
    if (it->first == name)
      return (it->second);
  }
  push_sym(name);
  return _syms.back().second;
}

void	OpenLib::push_sym(std::string const &name){
  char	*error = NULL;
  void	*tmp_handler = NULL;

  tmp_handler = dlsym(_libHandle, name.c_str());
  if (!tmp_handler || error)
    throw Error(error, "void push_sym(std::string const &)");
  _syms.push_back(pair(name, tmp_handler));
}

std::string const	&OpenLib::get_name() const{
  return _name;
}
