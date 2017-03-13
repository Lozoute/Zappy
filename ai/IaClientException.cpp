//
// IaClientException.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 17:16:06 2015 florian hellegouarch
// Last update Sun Jul  5 03:16:16 2015 florian hellegouarch
//

#include "IaClientException.hpp"
#include "Client.hpp"

IaClientException::IaClientException() noexcept
  : _what(""), _where("")
{
}

IaClientException::IaClientException(std::string what, std::string where) noexcept
  : _what(what), _where(where)
{
}

IaClientException::~IaClientException() noexcept
{
}

IaClientException	&IaClientException::operator=(const IaClientException &other)
{
  _what = other._what;
  _where = other._where;
  return *this;
}

const char		*IaClientException::what() const noexcept
{
  return _what.c_str();
}

std::string		IaClientException::toString() const
{
  return "IaClientException: " + _what + " in " + _where;
}

void			IaClientException::showError() const
{
  std::cerr << Client::red;
  std::cerr << toString();
  std::cerr << Client::reset << std::endl;
}

void			IaClientException::showError(const std::string &str)
{
  std::cerr << Client::red;
  std::cerr << str;
  std::cerr << Client::reset << std::endl;
}
