/*
** rocks_count.c for Zappy in /home/auzou_t/rendu/PSU_2014_zappy/server/rocks
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 12:16:36 2015 Thibaud Auzou
** Last update Thu Jul  2 00:29:32 2015 Thibaud Auzou
*/

#include "server.h"

static int		rocks_count(t_wrap_action action,
				    int mode,
				    t_rock_type type)
{
  static int		rocks_tab[NB_ROCKS] = {0, 0, 0, 0, 0, 0};
  int			res;
  int			i;

  if (action == SET)
    {
      rocks_tab[type] = (mode ? (rocks_tab[type] + 1) : (rocks_tab[type] - 1));
      if (rocks_tab[type] < 0)
	rocks_tab[type] = 0;
    }
  else if (action == GET && (int)(type) == -1)
    {
      for (res = 0, i = 0; i < NB_ROCKS; ++i)
	res += rocks_tab[i];
      return (res);
    }
  return (rocks_tab[type]);
}

t_rock_type		rocks_get_needed_type(void)
{
  t_rock_type		res;
  int			i;

  for (res = LINEMATE, i = 0; i < NB_ROCKS; ++i)
    if (rocks_count(GET, 0, i) < rocks_count(GET, 0, res))
      res = i;
  return (res);
}

void			rocks_count_incr(t_rock_type type)
{
  rocks_count(SET, 1, type);
}

void			rocks_count_decr(t_rock_type type)
{
  rocks_count(SET, 0, type);
}

int			rocks_get_count(t_rock_type type)
{
  return (rocks_count(GET, 0, type));
}
