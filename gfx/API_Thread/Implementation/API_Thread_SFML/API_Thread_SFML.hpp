//
// API_Thread_SFML.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread/Implementation/API_Thread_SFML
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 10:14:56 2015 jordan sabbah
// Last update Wed Jun 10 10:23:16 2015 jordan sabbah
//

#ifndef API_THREAD_SFML_HPP
# define API_THREAD_SFML_HPP

# include <iostream>
# include <string>
# include <SFML/System.hpp>
# include "API_Thread.hpp"

class Thread : public IThread
{
private:
  sf::Thread		*_thread;
  bool			_running;

  Thread(const Thread &);
  Thread &operator=(const Thread &);

public:
  Thread();
  virtual ~Thread();

  virtual bool		init(IThread::Routine, IThread::Arg);
  virtual bool		stop();
  virtual bool		join();
};

#endif /* !API_THREAD_C_HPP */
