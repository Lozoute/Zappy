//
// main.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Thu Jun 18 23:57:25 2015 jordan sabbah
// Last update Mon Jun 22 14:53:43 2015 jordan sabbah
//

#include "Protocol.hpp"
#include "ServerCommand.hpp"
#include <cstdlib>

// int	main(int ac, char **av){
//   if (ac < 3){
//     std::cerr << "usage: ./a.out host port" << std::endl;
//     return 1;
//   }
//   Protocol proto(av[1], std::atoi(av[2]));
//   proto.test();
//   return 0;
// }

int	main(int ac, char **av){
  if (ac < 2){
    std::cerr << "usage: ./a.out command" << std::endl;
    return 1;
  }
  ServerCommand	command("BIENVENUE\n");
  std::cout << "command = " << command.get_command() << std::endl;
  std::vector<std::string> const &params = command.get_params();
  int	i = 0;
  for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it){
    std::cout << "param " << i << ": '" << *it << "'" << std::endl;
    i++;
  }
  std::cout << "response = '" << command.get_response() << "'" << std::endl;
  return 1;
}
