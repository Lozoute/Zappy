//
// ConnectionException.hpp for zappy in /home/helleg_f/Desktop/zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jul  4 19:58:06 2015 florian hellegouarch
// Last update Sun Jul  5 03:20:56 2015 florian hellegouarch
//

#ifndef CONNECTIONEXCEPTION_HPP_
# define CONNECTIONEXCEPTION_HPP_

# include <stdexcept>

class		ConnectionException : public std::exception
{
  public:
    ConnectionException() noexcept;
    virtual ~ConnectionException() noexcept;

    ConnectionException             &operator=(const ConnectionException &other);
};

#endif // !CONNECTIONEXCEPTION_HPP_
