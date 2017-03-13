//
// API_MutexCond_C.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Mutex/Implementation/API_Mutex_C
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 15:30:56 2015 jordan sabbah
// Last update Mon Jun 22 15:17:07 2015 jordan sabbah
//

#include "API_MutexCond_C.hpp"

MutexCond::MutexCond(){
  if (pthread_cond_init(&_cond, NULL))
    throw Error("error init pthread_mutex_init", "MutexCond::MutexCond()");
}

MutexCond::~MutexCond(){
  pthread_cond_broadcast(&_cond);
}

bool	MutexCond::wait(IMutex &mutex){
  Mutex &m = dynamic_cast<Mutex &>(mutex);
  bool ret = pthread_cond_wait(&_cond, &m._mutex);
  return ret;
}

bool	MutexCond::wait(IMutex &mutex, int sec){
  Mutex &m = dynamic_cast<Mutex &>(mutex);
  timespec time = {sec, 0};
  bool ret = pthread_cond_timedwait(&_cond, &m._mutex, &time);
  return ret;
}

bool	MutexCond::broadcast(){
  return !pthread_cond_broadcast(&_cond);
}

bool	MutexCond::signal(){
  return !pthread_cond_signal(&_cond);
}

extern "C" IMutexCond *get_IMutexCond(){
  return (new MutexCond);
}
