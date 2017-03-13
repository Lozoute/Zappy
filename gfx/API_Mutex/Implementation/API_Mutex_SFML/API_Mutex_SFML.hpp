//
// API_Mutex_SFML.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_SFML
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:35:10 2015 jordan sabbah
// Last update Wed Jun 10 09:40:37 2015 jordan sabbah
//

#ifndef API_MUTEX_SFML_HPP
# define API_MUTEX_SFML_HPP

# include <iostream>
# include <string>
# include <SFML/System.hpp>
# include "API_Mutex.hpp"

class Mutex : public IMutex{
private:
  sf::Mutex		_mutex;

  Mutex(const Mutex &);
  Mutex &operator=(const Mutex &);

public:
  Mutex();
  virtual ~Mutex();

  virtual bool			lock();
  virtual bool			trylock();
  virtual bool			unlock();
};
#endif /* !API_MUTEX_SFML_HPP */
