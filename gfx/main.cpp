//
// main.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 23:10:29 2015 jordan sabbah
// Last update Sun Jul  5 00:08:55 2015 jordan sabbah
//

#include "Client.hpp"
#include <iostream>
#include "Error.hpp"
#include "Parser.hpp"

int	main(int ac, char **av){
  try
    {
      if (ac < 3){
	std::cerr << "./zappy-gfx -p port [-h host]" << std::endl;
	return 1;
      }
      Parser	parser(ac, av);
      int	port = parser.get_port();
      std::string const &host = parser.get_host();
      Client	client;
      if (!client.connect(port, host))
	return 1;
      client.display();
    }
  catch (Error const &e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 1;
}
