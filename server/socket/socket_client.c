/*
** socket_client.c for Zappy in /home/auzou_t/rendu/PSU_2014_zappy/server/socket
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 23 11:20:18 2015 Thibaud Auzou
** Last update Sat Jul  4 01:12:32 2015 Thibaud Auzou
*/

#include "server.h"

int		socket_client_init(t_socket *sock)
{
  sock->_read_func = &socket_client_read_func;
  sock->_write_func = &socket_client_write_func;
  application_init(&(sock->_application));
  return (OK);
}

static int	buff_log_error(int e)
{
  return (log_err("ERROR [read socket_client_read_func]: %s", e, e,
		  (e ? "" : "Reset From Peer Side")));
}

int		socket_client_read_func(t_socket *sock)
{
  char		buff[BUFF_SIZE];
  int		ret;
  int		e;

  if (sock == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((ret = read(sock->_fd, buff, BUFF_SIZE - 1)) <= 0)
    return (buff_log_error((ret == -1 ? 1 : 0)));
  buff[ret] = 0;
  if (strlen(buff) == 0)
    return (log_err("ERROR [ReadLen] [File: %s] [Line: %d]", 0, 0, _F, _L));
  buffer_copy(&(sock->_buff), buff);
  while (strstr(sock->_buff._read_buff, SEP))
    if ((e = application_treat_data
	 (sock, buffer_split(&(sock->_buff), SEP))) != OK)
      return (e);
  return (OK);
}

int		socket_client_write_func(t_socket *sock)
{
  char		*msg;
  int		ret;
  int		len;

  if (!sock || !sock->_buff._msg)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((msg = sock->_buff._msg->_elem) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((len = strlen(msg)) == 0)
    return (log_err("ERROR [WriteLen] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((ret = send(sock->_fd, msg, len, MSG_NOSIGNAL)) <= 0)
    return (log_err("ERROR [write socket_client_write_func]: ", 1, 1));
  if (ret < len)
    buffer_str_copy(msg, &(msg[ret]), len - ret);
  else
    list_pop_head(&(sock->_buff._msg), &buffer_del_func);
  return (OK);
}

int		socket_client_disconnect(t_socket *sock)
{
  t_list	**sockl;
  int		fd;
  extern int	errno;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  fd = sock->_fd;
  if (sock->_application._team)
    remove_player_from_team(sock->_application._team, sock);
  if (sock->_application._type == IA)
    board_rm_at_coord(sock->_application._x, sock->_application._y, sock);
  sockl = get_list_socket();
  if (sock->_socket_type == CLIENT && sock->_application._type == IA)
    send_msg_graph("pdi %d\n", sock->_fd);
  rm_from_list(sockl, sock, &socket_cmp_func_by_ptr, &socket_del_func);
  return (log_err("RESET [Id %d Disconnected]", 0, 0, fd));
}
