/*
** dump_teams.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 21:07:47 2015 Thibaud Auzou
** Last update Sat Jul  4 21:29:06 2015 Thibaud Auzou
*/

#include "server.h"

void				dump_teams(void)
{
  t_list			**list;
  t_list			*it;

  if ((list = get_list_teams()) == NULL)
    return;
  printf("---------- TEAMS ---------\n");
  for (it = *list; it != NULL; it = it->_next)
    if (it->_elem)
      dump_team(it->_elem);
  if ((list = get_list_socket()) == NULL)
    return;
  printf("---------- CLIENTS ---------\n");
  for (it = *list; it != NULL; it = it->_next)
    if (it->_elem)
      dump_client(it->_elem);
}

void				dump_client(t_socket *c)
{
  if (!c)
    return;
  printf("[Client: %d] ", c->_fd);
  if (c->_socket_type == SERVER)
    printf("[Type: %s]", "SERVER");
  else
    {
      printf("[Type :%s] ", "CLIENT");
      if (c->_application._type == IA)
	{
	  printf("[App: IA]");
	  printf(" [Team: %s]", c->_application._team->_name);
	  printf(" [Lvl: %d]", c->_application._lvl);
	}
      else if (c->_application._type == GRAPHIC)
	printf("[App: GRAPHIC]");
      else
	printf("[App: UNKNOWN]");
    }
  printf("\n");
}

void				dump_team(t_team *t)
{
  t_list			*tmp;
  t_socket			*sock;
  int				go;

  if (!t)
    return;
  printf("[Team: %d] [Name: %s] [Nb Members: %d] [Slots: %d] {",
	 t->_id, t->_name, t->_nb_members, t->_slots);
  go = 0;
  for (tmp = t->_members; tmp != NULL; tmp = tmp->_next)
    if ((sock = tmp->_elem))
      {
	printf("%s%d", (go ? ", " : ""), sock->_fd);
	go = 1;
      }
  printf("}\n");
}
