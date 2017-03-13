/*
** teams.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 12:24:22 2015 Thibaud Auzou
** Last update Sat Jul  4 20:17:22 2015 Thibaud Auzou
*/

#include "server.h"

int		check_param_n(char **teams)
{
  int		i;
  t_team	*graph;

  if (teams == NULL || teams[0] == NULL || teams[1] == NULL)
    return (print_error("Minimum 2 Team (-n)", 0));
  for (i = 0; teams[i]; ++i)
    {
      if (i >= MAX_N)
	return (print_error("Too Much Teams", 0));
      if (strlen(teams[i]) > BUFF_SIZE)
	return (print_error("Team Name Too Long.", 0));
      else if (!strcasecmp("GRAPHIC", teams[i]))
	return (print_error("You Can't Name A Team \"Graphic\"", 0));
      else if (find_team(teams[i]) != NULL)
	return (print_error("Two Teams Have The Same Name.", 0));
      else if (create_team(i, teams[i]) == NULL)
	return (print_error("Unable To Create New Team", 0));
    }
  if ((graph = create_team(i, "Graphic")) == NULL)
    return (print_error("Unable To Create New Team", 0));
  else
    set_graphic_team(graph);
  return (OK);
}
