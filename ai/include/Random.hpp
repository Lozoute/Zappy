//
// Random.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 23:07:05 2015 florian hellegouarch
// Last update Sun Jul  5 03:22:18 2015 florian hellegouarch
//

#ifndef RANDOM_HPP_
# define RANDOM_HPP_

# include <cstdlib>
# include <ctime>

class		Random
{
public:
  static void	init();
  static int	getInt();
  static float	getFloat();
  static bool	getBool();
};

#endif // !RANDOM_HPP_
