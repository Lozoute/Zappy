/*
** size_y.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 12:17:18 2015 Thibaud Auzou
** Last update Thu Jun 18 01:48:17 2015 Thibaud Auzou
*/

#include "server.h"

static int	size_y(t_wrap_action action, int val)
{
  static int	_size_y = DEFAULT_Y;

  if (action == SET)
    _size_y = val;
  return (_size_y);
}

int		get_size_y(void)
{
  return (size_y(GET, 0));
}

void		set_size_y(int val)
{
  size_y(SET, val);
}

int		check_param_y(char *str)
{
  int		val;

  if (str != NULL)
    {
      if ((val = atoi(str)) < MIN_Y || val > MAX_Y)
	return (print_error("Invalide Size Y", 0));
      set_size_y(val);
    }
  return (OK);
}
