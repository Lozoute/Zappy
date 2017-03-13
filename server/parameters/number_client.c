/*
** number_client.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 12:19:18 2015 Thibaud Auzou
** Last update Thu Jun 18 01:47:59 2015 Thibaud Auzou
*/

#include "server.h"

static int	number_client(t_wrap_action action, int val)
{
  static int	_number = DEFAULT_C;

  if (action == SET)
    _number = val;
  return (_number);
}

int		get_number_client(void)
{
  return (number_client(GET, 0));
}

void		set_number_client(int val)
{
  number_client(SET, val);
}

int		check_param_c(char *str)
{
  int		val;

  if (str != NULL)
    {
      if ((val = atoi(str)) < MIN_C || val > MAX_C)
	return (print_error("Invalide Number Of Client", 0));
      set_number_client(val);
    }
  return (OK);
}
