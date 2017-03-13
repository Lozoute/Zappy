/*
** get_char.c for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/c_protocol
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Wed Jun 17 20:22:09 2015 florian hellegouarch
** Last update Sun Jul  5 03:22:44 2015 florian hellegouarch
*/

#include "socket.h"

char		get_char(int fd)
{
  static char	buff[BUFF_SIZE];
  static int	read_size = 0;
  static int	char_left = 0;

  if (!char_left)
    {
      if ((read_size = read(fd, &buff, BUFF_SIZE)) == -1)
	{
	  perror_color(RD_ERR);
	  return (-1);
	}
      if (read_size == 0)
	return (0);
      char_left = read_size;
    }
  return (buff[read_size - (char_left--)]);
}
