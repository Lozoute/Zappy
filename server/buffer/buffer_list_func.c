/*
** buffer_list_func.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 20:20:57 2015 Thibaud Auzou
** Last update Wed Jun 24 20:21:38 2015 Thibaud Auzou
*/

#include "server.h"

int		buffer_del_func(void *elem)
{
  if (elem)
    free((char *)(elem));
  return (OK);
}
