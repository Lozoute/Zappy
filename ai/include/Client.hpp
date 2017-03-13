//
// Client.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 18:17:29 2015 florian hellegouarch
// Last update Sun Jul  5 22:59:28 2015 florian hellegouarch
//

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <unistd.h>

class				Client
{
private:
  static int			timeout;
  static bool			debug;
  static int			minPlayers;
  static pid_t			pid;

  Client();

  static bool			parseArgs(std::string *args, int ac, char **av);
  static bool			getArg(std::string *args, int ac, char **av);
  static void			checkArgs();

public:
  static void			start(int ac, char **av);
  static int			getTimeout();
  static bool			getDebug();
  static void			exit();
  static int			getMinPlayers();
  static pid_t			getPid();

  static const std::string	white;
  static const std::string	red;
  static const std::string	blue;
  static const std::string	green;
  static const std::string	yellow;
  static const std::string	reset;
};

#endif // !CLIENT_HPP_
