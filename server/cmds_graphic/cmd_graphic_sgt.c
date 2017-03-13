/*
** cmd_graphic_sgt.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 16:20:33 2015 Thibaud Auzou
** Last update Fri Jul  3 13:57:35 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_sgt(t_socket *sock)
{
  char		b[BUFF_SIZE];

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  sprintf(b, "sgt %d\n", get_time());
  return (add_msg_to_buffer(&(sock->_buff), b));
}
