//
// API_Mutex_C.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_STD
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:45:07 2015 jordan sabbah
// Last update Sun Jun 21 15:05:46 2015 jordan sabbah
//

#include <iostream>
#include "API_Mutex_C.hpp"

Mutex::Mutex() : _locked(false)
{
  if (pthread_mutex_init(&_mutex, NULL))
    throw Error("error init pthread_mutex_init", "Mutex::Mutex()");
}

Mutex::Mutex(const Mutex &){
  throw Error("error call copy constructor", "Mutex::Mutex(Mutex const &)");
}

Mutex &Mutex::operator=(const Mutex &){
  return (*this);
}

Mutex::~Mutex(){
}

bool	Mutex::lock(){
  if (!pthread_mutex_lock(&_mutex))
    _locked = true;
  return _locked;
}
bool	Mutex::unlock(){
  if (!pthread_mutex_unlock(&_mutex))
    _locked = false;
  return !_locked;
}

bool	Mutex::trylock(){
  return (_locked = pthread_mutex_trylock(&_mutex));
}

extern "C" EXPORT IMutex *__API_Load__(){
  return (new Mutex);
}
