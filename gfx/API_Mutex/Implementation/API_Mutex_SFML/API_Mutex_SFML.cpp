//
// API_Mutex_SFML.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_SFML
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:40:16 2015 jordan sabbah
// Last update Wed Jun 10 09:42:58 2015 jordan sabbah
//

#include "API_Mutex_SFML.hpp"

Mutex::Mutex(){
}

Mutex::Mutex(const Mutex &){
  throw Error("error call copy constructor", "Mutex::Mutex(Mutex const &)");
}

Mutex &Mutex::operator=(const Mutex &){
  return (*this);
}

Mutex::~Mutex(){
}

bool Mutex::lock(){
  _mutex.lock();
  return (true);
}

bool Mutex::trylock(){
  throw Error("sf::Mutex doesn't have trylock", "Mutex::trylock");
  return (false);
}

bool Mutex::unlock(){
  _mutex.unlock();
  return (true);
}

extern "C" EXPORT IMutex *__API_Load__(){
  return (new Mutex);
}
