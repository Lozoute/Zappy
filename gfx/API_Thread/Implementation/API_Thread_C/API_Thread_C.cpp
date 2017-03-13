//
// API_Thread_C.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread/Implementation/API_Thread_C
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 10:13:18 2015 jordan sabbah
// Last update Sun Jul  5 18:32:24 2015 jordan sabbah
//

#include "API_Thread_C.hpp"

Thread::Thread() : _running(false){

}

Thread::Thread(const Thread &)  : _running(false){
  throw Error("called copy constructor", "Thread::Thread(Thread const &)");
}

Thread	&Thread::operator=(const Thread &)
{
  return (*this);
}

Thread::~Thread(){
  if (_running)
    join();
}

bool Thread::init(IThread::Routine routine, IThread::Arg arg)
{
  if (_running)
    stop();
  return (_running = !pthread_create(&_thread, NULL, routine, arg));
}

bool Thread::stop()
{
  if (_running && !pthread_cancel(_thread))
    return !(_running = false);
  return (_running);
}

bool Thread::join()
{
  if (_running && !pthread_join(_thread, NULL))
    return !(_running = false);
  return false;
}

extern "C"  EXPORT IThread *__API_Load__()
{
  return (new Thread);
}
