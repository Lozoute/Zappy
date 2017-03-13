/*
** socket_destroy.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server/socket
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 21:41:15 2015 Thibaud Auzou
** Last update Wed Jun 17 21:44:42 2015 Thibaud Auzou
*/

#include "server.h"

int		socket_destroy(void)
{
  return (destroy_list(get_list_socket(), &socket_del_func));
}
