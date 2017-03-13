/*
** board_list_func.c for Zappy in /home/auzou_t/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 13:26:20 2015 Thibaud Auzou
** Last update Wed Jun 24 21:27:28 2015 Thibaud Auzou
*/

#include "server.h"

int		board_cmp_func_by_type(void *elem1, void *elem2)
{
  if (!elem1 || !elem2)
    return (0);
  return (((t_item *)(elem1))->_type == ((t_item *)(elem2))->_type);
}

int		board_cmp_func_by_ptr(void *elem1, void *elem2)
{
  if (!elem1 || !elem2)
    return (0);
  return (((t_item *)(elem1))->_item == ((t_item *)(elem2))->_item);
}

int		board_cmp_func_by_item(void *elem1, void *elem2)
{
  if (!elem2)
    return (0);
  return (elem1 == ((t_item *)(elem2))->_item);
}

int		board_del_func(void *elem)
{
  if (elem)
    free((t_item *)(elem));
  return (OK);
}
