/*
** socket_list_func.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server/socket
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 17:48:56 2015 Thibaud Auzou
** Last update Fri Jul  3 14:47:14 2015 Thibaud Auzou
*/

#include "server.h"

int		socket_cmp_func_by_fd(void *sock1, void *sock2)
{
  if (sock1 == NULL || sock2 == NULL)
    return (0);
  return (((t_socket *)(sock1))->_fd == ((t_socket *)(sock2))->_fd ? 1 : 0);
}

int		socket_cmp_func_by_fd_only(void *fd, void *sock)
{
  if (!sock || !fd)
    return (0);
  return (((t_socket *)(sock))->_fd == *((int *)(fd)));
}
int		socket_cmp_func_by_ptr(void *sock1, void *sock2)
{
  return (sock1 == sock2 ? 1: 0);
}

int		socket_del_func(void *arg)
{
  t_socket	*sock;

  sock = (t_socket *)(arg);
  if (sock == NULL)
    return (ERROR);
  if (close(sock->_fd) == -1)
    log_err("ERROR [close socket_del_func]: ", 1, 1);
  if (sock->_buff._msg)
    destroy_list(&(sock->_buff._msg), &buffer_del_func);
  if (sock->_socket_type == CLIENT)
    destroy_list(&(sock->_application._exec), &exec_del_func);
  free(sock);
  return (OK);
}
