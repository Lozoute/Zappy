/*
** cmd_graphic_mct.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 15:47:28 2015 Thibaud Auzou
** Last update Thu Jul  2 15:49:45 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_mct(t_socket *sock)
{
  return (cmd_graphic_welcome_cases(sock));
}
