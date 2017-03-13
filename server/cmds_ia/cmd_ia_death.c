/*
** cmd_ia_death.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 13:16:19 2015 Thibaud Auzou
** Last update Fri Jul  3 20:13:13 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_death(t_socket *s)
{
  t_team	*t;

  if (!s)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (--(s->_application._pv) <= 0)
    {
      t = s->_application._team;
      add_msg_to_buffer(&(s->_buff), "mort\n");
      s->_blocked = 1;
      return (log_evt("EVENT [Death] [Id: %d] [Team: %s]", s->_fd,
		      (t ? t->_name : "")));
    }
  s->_application._bag[0] = s->_application._pv / PV_RATIO;
  return (OK);
}
