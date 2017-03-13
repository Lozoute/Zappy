/*
** application_ia.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 14:01:18 2015 Thibaud Auzou
** Last update Fri Jul  3 15:19:58 2015 Thibaud Auzou
*/

#include "server.h"

const t_cmd		g_ia_cmds[] =
{
  {"avance", 7, &cmd_ia_avance},
  {"droite", 7, &cmd_ia_droite},
  {"gauche", 7, &cmd_ia_gauche},
  {"voir", 7, &cmd_ia_voir},
  {"inventaire", 1, &cmd_ia_inventaire},
  {"prend", 7, &cmd_ia_prend},
  {"pose", 7, &cmd_ia_pose},
  {"expulse", 7, &cmd_ia_expulse},
  {"broadcast", 7, &cmd_ia_broadcast},
  {"incantation", 300, &cmd_ia_incantation},
  {"fork", 42, &cmd_ia_fork},
  {"connect_nbr", 0, &cmd_ia_connect_nbr},
  {NULL, 0, NULL}
};

int			application_ia_init(t_socket *sock, t_team *team)
{
  t_application		*app;
  char			buff[BUFF_SIZE];

  if (!sock || !team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  app->_connected = 1;
  app->_type = IA;
  app->_entry_point = &entry_point_ia;
  app->_team = team;
  if (take_egg(sock, team) == ERROR)
    return (ERROR);
  send_msg_graph("pnw %d %d %d %d %d %s\n", sock->_fd, app->_x,
		 app->_y, app->_direction + 1, 1, team->_name);
  app->_direction = rand() % 4;
  if (board_add_at_coord(app->_x, app->_y, PLAYER, sock) == ERROR)
    return (ERROR);
  if (add_player_to_team(team, sock) == ERROR)
    return (ERROR);
  sprintf(buff, "%d\n", app->_team->_slots);
  if (add_msg_to_buffer(&(sock->_buff), buff) == ERROR)
    return (ERROR);
  sprintf(buff, "%d %d\n", get_size_x(), get_size_y());
  log_evt("EVENT [JoinTeam] [Id %d] [Team: %s]", sock->_fd, team->_name);
  return (add_msg_to_buffer(&(sock->_buff), buff));
}

int			take_egg(t_socket *sock, t_team *team)
{
  t_egg			*egg;
  t_application		*app;

  if (!sock || !team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (team->_eggs && (egg = team->_eggs->_elem) && egg->_ready)
    {
      send_msg_graph("ebo %d\n", egg->_id);
      list_pop_head(&(team->_eggs), NULL);
      sock->_application._x = egg->_x;
      sock->_application._y = egg->_y;
      if (board_rm_at_coord(egg->_x, egg->_y, egg) == ERROR)
	return (ERROR);
      free(egg);
    }
  else
    board_generate_random_coord(&(app->_x), &(app->_y), RDM_TOLERANCE);
  return (OK);
}

int			entry_point_ia(t_socket *sock, char *data)
{
  int			i;
  char			*cmd;

  if ((cmd = strtok(data, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), KO));
  for (i = 0; g_ia_cmds[i]._name && i < NB_IA_CMD; ++i)
    if (!strcmp(cmd, g_ia_cmds[i]._name))
      return (add_cmd_to_queue(sock, g_ia_cmds[i]._delay,
			       g_ia_cmds[i]._func, i));
  return (add_msg_to_buffer(&(sock->_buff), KO));
}

int			check_incant(t_socket *sock)
{
  char			b[BUFF_SIZE * 2];
  int			ret;
  t_application		*a;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  memset(b, 0, BUFF_SIZE * 2);
  a = &(sock->_application);
  if ((ret = cmd_ia_incantation_check_conditions(sock, b)) == ERROR)
    return (ERROR);
  else if (ret == NOK)
    {
      if (add_msg_to_buffer(&(sock->_buff), KO) == ERROR)
	return (ERROR);
      return (NOK);
    }
  send_msg_graph("pic %d %d %d%s\n", a->_x, a->_y, a->_lvl, b);
  return (add_msg_to_buffer(&(sock->_buff), "elevation en cours\n"));
}

int			add_cmd_to_queue(t_socket *sock,
					 int delay,
					 t_cmd_func func,
					 int i)
{
  t_exec		*new;
  t_application		*app;
  int			ret;
  char			*args;

  if (!sock || delay < 0 || !func)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (i == 9 && (ret = check_incant(sock)) != OK)
    return ((ret == NOK ? OK : ERROR));
  app = &(sock->_application);
  if (app->_type == GRAPHIC && app->_nb_exec >= MAX_EXEC)
    return (OK);
  if ((new = malloc(sizeof(t_exec))) == NULL)
    return (log_err("ERROR [malloc add_cmd_to_queue]: ", 1, 1));
  new->_delay = delay;
  new->_func = func;
  memset(new->_args, 0, BUFF_SIZE);
  if ((args = strtok(NULL, SEP)) != NULL)
    strncpy(new->_args, args, strlen(args) % (BUFF_SIZE - 1));
  (app->_nb_exec)++;
  if (func == &cmd_ia_fork)
    send_msg_graph("pfk %d\n", sock->_fd);
  return (add_to_list_end(&(app->_exec), new));
}
