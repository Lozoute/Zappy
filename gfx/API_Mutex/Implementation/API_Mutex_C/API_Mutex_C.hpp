//
// API_Mutex_C.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_STD
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:45:01 2015 jordan sabbah
// Last update Fri Jun 19 18:42:49 2015 jordan sabbah
//

#ifndef API_MUTEX_C_HPP
# define API_MUTEX_C_HPP

# include <iostream>
# include <string>
# include <pthread.h>
# include "API_Mutex.hpp"
# include "API_Mutex_Cond.hpp"

class Mutex : public IMutex{
protected:
  pthread_mutex_t		_mutex;
  bool				_locked;

  Mutex(const Mutex &);
  Mutex &operator=(const Mutex &);

public:
  Mutex();
  virtual ~Mutex();

  virtual bool			lock();
  virtual bool			trylock();
  virtual bool			unlock();
  friend class MutexCond;
};
#endif /* !API_MUTEX_C_HPP */
