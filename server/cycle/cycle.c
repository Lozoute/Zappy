/*
** cycle.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jun 18 17:43:14 2015 Thibaud Auzou
** Last update Sun Jul  5 00:47:11 2015 Thibaud Auzou
*/

#include "server.h"

size_t			get_cycle_number(t_wrap_action action)
{
  static size_t		_nb = 0;

  if (action == SET)
    ++_nb;
  else if (action == CLEAN)
    _nb = 0;
  return (_nb);
}

t_timeval		*get_cycle(void)
{
  static t_timeval	_tv;

  _tv.tv_sec = 0;
  _tv.tv_usec = USEC / get_time() - cycle_delta(GET, 0);
  if (_tv.tv_usec <= 0)
    _tv.tv_usec = 10;
  return (&_tv);
}

size_t			get_ucycle(void)
{
  return (USEC / get_time());
}

size_t			get_average_cycle(t_wrap_action action, size_t val)
{
  static size_t		_av = 0;

  if (_av == 0)
    _av = get_ucycle();
  else if (action == SET)
    _av = ((_av * get_cycle_number(GET) + val)) / (get_cycle_number(GET) + 1);
  else if (action == CLEAN)
    _av = get_ucycle();
  return (_av);
}

size_t			cycle_diff(t_timeval *a, t_timeval *b)
{
  size_t		diff;

  diff = (a->tv_sec - b->tv_sec) * USEC;
  diff += a->tv_usec - b->tv_usec;
  return (diff);
}
