//
// ScopedLock.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 09:46:35 2015 jordan sabbah
// Last update Wed Jun 10 09:53:35 2015 jordan sabbah
//

#ifndef SCOPEDLOCK_HPP_
# define SCOPEDLOCK_HPP_

# include "Error.hpp"
# include "API_Mutex.hpp"

class ScopedLock{
private:
  IMutex		&_mutex;
public:
  ScopedLock(IMutex &);
  ~ScopedLock();
  ScopedLock(ScopedLock const &);
  ScopedLock &operator=(ScopedLock const &);
};

#endif // !SCOPEDLOCK_HPP_
