//
// main.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 15:25:05 2015 jordan sabbah
// Last update Sun Jun 21 18:07:09 2015 sabbah jordan
//

#include "Loader.hpp"
#include "API_Mutex.hpp"
#include "API_Mutex_C.hpp"
#include "ScopedLock.hpp"
#include "iostream"
#include <string>

int	main(){
  try
    {
      Loader		load;
      // IMutex		&mutex = load.getInstance<Mutex>("../SOs/lib_API_Mutex_C.so");
      // ScopedLock	lock(mutex);
      std::shared_ptr<IMutex> const	&mutex = load.getSmartPtr<IMutex>("../SOs/lib_API_Mutex_C.so", "__API_Load__");
      ScopedLock			lock(*mutex);
    }
  catch (Error &e)
    {
      std::cerr << e.what() <<  " in " << e.who() << std::endl;
    }
  return 1;
}
