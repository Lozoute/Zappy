/*
** cmd_ia_victory.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 14:40:01 2015 Thibaud Auzou
** Last update Sat Jul  4 23:12:52 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_victory(t_team *team)
{
  t_list	*it;
  t_socket	*s;
  int		nb;

  if (!team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  nb = 0;
  for (it = team->_members; it; it = it->_next)
    if ((s = it->_elem))
      if (s->_application._lvl == 8)
	nb++;
  if (nb >= 6)
    return (cmd_ia_victory_yes(team->_name));
  return (OK);
}

int		cmd_ia_victory_yes(char *name)
{
  t_list	**sockets;
  t_list	*it;
  t_socket	*s;

  if (!name)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  send_msg_graph("seg %s\n", name);
  if ((sockets = get_list_socket()) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *sockets; it; it = it->_next)
    if ((s = it->_elem) && s->_socket_type == CLIENT
	&& s->_application._type == IA)
      {
	if (add_msg_to_buffer(&(s->_buff), "mort\n") == ERROR)
	  return (ERROR);
	s->_blocked = 1;
      }
  log_evt("VICTORY: %s", name);
  printf("%s WIN !!\n", name);
  return (OK);
}
