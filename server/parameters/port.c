/*
** port.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 21:41:18 2015 Thibaud Auzou
** Last update Tue Jun 23 11:29:13 2015 Thibaud Auzou
*/

#include "server.h"

static int	port(t_wrap_action action, int val)
{
  static int	_port = DEFAULT_P;

  if (action == SET)
    _port = val;
  return (_port);
}

int		get_port(void)
{
  return (port(GET, 0));
}

void		set_port(int val)
{
  port(SET, val);
}

int		check_param_p(char *str)
{
  int		i;

  if (str != NULL)
    {
      for (i = 0; str[i]; ++i)
	if (!isdigit(str[i]))
	  return (print_error("Invalid Port.", 0));
      set_port(atoi(str));
    }
  return (OK);
}
