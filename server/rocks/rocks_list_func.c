/*
** rocks_list_func.c for Zappy in /home/auzou_t/rendu/PSU_2014_zappy/server/rocks
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 12:10:23 2015 Thibaud Auzou
** Last update Tue Jun 23 12:36:36 2015 Thibaud Auzou
*/

#include "server.h"

int		rocks_cmp_func_by_ptr(void *elem1, void *elem2)
{
  return ((t_rock *)(elem1) == (t_rock *)(elem2));
}

int		rocks_cmp_type_only(void *elem1, void *elem2)
{
  return (*((t_rock_type *)(elem1)) == *((t_rock_type *)(elem2)));
}

int		rocks_del_func(void *elem)
{
  free((t_rock *)(elem));
  return (OK);
}
