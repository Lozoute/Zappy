//
// ScopedLock.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:46:38 2015 jordan sabbah
// Last update Wed Jun 10 09:56:54 2015 jordan sabbah
//

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(IMutex &mutex) : _mutex(mutex){
  _mutex.lock();
}

ScopedLock::~ScopedLock(){
  _mutex.unlock();
}

ScopedLock::ScopedLock(ScopedLock const &other) : _mutex(other._mutex){
  throw Error("this function should not have been called", "ScopedLock::ScopedLock(ScopedLock const &)");
}

ScopedLock	&ScopedLock::operator=(ScopedLock const &){
  throw Error("this function should not have been called", "ScopedLock::ScopedLock(ScopedLock const &)");
}
