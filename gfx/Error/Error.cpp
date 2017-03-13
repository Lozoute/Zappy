//
// Error.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Socket
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun  7 12:50:26 2015 jordan sabbah
// Last update Sun Jun  7 12:59:46 2015 jordan sabbah
//

#include "Error.hpp"

Error::Error(){
}

Error::Error(Error const &other){
  static_cast<void>(other);
}

Error::Error(std::string const &what, std::string const &who)
  : _what(what), _who(who)
{

}

Error		&Error::operator=(Error const &other){
  static_cast<void>(other);
  return (*this);
}

Error::~Error() throw(){

}
char const	*Error::what() const throw(){
  return _what.c_str();
}

char const 	*Error::who() const throw(){
  return _who.c_str();
}
