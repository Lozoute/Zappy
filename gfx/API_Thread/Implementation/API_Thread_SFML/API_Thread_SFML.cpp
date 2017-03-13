//
// API_Thread_SFML.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread/Implementation/API_Thread_SFML
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 10:15:28 2015 jordan sabbah
// Last update Wed Jun 10 10:32:27 2015 jordan sabbah
//

#include "API_Thread_SFML.hpp"

Thread::Thread() : _thread(NULL), _running(false){

}

Thread::Thread(const Thread &)  : _thread(NULL), _running(false){
  throw Error("called copy constructor", "Thread::Thread(Thread const &)");
}

Thread	&Thread::operator=(const Thread &)
{
  throw Error("you should not call operator=", "Thread &operator=(Thread const &)");
  return (*this);
}

Thread::~Thread(){
  if (_running)
    _thread->wait();
  if (_thread)
    delete _thread;
}

bool Thread::init(IThread::Routine routine, IThread::Arg arg)
{
  if (_running){
    stop();
    delete _thread;
  }
  _running = true;
  _thread = new sf::Thread(routine, arg);
  _thread->launch();
  return (_running);
}

bool Thread::stop()
{
  try
    {
      if (!_running)
	return false;
      _thread->terminate();
      _running = false;
      delete _thread;
      _thread = NULL;
    }
  catch (std::exception &e)
    {
      return false;
    }
  return true;
}

bool Thread::join()
{
  try
    {
      if (!_running)
	return false;
      _thread->wait();
    }
  catch (std::exception &e)
    {
      return false;
    }
  return true;
}

extern "C"  EXPORT IThread *__API_Load__()
{
  return (new Thread);
}
