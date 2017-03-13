/*
** application.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 18:22:19 2015 Thibaud Auzou
** Last update Sat Jul  4 18:40:14 2015 Thibaud Auzou
*/

#include "server.h"

int		application_init(t_application *app)
{
  app->_connected = 0;
  app->_type = UNKNOWN;
  app->_entry_point = NULL;
  app->_team = NULL;
  app->_x = 0;
  app->_y = 0;
  app->_direction = TOP;
  app->_pv = 10 * PV_RATIO;
  app->_lvl = 1;
  app->_exec = NULL;
  app->_nb_exec = 0;
  memset(app->_bag, 0, (sizeof(int) * NB_BAG));
  app->_bag[0] = 10;
  return (OK);
}

int		application_treat_data(t_socket *sock, char *data)
{
  if (!sock || !data)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!sock->_application._connected)
    return (application_try_to_connect(sock, data));
  if (!sock->_application._entry_point)
    return (log_err("ERROR [NullFunc [File: %s] [Line: %d]", 0, 0, _F, _L));
  return (sock->_application._entry_point(sock, data));
}

int		application_try_to_connect(t_socket *sock, char *data)
{
  int		err;
  t_team	*t;

  err = 0;
  if (!sock || !data)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (strlen(data) > BUFF_SIZE)
    err = 1;
  else if (!strcasecmp("graphic", data))
    return (application_graphic_init(sock));
  else if (!(t = find_team(data)))
    err = 1;
  else if (t->_slots < 1)
    err = 1;
  if (!err)
    return (application_ia_init(sock, t));
  if (add_msg_to_buffer(&(sock->_buff), "ko\n") == ERROR)
    return (ERROR);
  return (log_nok("EVENT Unable To Join Team [Id %d] [Team: %s] [Slots: %d]",
		  sock->_fd, data, (t ? t->_slots : 0)));
}

int		application_exec_cycle(t_socket *sock)
{
  t_list	*it;
  t_exec	*elem;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (sock->_socket_type == SERVER || sock->_application._type != IA)
    return (OK);
  if (cmd_ia_death(sock) == ERROR)
    return (ERROR);
  if (!(it = sock->_application._exec) || !(elem = it->_elem))
    return (OK);
  if (--(elem->_delay) <= 0)
    {
      strcpy(sock->_buff._args_buff, elem->_args);
      if (elem->_func(sock) == ERROR)
	return (ERROR);
      list_pop_head(&(sock->_application._exec), &exec_del_func);
      (sock->_application._nb_exec)--;
    }
  return (OK);
}

int		application_exec_cycle_eggs(void)
{
  t_list	**teams;
  t_list	*it;

  if ((teams = get_list_teams()) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *teams; it != NULL; it = it->_next)
    if (it->_elem && cook_eggs(it->_elem) == ERROR)
      return (ERROR);
  return (OK);
}
