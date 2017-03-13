/*
** cycle_delta.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 01:56:55 2015 Thibaud Auzou
** Last update Sun Jul  5 00:48:17 2015 Thibaud Auzou
*/

#include "server.h"

size_t			cycle_delta(t_wrap_action action, size_t val)
{
  static size_t		_av = 0;

  if (_av == 0)
    _av = get_ucycle() / 100 * 20;
  else if (action == SET)
    _av = ((_av * get_cycle_number(GET) + val)) / (get_cycle_number(GET) + 1);
  else if (action == CLEAN)
    _av = get_ucycle() / 100 * 20;
  return (_av);
}
