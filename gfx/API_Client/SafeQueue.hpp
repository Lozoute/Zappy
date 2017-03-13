//
// SafeQueue.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 15:20:44 2015 jordan sabbah
// Last update Sat Jul  4 05:03:23 2015 jordan sabbah
//

#ifndef SAFEQUEUE_HPP_
# define SAFEQUEUE_HPP_

# include <deque>
# include "API_Mutex_C.hpp"
# include "ScopedLock.hpp"
# include <iostream>

template<typename T>
class SafeQueue{
protected:
  std::deque<T>		_queue;
  Mutex			_mutex;
  bool			_closed;
public:
  SafeQueue()
  {
    _closed = false;
  }
  ~SafeQueue(){
    _closed = true;
    ScopedLock	lock(_mutex);
  }
  void			put(T arg){
    if (_closed)
      return ;
    ScopedLock	lock(_mutex);
    _queue.push_back(arg);
  }
  T		get(){
    if (_closed)
      return NULL;
    ScopedLock	lock(_mutex);
    if (_queue.empty())
      return NULL;
    T  val = _queue.front();
    _queue.pop_front();
    return val;
  }
   bool			empty(){
    ScopedLock	lock(_mutex);
    return _queue.empty();
  }
  int			size(){
    ScopedLock	lock(_mutex);
    return _queue.size();
  }
};

#endif // !SAFEQUEUE_HPP_
