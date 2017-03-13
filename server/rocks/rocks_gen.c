/*
** rocks_gen.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 30 16:10:59 2015 Thibaud Auzou
** Last update Sun Jul  5 18:59:55 2015 florian hellegouarch
*/

#include "server.h"

t_rock		*rocks_generate_type(t_rock_type type)
{
  t_rock	*new;

  type %= NB_ROCKS;
  if ((new = malloc(sizeof(t_rock))) == NULL)
    log_err("ERROR [malloc rocks_generate_type]: ", 1, 1);
  if (new != NULL)
    {
      new->_type = type;
      new->_name = g_rock_str[type]._name;
      add_to_list_begin(get_list_rocks(), new);
      rocks_count_incr(type);
    }
  return (new);
}

int		auto_generate_rocks(void)
{
  void		*elem;

  while (rocks_get_count(-1) < (get_size_x() * get_size_y() * 1) / ROCK_RATIO)
    if ((elem = rocks_generate()) == NULL ||
	board_add_at_random_coord(ROCK, elem) == ERROR)
      return (ERROR);
  return (OK);
}
