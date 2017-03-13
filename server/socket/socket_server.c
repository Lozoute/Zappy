/*
** socket_server.c for Zappy in /home/auzou_t/rendu/PSU_2014_zappy/server/socket
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 11:17:52 2015 Thibaud Auzou
** Last update Fri Jul  3 15:18:53 2015 Thibaud Auzou
*/

#include "server.h"

int		socket_server_init(t_socket *sock)
{
  sock->_read_func = &socket_server_read_func;
  sock->_write_func = NULL;
  application_init(&(sock->_application));
  return (OK);
}

int		socket_server_read_func(t_socket *server)
{
  t_sockaddr	addr;
  t_socket	*client;
  socklen_t	addrlen;
  int		fd;

  addrlen = sizeof(t_sockaddr);
  if ((fd = accept(server->_fd, (struct sockaddr *)(&addr), &addrlen)) == -1)
    return (log_err("ERROR [accept] :", 1, 1));
  if ((client = create_socket(CLIENT, fd)) == NULL)
    return (log_err("ERROR [create_socket]", 0, 0));
  if (add_msg_to_buffer(&(client->_buff), "BIENVENUE\n") == ERROR)
    return (log_err("ERROR [Bienvenue]: ", 0, 0));
  log_evt("EVENT [Connexion] [Id %d]", fd);
  return (OK);
}
