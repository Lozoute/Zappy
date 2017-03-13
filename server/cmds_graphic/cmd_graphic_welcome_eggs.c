/*
** cmd_graphic_welcome_eggs.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 12:48:46 2015 Thibaud Auzou
** Last update Fri Jul  3 13:56:28 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_welcome_eggs(t_socket *sock)
{
  t_list	**teams;
  t_list	*it;
  t_team	*t;

  if (!sock || !(teams = get_list_teams()))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *teams; it; it = it->_next)
    if ((t = it->_elem) && t != get_graphic_team())
      {
	if (cmd_graphic_welcome_ceggs(sock, t) == ERROR)
	  return (ERROR);
	if (cmd_graphic_welcome_reggs(sock, t) == ERROR)
	  return (ERROR);
      }
  return (OK);
}

int		cmd_graphic_welcome_ceggs(t_socket *sock, t_team *t)
{
  t_list	*it;
  t_egg		*e;
  char		b[BUFF_SIZE];

  if (!sock || !t)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = t->_ceggs; it; it = it->_next)
    if ((e = it->_elem))
      {
	sprintf(b, "enw %d %d %d %d\n", e->_id, e->_dad, e->_x, e->_y);
	if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	  return (ERROR);
      }
  return (OK);
}

int		cmd_graphic_welcome_reggs(t_socket *sock, t_team *t)
{
  t_list	*it;
  t_egg		*e;
  char		b[BUFF_SIZE];

  if (!sock || !t)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = t->_eggs; it; it = it->_next)
    if ((e = it->_elem))
      {
	sprintf(b, "enw %d %d %d %d\n", e->_id, e->_dad, e->_x, e->_y);
	if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	  return (ERROR);
	sprintf(b, "eht %d\n", e->_id);
	if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	  return (ERROR);
      }
  return (OK);
}
