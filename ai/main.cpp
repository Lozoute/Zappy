//
// main.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Wed Jun 17 16:18:18 2015 florian hellegouarch
// Last update Sun Jul  5 03:16:55 2015 florian hellegouarch
//

#include <iostream>
#include <string>
#include <stdexcept>
#include "IaClientException.hpp"
#include "ConnectionException.hpp"
#include "Client.hpp"

int		main(int ac, char **av)
{
  try
    {
      Client::start(ac, av);
    }
  catch (IaClientException &e)
    {
      e.showError();
    }
  catch (ConnectionException &)
    { }
  catch (std::exception &e)
    {
      IaClientException::showError(e.what());
    }
  return (0);
}
