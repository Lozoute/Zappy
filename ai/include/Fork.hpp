//
// Fork.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 16:58:49 2015 florian hellegouarch
// Last update Sun Jul  5 03:21:03 2015 florian hellegouarch
//

#ifndef FORK_HPP_
# define FORK_HPP_

# include "IaClientException.hpp"
# include <unistd.h>

class			Fork
{
public:
  enum			forkProcess
    {
      Child,
      Parent
    };

  static forkProcess	fork();
};

#endif // !FORK_HPP_
