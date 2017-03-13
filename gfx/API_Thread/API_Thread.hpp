//
// API_Thread.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun  7 16:38:41 2015 jordan sabbah
// Last update Sun Jun  7 16:59:24 2015 jordan sabbah
//

#ifndef API_THREAD_HPP
# define API_THREAD_HPP

# include "Error.hpp"

class IThread
{
public:
  typedef void * Arg;	       // Arg Type
  typedef Arg (*Routine)(Arg); // Function Pointer Type

  virtual ~IThread() {}

  virtual bool init(Routine, Arg) = 0;
  virtual bool stop() = 0;
  virtual bool join() = 0;
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
#endif /* !API_THREAD_HPP */
