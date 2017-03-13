//
// Loader.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 00:11:38 2015 jordan sabbah
// Last update Sun Jun 21 18:06:55 2015 sabbah jordan
//

#ifndef LOADER_HPP_
# define LOADER_HPP_

# include <iostream>
# include <string>
# include <memory>
# include <list>
# include "Error.hpp"
# include "Instance.hpp"
# include "API_OpenLib.hpp"

class Loader
{
protected:
  std::list<AInstance *>		_instance;
  std::list<OpenLib *>			_openLibs;

  OpenLib			*&get_openLib(std::string const &);
public:
  Loader();
  ~Loader();
  Loader(const Loader &);
  Loader			&operator=(const Loader &);
  template <typename T, typename... Args>
  T				&getInstance(std::string const &lib,
					     std::string const &sym,
					     Args... args)
  {
    OpenLib *&my_lib = get_openLib(lib);
    T *(*f)(Args...) = reinterpret_cast<T *(*)(Args...)>(my_lib->get_sym(sym));
    AInstance *tmp = new Instance<T>(f(args...));
    _instance.push_back(tmp);
    return (tmp->get_inst<T>());
  }
  template <typename T, typename... Args>
  std::shared_ptr<T>		getSmartPtr(std::string const &lib,
					    std::string const &sym,
					    Args... args)
  {
    OpenLib *&my_lib = get_openLib(lib);
    T *(*f)(Args...) = reinterpret_cast<T *(*)(Args...)>(my_lib->get_sym(sym));
    T *ptr = f(args...);
    return (std::shared_ptr<T>(ptr));
  }
  template<typename T>
  T	&get_sym(std::string const &lib,
	     std::string const &sym = "__API_Load__"){
    OpenLib *&my_lib = get_openLib(lib);
    T &f = static_cast<T>(my_lib->get_sym(sym));
    return (f);
  }
  void				clean_instance();
  void				clean_openLibs();
};
#endif /* !LOADER_HPP_ */
