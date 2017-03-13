/*
** rocks.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jun 20 02:18:01 2015 Thibaud Auzou
** Last update Fri Jul  3 14:46:27 2015 Thibaud Auzou
*/

#include "server.h"

const t_rock		g_rock_str[] =
  {
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
  };

static t_list		**rocks(void)
{
  static t_list		*_rocks = NULL;

  return (&_rocks);
}

t_list			**get_list_rocks(void)
{
  return (rocks());
}

t_rock			*rocks_generate(void)
{
  t_rock_type		needed_type;
  t_rock		*new;

  needed_type = rocks_get_needed_type();
  if ((new = malloc(sizeof(t_rock))) == NULL)
    log_err("ERROR [malloc rocks_generate]: ", 1, 1);
  if (new != NULL)
    {
      new->_type = needed_type;
      new->_name = g_rock_str[needed_type]._name;
      add_to_list_begin(rocks(), new);
      rocks_count_incr(needed_type);
    }
  return (new);
}

void			rocks_delete(t_rock *rock)
{
  if (rock)
    {
      rocks_count_decr(rock->_type);
      rm_from_list(rocks(), rock, &rocks_cmp_func_by_ptr, &rocks_del_func);
    }
}

void			rocks_destroy(void)
{
  destroy_list(rocks(), &rocks_del_func);
}
