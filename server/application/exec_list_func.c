/*
** exec_list_func.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jun 26 13:28:09 2015 Thibaud Auzou
** Last update Fri Jun 26 13:28:48 2015 Thibaud Auzou
*/

#include "server.h"

int		exec_del_func(void *elem)
{
  if (elem)
    free((t_exec *)(elem));
  return (OK);
}
