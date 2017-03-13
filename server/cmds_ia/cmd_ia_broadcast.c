/*
** cmd_ia_broadcast.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 30 22:29:55 2015 Thibaud Auzou
** Last update Fri Jul  3 14:00:37 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_broadcast(t_socket *sock)
{
  char		*msg;
  t_list	**teams;
  t_list	*it;
  char		buff[BUFF_SIZE];

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!strlen((msg = sock->_buff._args_buff)))
    return (add_msg_to_buffer(&(sock->_buff), ROK));
  memset(buff, 0, BUFF_SIZE);
  strncpy(buff, msg, strlen(msg) % (BUFF_SIZE - 1));
  if ((teams = get_list_teams()) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  send_msg_graph("pbc %d %s\n", sock->_fd, buff);
  for (it = *teams; it != NULL; it = it->_next)
    if (it->_elem && cmd_ia_broadcast_to_team(buff, it->_elem, sock) == ERROR)
      return (ERROR);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}

int		cmd_ia_broadcast_to_team(char *msg,
					 t_team *team,
					 t_socket *self)
{
  t_list	*it;
  t_socket	*sock;
  char		buff[BUFF_SIZE * 2];
  int		dir;
  t_application	*app;

  if (!msg || !team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (team == get_graphic_team())
    return (OK);
  for (it = team->_members; it != NULL; it = it->_next)
    if ((sock = it->_elem) != NULL && sock != self)
      {
	app = &(self->_application);
	dir = cmd_ia_broadcast_calc(app, &(sock->_application));
	dir = cmd_ia_broadcast_relative(dir, &(sock->_application));
	sprintf(buff, "message %d,%s\n", dir, msg);
	if (add_msg_to_buffer(&(sock->_buff), buff) == ERROR)
	  return (ERROR);
      }
  return (OK);
}
