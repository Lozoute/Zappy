/*
** food.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 18:04:00 2015 Thibaud Auzou
** Last update Mon Jun 29 22:37:48 2015 Thibaud Auzou
*/

#include "server.h"

static t_list			**food(void)
{
  static t_list			*_food = NULL;

  return (&_food);
}

t_list				**get_list_food(void)
{
  return (food());
}

void				food_destroy(void)
{
  destroy_list(food(), NULL);
}

int				generate_food(void)
{
  if (add_to_list_begin(food(), NULL) == ERROR)
    return (ERROR);
  food_count_incr();
  return (OK);
}

void				food_delete(void)
{
  list_pop_head(food(), NULL);
  food_count_decr();
}
