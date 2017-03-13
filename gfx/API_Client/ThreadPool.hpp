//
// ThreadPool.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Thread
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jun 19 16:50:30 2015 jordan sabbah
// Last update Mon Jun 22 17:53:12 2015 jordan sabbah
//

#ifndef THREADPOOL_HPP
# define THREADPOOL_HPP

# include <vector>
# include "Loader.hpp"
# include "API_Mutex_Cond.hpp"
# include "API_Thread.hpp"
# include "SafeQueue.hpp"
# include "IGameEngine.hpp"
# include "IServerCommand.hpp"

void *thread_routine(class ThreadPool *);

class ThreadPool{
private:
  Loader					_loader;
  std::vector<IThread *>			_thread;
  SafeQueue<std::shared_ptr<IServerCommand>>	_queue;
  IMutex					&_mutex;
  IMutexCond					&_cond;
  bool						_stop;
  IGameEngine					&_instance;
  bool						is_stopped() const{
    ScopedLock	lock(_mutex);
    return _stop;
  }
  void						stop(){
    ScopedLock lock(_mutex);
    _stop = true;
  }
public:
  ThreadPool(IGameEngine &instance)
    :_mutex(_loader.getInstance<IMutex>("SOs/lib_API_Mutex_C.so", "__API_Load__")),
     _cond(_loader.getInstance<IMutexCond>("SOs/lib_API_Mutex_C.so", "get_IMutexCond")),
     _stop(false),
     _instance(instance)
  {
    for (int i = 0; i < 2; ++i){
      _thread.push_back(&_loader.getInstance<IThread>("SOs/lib_API_Thread_C.so", "__API_Load__"));
      _thread[i]->init(reinterpret_cast<IThread::Routine>(&thread_routine), this);
    }
  }
  ~ThreadPool(){
    while (!_queue.empty())
      _cond.broadcast();
    stop();
    _cond.broadcast();
    for (std::vector<IThread *>::iterator it = _thread.begin(); it != _thread.end(); ++it){
      (*it)->join();
    }
  }
  void				add_queue(std::shared_ptr<IServerCommand> const &task){
    ScopedLock	lock(_mutex);
    _queue.put(task);
  }
  friend void			*thread_routine(ThreadPool *);
};

void				*thread_routine(ThreadPool *pool){
  while (!pool->is_stopped())
    {
      pool->_mutex.lock();
      if (pool->_queue.empty()){
	pool->_cond.wait(pool->_mutex, 5);
	pool->_mutex.unlock();
	continue ;
      }
      std::shared_ptr<IServerCommand> const &task = pool->_queue.get();
      if (!pool->_queue.empty())
	pool->_cond.signal();
      pool->_mutex.unlock();
      pool->_instance.update(task);
    }
  return NULL;
}
#endif // !THREADPOOL_HPP
