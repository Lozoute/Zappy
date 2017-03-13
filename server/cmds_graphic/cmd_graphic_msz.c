/*
** cmd_graphic_msz.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 15:30:58 2015 Thibaud Auzou
** Last update Fri Jul  3 13:58:53 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_msz(t_socket *sock)
{
  char		buff[BUFF_SIZE];

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  sprintf(buff, "msz %d %d\n", get_size_x(), get_size_y());
  return (add_msg_to_buffer(&(sock->_buff), buff));
}
