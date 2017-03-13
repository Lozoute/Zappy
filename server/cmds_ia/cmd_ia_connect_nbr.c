/*
** cmd_ia_connect_nbr.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jul  1 00:01:37 2015 Thibaud Auzou
** Last update Fri Jul  3 14:00:58 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_connect_nbr(t_socket *sock)
{
  char		buff[BUFF_SIZE];

  if (!sock || !sock->_application._team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  sprintf(buff, "%d\n", sock->_application._team->_slots);
  return (add_msg_to_buffer(&(sock->_buff), buff));
}
