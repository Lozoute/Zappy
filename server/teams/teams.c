/*
** teams_manip.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 20:59:45 2015 Thibaud Auzou
** Last update Fri Jul  3 14:47:44 2015 Thibaud Auzou
*/

#include "server.h"

static t_list	**teams(void)
{
  static t_list	*_teams = NULL;

  return (&_teams);
}

t_list		**get_list_teams(void)
{
  return (teams());
}

t_team		*create_team(int id, char *name)
{
  t_team	*new;

  if (id < 0 || name == NULL)
    return (NULL);
  if ((new = malloc(sizeof(t_team))) == NULL)
    {
      log_err("ERROR [malloc create_team]: ", 1, 1);
      return (NULL);
    }
  strcpy(new->_name, name);
  new->_id = id;
  new->_members = NULL;
  new->_eggs = NULL;
  new->_ceggs = NULL;
  new->_nb_members = 0;
  new->_slots = get_number_client();
  if (add_to_list_end(teams(), new) == ERROR)
    return (NULL);
  return (new);
}

int		remove_team(t_team *elem)
{
  return (rm_from_list(teams(), elem,
		       &team_cmp_func_by_name, &team_del_func));
}

t_team		*find_team(char *name)
{
  return (find_in_list(teams(), name, &team_cmp_func_by_name_and_team));
}
