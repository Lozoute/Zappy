/*
** time.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 12:22:31 2015 Thibaud Auzou
** Last update Thu Jun 18 01:48:36 2015 Thibaud Auzou
*/

#include "server.h"

static int	cycle_time(t_wrap_action action, int val)
{
  static int	_time = DEFAULT_T;

  if (action == SET)
    _time = val;
  return (_time);
}

int		get_time(void)
{
  return (cycle_time(GET, 0));
}

void		set_time(int val)
{
  cycle_time(SET, val);
}

int		check_param_t(char *str)
{
  int		val;

  if (str != NULL)
    {
      if ((val = atoi(str)) < MIN_T || val > MAX_T)
	return (print_error("Invalide Frequency", 0));
      set_time(val);
    }
  return (OK);
}
