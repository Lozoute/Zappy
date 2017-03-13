/*
** teams_eggs.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jul  1 02:16:42 2015 Thibaud Auzou
** Last update Sat Jul  4 18:33:45 2015 Thibaud Auzou
*/

#include "server.h"

int		cook_eggs(t_team *team)
{
  t_list	*it;
  t_list	*cursor;
  t_egg		*egg;

  if (!team || fry_eggs(team) == ERROR)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = team->_ceggs; it != NULL; it = cursor)
    {
      cursor = it->_next;
      if ((egg = it->_elem) && egg->_delay > 0 && !egg->_ready)
	{
	  egg->_delay--;
	  if (egg->_delay <= 0)
	    {
	      egg->_ready = 1;
	      team->_slots++;
	      if (list_pop(&(team->_ceggs), egg, &team_cmp_egg_by_ptr) == NULL)
		return (ERROR);
	      if (add_to_list_end(&(team->_eggs), egg) == ERROR)
		return (ERROR);
	      send_msg_graph("eht %d\n", egg->_id);
	    }
	}
    }
  return (OK);
}

int		fry_eggs(t_team *team)
{
  t_list	*it;
  t_list	*cursor;
  t_egg		*egg;

  if (!team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = team->_eggs; it != NULL; it = cursor)
    {
      cursor = it->_next;
      if ((egg = it->_elem))
	{
	  egg->_pv--;
	  if (egg->_pv <= 0)
	    {
	      send_msg_graph("edi %d\n", egg->_id);
	      team->_slots--;
	      if (board_rm_at_coord(egg->_x, egg->_y, egg) == ERROR)
		return (ERROR);
	      if (rm_from_list(&(team->_eggs), egg, &team_cmp_egg_by_ptr,
			       &team_del_egg_func) == ERROR)
		return (ERROR);
	    }
	}
    }
  return (OK);
}
