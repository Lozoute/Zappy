//
// OpenLib_Windows.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 16:55:11 2015 jordan sabbah
// Last update Wed Jun 10 00:53:50 2015 jordan sabbah
//

#include "OpenLib_Windows.hpp"


OpenLib::OpenLib(std::string const &name)
  : _name(name), _libHandle(NULL)
{
  if (!(_libHandle = LoadLibrary((name.c_str()))))
    throw Error("Windows LoadLibrary failed", "OpenLib(std::string const &)");
}

OpenLib::~OpenLib(){
  if (!FreeLibrary(_libHandle))
    throw Error("FreeLibrary", "Loader Windows");
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
  return _syms.back();
}

void	OpenLib::push_sym(std::string const &name){
  void	*tmp_handler = NULL;

  if (!(tmp_handler = GetProcAddress(_libHandle, name.c_str())))
    throw Error("Windows GetProcAddress failed", "void push_sym(std::string const &)");
  _syms.push_back(pair(name, tmp_handler));
}

std::string const	OpenLib::get_name() const{
  return _name;
}
