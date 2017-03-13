/*
** socket_close.c for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/c_socket
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Sat Jun 20 17:12:42 2015 florian hellegouarch
** Last update Sun Jul  5 03:23:01 2015 florian hellegouarch
*/

#include "socket.h"

int		close_socket(int fd)
{
  if (close(fd) == -1)
    {
      perror_color(SOCKET_CL_ERR);
      return (-1);
    }
  return (0);
}
