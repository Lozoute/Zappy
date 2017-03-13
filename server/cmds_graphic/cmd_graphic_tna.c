/*
** cmd_graphic_tna.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 15:56:19 2015 Thibaud Auzou
** Last update Thu Jul  2 15:57:12 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_tna(t_socket *sock)
{
  return (cmd_graphic_welcome_teams(sock));
}
