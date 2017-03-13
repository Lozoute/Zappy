/*
** cmd_ia_prend.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Jun 29 21:25:33 2015 Thibaud Auzou
** Last update Fri Jul  3 14:59:31 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_prend(t_socket *sock)
{
  char		*objet;
  t_item_type	item_type;
  t_rock_type	rock_type;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!strlen((objet = sock->_buff._args_buff)))
    return (add_msg_to_buffer(&(sock->_buff), KO));
  if (cmd_ia_prend_find_item_type(objet, &item_type, &rock_type) == ERROR)
    return (add_msg_to_buffer(&(sock->_buff), KO));
  return (cmd_ia_prend_pop_item(sock, item_type, rock_type));
}

int		cmd_ia_prend_find_item_type(char *obj,
					    t_item_type *item,
					    t_rock_type *rock)
{
  int		i;

  if (!obj || !item || !rock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!strcmp(obj, "nourriture"))
    *item = FOOD;
  else
    {
      for (i = 0; i < NB_ROCKS; ++i)
	if (!strcmp(g_rock_str[i]._name, obj))
	  {
	    *item = ROCK;
	    *rock = g_rock_str[i]._type;
	    return (OK);
	  }
      return (log_err("ERROR [Bad Type] [File: %s] [Line: %d]", 0, 0, _F, _L));
    }
  return (OK);
}

int		cmd_ia_prend_pop_item(t_socket *sock,
				      t_item_type item_type,
				      t_rock_type rock_t)
{
  t_application	*app;
  t_list	**kase;
  t_list	*it;
  t_item	*elem;
  t_rock	*rock;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if ((kase = board_get_at_coord(app->_x, app->_y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *kase; it != NULL; it = it->_next)
    if ((elem = it->_elem) && elem->_type == item_type)
      {
	rock = elem->_item;
	if (item_type == ROCK && rock && rock->_type == rock_t)
	  return (cmd_ia_prend_pop_rock(sock, rock));
	else if (item_type == FOOD)
	  return (cmd_ia_prend_pop_food(sock, kase, elem));
      }
  log_evt("EVENT [Prend Item Non Dispo] [%s]",
	  (item_type == FOOD ? "Food" : g_rock_str[rock_t]._name));
  return (add_msg_to_buffer(&(sock->_buff), KO));
}

int		cmd_ia_prend_pop_rock(t_socket *sock, t_rock *rock)
{
  t_application	*app;

  if (!sock || !rock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (board_rm_at_coord(app->_x, app->_y, rock) == ERROR)
    return (ERROR);
  app->_bag[rock->_type + 1] = (app->_bag[rock->_type + 1] + 1) % INT_MAX;
  cmd_graphic_prend(sock, rock->_type + 1);
  rocks_delete(rock);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}

int		cmd_ia_prend_pop_food(t_socket *sock,
				      t_list **kase,
				      t_item *elem)
{
  t_application	*app;

  if (!sock || !kase)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (rm_from_list(kase, elem, &board_cmp_func_by_ptr,
		   &board_del_func) == ERROR)
    return (ERROR);
  app->_bag[0] = (app->_bag[0] + 1) % INT_MAX;
  app->_pv = (app->_pv + PV_RATIO) % INT_MAX;
  food_delete();
  cmd_graphic_prend(sock, 0);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}
