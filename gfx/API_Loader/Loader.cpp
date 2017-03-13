//
// Loader.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 00:11:43 2015 jordan sabbah
// Last update Sun Jun 21 15:00:23 2015 jordan sabbah
//

#include "Loader.hpp"

Loader::Loader(Loader const &){
  throw Error("this function should not have been called", "Loader(Loader const &)");
}

Loader		&Loader::operator=(const Loader &){
  throw Error("this function should not have been called", "Loader &operator=(const Loader &)");
}

Loader::Loader()
{
}


Loader::~Loader(){
  clean_instance();
  clean_openLibs();
}

OpenLib	*&Loader::get_openLib(std::string const &name){
  for (std::list<OpenLib *>::iterator it = _openLibs.begin(); it != _openLibs.end(); ++it){
    if ((*it)->get_name() == name)
      return *it;
  }
  _openLibs.push_back(new OpenLib(name));
  return _openLibs.back();
}

void	Loader::clean_instance(){
  if (_instance.empty())
    return ;
  for (std::list<AInstance *>::iterator it = _instance.begin(); it != _instance.end(); ++it){
    delete *it;
  }
  _instance.clear();
}

void	Loader::clean_openLibs(){
  if (_openLibs.empty())
    return ;
  for (std::list<OpenLib *>::iterator it = _openLibs.begin(); it != _openLibs.end(); ++it){
    delete *it;
  }
  _openLibs.clear();
}
