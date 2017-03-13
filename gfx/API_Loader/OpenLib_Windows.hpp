//
// OpenLib_Windows.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 16:38:36 2015 jordan sabbah
// Last update Wed Jun 10 00:06:38 2015 jordan sabbah
//

#ifndef OPENLIB_WINDOWS_HPP
# define OPENLIB_WINDOWS_HPP

# include <string>
# include <utility>
# include <list>
# include <Windows.h>
# include <Winbase.h>
# include "API_OpenLib.hpp"

class OpenLib : public IOpenLib{
private:
  typedef std::pair<std::string const, void *> pair;
  std::list<pair>		_syms;
  std::string const		_name;
  HMODULE			_libHandle;
public:
  OpenLib(std::string const &);
  virtual ~OpenLib();
  OpenLib(OpenLib const &);
  OpenLib &operator=(OpenLib const &);
  virtual bool			is_sym(std::string const &) const;
  virtual void			*&get_sym(std::string const &);
  virtual void			push_sym(std::string const &);
  virtual std::string const	&get_name() const;
};

# endif // !OPENLIB_WINDOWS_HPP
