/*
** cycle_timer.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 01:34:12 2015 Thibaud Auzou
** Last update Sun Jul  5 01:17:36 2015 Thibaud Auzou
*/

#include "server.h"

int			first_cycle(t_wrap_action action)
{
  static int		first = 1;

  if (action == SET)
    first = 0;
  else if (action == CLEAN)
    first = 1;
  return (first);
}

int			cycle_need_to_be_executed(void)
{
  static t_timeval	_last = {0, 0};
  t_timeval		_now;
  size_t		_diff;
  size_t		_ucycle;

  if (first_cycle(GET) && gettimeofday(&_last, NULL) == -1)
    log_err("ERROR [getimeofday]: ", 1, 1);
  first_cycle(SET);
  if (gettimeofday(&_now, NULL) == -1)
    log_err("ERROR [getimeofday]: ", 1, 1);
  _diff = cycle_diff(&_now, &_last) + cycle_delta(GET, 0);
  if ((_ucycle = get_ucycle()) <= _diff)
    {
      memcpy(&_last, &_now, sizeof(t_timeval));
      get_average_cycle(SET, _diff);
      cycle_delta(SET, _diff - _ucycle);
      get_cycle_number(SET);
      cycle_execute(SET, 1);
      return (1);
    }
  cycle_execute(SET, 0);
  return (0);
}

int			cycle_execute(t_wrap_action action, int val)
{
  static int		_go = 0;

  if (action == SET)
    {
      if (val == 1)
	{
	  auto_generate_rocks();
	  auto_generate_food();
	  application_exec_cycle_eggs();
	}
      _go = val;
    }
  return (_go);
}
