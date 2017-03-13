//
// API_Mutex.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun  7 16:05:44 2015 jordan sabbah
// Last update Wed Jun 10 09:41:09 2015 jordan sabbah
//

#ifndef API_MUTEX_HPP_
# define API_MUTEX_HPP_

# include <iostream>
# include <string>
# include "Error.hpp"

class IMutex
{
public:
  virtual ~IMutex() {}

  virtual bool			lock() = 0;
  virtual bool			trylock() = 0;
  virtual bool			unlock() = 0;
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
#endif /* !API_MUTEX_HPP_ */
