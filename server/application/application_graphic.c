/*
** application_graphic.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 14:02:34 2015 Thibaud Auzou
** Last update Fri Jul  3 13:51:41 2015 Thibaud Auzou
*/

#include "server.h"

const t_cmd	g_graphic_cmds[] =
  {
    {"msz", 0, &cmd_graphic_msz},
    {"bct", 0, &cmd_graphic_bct},
    {"mct", 0, &cmd_graphic_mct},
    {"tna", 0, &cmd_graphic_tna},
    {"ppo", 0, &cmd_graphic_ppo},
    {"plv", 0, &cmd_graphic_plv},
    {"pin", 0, &cmd_graphic_pin},
    {"sgt", 0, &cmd_graphic_sgt},
    {"sst", 0, &cmd_graphic_sst},
    {NULL, 0, NULL},
  };

int		application_graphic_init(t_socket *sock)
{
  t_application	*app;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  app->_connected = 1;
  app->_type = GRAPHIC;
  app->_entry_point = &entry_point_graphic;
  app->_team = get_graphic_team();
  if (add_player_to_team(get_graphic_team(), sock) == ERROR)
    return (ERROR);
  return (cmd_graphic_welcome(sock));
}

int		entry_point_graphic(t_socket *sock, char *data)
{
  int		i;
  char		*cmd;
  char		*a;

  if ((cmd = strtok(data, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RNOT));
  for (i = 0; g_graphic_cmds[i]._name && i < NB_GRAPHIC_CMD; ++i)
    if (!strcmp(cmd, g_graphic_cmds[i]._name) && g_graphic_cmds[i]._func)
      {
	memset(sock->_buff._args_buff, 0, BUFF_SIZE);
	if ((a = strtok(NULL, SEP)) != NULL)
	  strncpy(sock->_buff._args_buff, a, strlen(a) % (BUFF_SIZE - 1));
	return (g_graphic_cmds[i]._func(sock));
      }
  return (add_msg_to_buffer(&(sock->_buff), RNOT));
}
