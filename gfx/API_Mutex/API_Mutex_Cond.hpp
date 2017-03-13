//
// API_Mutex_Cond.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Mutex
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 15:25:16 2015 jordan sabbah
// Last update Sat Jun 20 14:18:54 2015 jordan sabbah
//

#ifndef API_MUTEX_COND_HPP
# define API_MUTEX_COND_HPP

# include "API_Mutex.hpp"

class IMutexCond{
public:
  virtual ~IMutexCond(){}

  virtual bool	wait(IMutex &) = 0;
  virtual bool	wait(IMutex &, int) = 0;
  virtual bool	broadcast() = 0;
  virtual bool	signal() = 0;
};

# if defined(WIN32) || defined (_WIN32)
  //  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# elif defined(linux) || defined (__unix__)
  //  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# else
  //  do nothing and hope for the best?
# define EXPORT
# define IMPORT
# pragma warning Unknown dynamic link import/export semantics.
# endif

#endif // !API_MUTEX_COND_HPP
