/*
** cmd_graphic_welcome_teams.c for Zappy in /home/lks/rendu/PSU_2014_zappy/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 12:50:28 2015 Thibaud Auzou
** Last update Fri Jul  3 13:55:42 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_welcome_teams(t_socket *sock)
{
  t_list	**teams;
  t_list	*it;
  t_team	*t;
  char		b[BUFF_SIZE * 2];

  if (!sock || !(teams = get_list_teams()))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *teams; it; it = it->_next)
    if ((t = it->_elem) && t != get_graphic_team())
      {
	sprintf(b, "tna %s\n", t->_name);
	if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	  return (ERROR);
    }
  return (OK);
}
