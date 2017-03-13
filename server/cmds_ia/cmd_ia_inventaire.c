/*
** cmd_ia_inventaire.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Jun 29 20:58:41 2015 Thibaud Auzou
** Last update Fri Jul  3 14:23:28 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_inventaire(t_socket *sock)
{
  t_application	*app;
  char		buff[BUFF_SIZE];
  int		size;
  char		*name;
  int		i;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  memset(buff, 0, BUFF_SIZE);
  buff[0] = '{';
  for (i = 0; i < NB_BAG; ++i)
    {
      if (i == 0)
	sprintf(&(buff[1]), "nourriture %d", app->_bag[0]);
      else
	{
	  name = g_rock_str[i - 1]._name;
	  size = strlen(buff);
	  sprintf(&(buff[size]), ", %s %d", name, app->_bag[i]);
	}
    }
  strcat(buff, "}\n");
  return (add_msg_to_buffer(&(sock->_buff), buff));
}
