/*
** socket.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 16:33:19 2015 Thibaud Auzou
** Last update Thu Jul  2 16:04:08 2015 Thibaud Auzou
*/

#include "server.h"

static t_list		**socket_list()
{
  static t_list		*_socket_list = NULL;

  return (&_socket_list);
}

t_socket		*create_socket(t_socket_type type, int fd)
{
  t_socket		*new;

  if ((new = malloc(sizeof(t_socket))) == NULL)
    return (NULL);
  new->_fd = fd;
  new->_blocked = 0;
  new->_socket_type = type;
  buffer_init(&(new->_buff));
  if (type == SERVER && socket_server_init(new) == ERROR)
    return (NULL);
  else if (type == CLIENT && socket_client_init(new) == ERROR)
    return (NULL);
  if (add_to_list_begin(socket_list(), new) == ERROR)
    return (NULL);
  return (new);
}

int			remove_socket(t_socket *s)
{
  return (rm_from_list(socket_list(), s,
		       &socket_cmp_func_by_fd, &socket_del_func));
}

t_list			**get_list_socket(void)
{
  return (socket_list());
}

t_socket		*get_socket(int fd)
{
  return (find_in_list(socket_list(), &fd, &socket_cmp_func_by_fd_only));
}
