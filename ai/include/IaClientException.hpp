//
// IaClientException.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 17:13:31 2015 florian hellegouarch
// Last update Sun Jul  5 03:21:13 2015 florian hellegouarch
//

#ifndef IACLIENTEXCEPTION_HPP_
# define IACLIENTEXCEPTION_HPP_

#include <exception>
#include <string>
#include <iostream>

class				IaClientException : public std::exception
{
private:
  std::string			_what;
  std::string			_where;

public:
  IaClientException() noexcept;
  IaClientException(std::string what, std::string where) noexcept;
  virtual ~IaClientException() noexcept;

  IaClientException		&operator=(const IaClientException &other);

  virtual const char		*what() const noexcept;
  std::string			toString() const;
  void				showError() const;

  static void			showError(const std::string &str);
};

#endif // !IACLIENTEXCEPTION_HPP_
