/*
** food_count.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 18:06:26 2015 Thibaud Auzou
** Last update Fri Jul  3 15:43:18 2015 Thibaud Auzou
*/

#include "server.h"

static int		food_count(t_wrap_action action, int mode)
{
  static int		_food_count = 0;

  if (action == SET)
    {
      _food_count = (mode ? (_food_count + 1) : (_food_count - 1));
      if (_food_count < 0)
	_food_count = 0;
    }
  return (_food_count);
}

void			food_count_incr(void)
{
  food_count(SET, 1);
}

void			food_count_decr(void)
{
  food_count(SET, 0);
}

int			get_food_count(void)
{
  return (food_count(GET, 0));
}

int			auto_generate_food(void)
{
  while (get_food_count() < ((get_size_x() * get_size_y() * 1 / FOOD_RATIO)))
    if (generate_food() == ERROR ||
	board_add_at_random_coord(FOOD, NULL) == ERROR)
      return (ERROR);
  return (OK);
}
