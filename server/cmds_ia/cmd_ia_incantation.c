/*
** cmd_ia_incantation.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jul  1 18:23:13 2015 Thibaud Auzou
** Last update Sun Jul  5 18:31:37 2015 florian hellegouarch
*/

#include "server.h"

int		cmd_ia_incantation(t_socket *sock)
{
  int		ret;
  t_application	*a;
  t_list	**kase;
  int		t[7];

  if (!sock || (ret = cmd_ia_incantation_check_conditions(sock, 0)) == ERROR)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  a = &(sock->_application);
  send_msg_graph("pie %d %d %d\n", a->_x, a->_y, 1);
  if (cmd_ia_incantation_raise(sock, (ret == OK ? 1 : 0)) == ERROR)
    return (ERROR);
  if ((kase = board_get_at_coord(a->_x, a->_y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  memset(t, 0, sizeof(int) * 7);
  if (cmd_graphic_welcome_case_count(*kase, t) == ERROR)
    return (ERROR);
  send_msg_graph("bct %d %d %d %d %d %d %d %d %d\n",
		 a->_x, a->_y, t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
  if (ret == OK)
    return (cmd_ia_victory(sock->_application._team));
  return (OK);
}

int		cmd_ia_incantation_check_conditions(t_socket *sock, char *b)
{
  t_application	*app;
  t_list	**kase;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (app->_lvl < 0 || app->_lvl > NB_LVL)
    {
      log_err("ERROR [Bad Lvl] [File: %s] [Line: %d]", 0, 0, _F, _L);
      return (NOK);
    }
  if ((kase = board_get_at_coord(app->_x, app->_y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  return (cmd_ia_incantation_check_case(*kase, app->_lvl, b));
}

static int	cmd_ia_incant_nok(t_socket *p, int lvl, char *b, int *ac)
{
  int		olvl;

  if (!p || !ac)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((olvl = p->_application._lvl) != lvl)
    return (log_nok("EVENT [IncantFail Lvl %d] [%s] %s [Need %d] [Got %d]",
		    lvl, (b ? "Debut" : "Fin"),
		    "Joueur D'un LVl Different Sur La Case", lvl, olvl));
  (ac[0])++;
  if (b && ac[0] < 10)
    sprintf(b + strlen(b), " %d", p->_fd);
  if (ac[0] > 10)
    return (NOK);
  return (OK);
}

int		cmd_ia_incantation_check_case(t_list *it, int lvl, char *b)
{
  int		actual[NB_LVL];
  int		i;
  t_item	*item;

  memset(actual, 0, sizeof(int) * NB_LVL);
  for (; it != NULL; it = it->_next)
    if ((item = it->_elem) != NULL)
      {
	if (item->_type == PLAYER && item->_item &&
	    cmd_ia_incant_nok(item->_item, lvl, b, actual) != OK)
	  return (NOK);
	else if (item->_type == ROCK && item->_item)
	  (actual[(((t_rock *)(item->_item))->_type + 1)])++;
      }
  for (i = 0; i < NB_LVL; ++i)
    if (actual[i] != g_elevation[lvl - 1][i])
      return (log_nok("EVENT [IncantFail Lvl %d][%s] %s [%s][Need %d][Got %d]",
		      lvl, (b ? "Debut" : "Fin"),
		      "Nombre De Ressources Sur La Case Incorrect",
		      (i == 0 ? "Player" : (g_rock_str[i - 1]._name)),
		      g_elevation[lvl - 1][i], actual[i]));
  return (OK);
}

int		cmd_ia_incantation_raise(t_socket *sock, int ok)
{
  t_application	*app;
  t_list	**kase;
  t_list	*it;
  t_list	*cursor;
  t_item	*item;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if ((kase = board_get_at_coord(app->_x, app->_y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *kase; it != NULL; it = cursor)
    {
      cursor = it->_next;
	if ((item = it->_elem) && item->_type == PLAYER && item->_item &&
	    cmd_ia_incantation_raise_player(item->_item, ok) == ERROR)
	  return (ERROR);
	else if (item && item->_type == ROCK && item->_item &&
		 cmd_ia_incantation_raise_rock(app->_x, app->_y,
					       item->_item, ok) == ERROR)
	  return (ERROR);
    }
  return (OK);
}
