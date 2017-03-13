//
// API_MutexCond_C.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Mutex/Implementation/API_Mutex_C
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 15:30:58 2015 jordan sabbah
// Last update Sat Jun 20 14:21:23 2015 jordan sabbah
//


#ifndef API_MUTEXCOND_C_HPP
# define API_MUTEXCOND_C_HPP

# include "pthread.h"
# include "API_Mutex_Cond.hpp"
# include "API_Mutex_C.hpp"
# include "Error.hpp"

class MutexCond : public IMutexCond{
protected:
  pthread_cond_t	_cond;
public:
  MutexCond();
  ~MutexCond();
  virtual bool		signal();
  virtual bool		broadcast();
  virtual bool		wait(IMutex &);
  virtual bool		wait(IMutex &, int);
};

#endif // !API_MUTEXCOND_C_HPP
