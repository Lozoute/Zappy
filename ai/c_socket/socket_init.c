/*
** socket_init.c for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/c_socket_client
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Wed Jun 17 15:56:29 2015 florian hellegouarch
** Last update Sun Jul  5 03:23:23 2015 florian hellegouarch
*/

#include "socket.h"

static int		socket_clt(struct sockaddr_in *s, int socket_fd)
{
  if (connect(socket_fd, (struct sockaddr*)s, sizeof(*s)) == -1)
    {
      perror_color(CONNECT_ERR);
      return (-1);
    }
  return (0);
}

static int		socket_init(struct sockaddr_in *s,
				    char const *port, char const *ip)
{
  int			fd;
  struct protoent	*pe;

  s->sin_family = AF_INET;
  s->sin_port = htons(atoi(port));
  s->sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;
  if (!(pe = getprotobyname("TCP")))
    {
      perror_color(PROTO_ERR);
      return (-1);
    }
  fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (fd == -1)
    perror_color(INIT_ERR);
  return (fd);
}

int			socket_init_clt(char const *ip, char const *port)
{
  int			fd;
  struct sockaddr_in	s;

  if ((fd = socket_init(&s, port, ip)) != -1 && socket_clt(&s, fd) != -1)
    return (fd);
  return (-1);
}
