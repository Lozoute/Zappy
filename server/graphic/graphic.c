/*
** graphic.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 16:02:23 2015 Thibaud Auzou
** Last update Fri Jul  3 14:33:45 2015 Thibaud Auzou
*/

#include "server.h"

static t_team		*graphic(t_wrap_action action, t_team *val)
{
  static t_team		*_graphic = NULL;

  if (action == SET && val)
    _graphic = val;
  return (_graphic);
}

t_team			*get_graphic_team(void)
{
  return (graphic(GET, 0));
}

void			set_graphic_team(t_team *val)
{
  graphic(SET, val);
}

int			send_msg_graph(char *msg, ...)
{
  char			buff[BUFF_SIZE * 2];
  va_list		ap;
  t_team		*graph;
  t_list		*it;
  t_socket		*sock;

  va_start(ap, msg);
  vsprintf(buff, msg, ap);
  if ((graph = get_graphic_team()) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = graph->_members; it; it = it->_next)
    if ((sock = it->_elem))
      if (add_msg_to_buffer(&(sock->_buff), buff) == ERROR)
	return (ERROR);
  va_end(ap);
  return (OK);
}
