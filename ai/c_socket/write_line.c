/*
** write_line.c for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/c_socket
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Sat Jun 20 17:21:53 2015 florian hellegouarch
** Last update Sun Jul  5 03:23:39 2015 florian hellegouarch
*/

#include "socket.h"

static char	*malloc_line(const char *str, int len)
{
  char		*line;

  line = malloc(len);
  if (!line)
    {
      perror_color(MALLOC_ERR);
      return (0);
    }
  strcpy(line, str);
  line[len - 1] = '\n';
  return (line);
}

int		write_line(int fd, const char *str)
{
  int		len;
  char		*line;
  int		nbChar;
  int		n;

  len = strlen(str) + 1;
  line = malloc_line(str, len);
  if (!line)
    return (-1);
  nbChar = 0;
  while (nbChar < len)
    {
      n = write(fd, line + nbChar, len - nbChar);
      if (n == -1 || n == 0)
	{
	  free(line);
	  perror_color(WR_ERR);
	  return (-1);
	}
      nbChar += n;
    }
  free(line);
  return (0);
}
