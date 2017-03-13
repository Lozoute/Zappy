/*
** size.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 12:09:11 2015 Thibaud Auzou
** Last update Thu Jun 18 01:48:22 2015 Thibaud Auzou
*/

#include "server.h"

static int	size_x(t_wrap_action action, int val)
{
  static int	_size_x = DEFAULT_X;

  if (action == SET)
    _size_x = val;
  return (_size_x);
}

int		get_size_x(void)
{
  return (size_x(GET, 0));
}

void		set_size_x(int val)
{
  size_x(SET, val);
}

int		check_param_x(char *str)
{
  int		val;

  if (str != NULL)
    {
      if ((val = atoi(str)) < MIN_X || val > MAX_X)
	return (print_error("Invalide Size X", 0));
      set_size_x(val);
    }
  return (OK);
}
