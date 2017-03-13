/*
** cmd_graphic_welcome.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 02:21:14 2015 Thibaud Auzou
** Last update Fri Jul  3 13:57:11 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_welcome(t_socket *sock)
{
  char		buff[BUFF_SIZE];

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  sprintf(buff, "msz %d %d\n", get_size_x(), get_size_y());
  if (add_msg_to_buffer(&(sock->_buff), buff) == ERROR)
    return (ERROR);
  sprintf(buff, "sgt %d\n", get_time());
  if (add_msg_to_buffer(&(sock->_buff), buff) == ERROR)
    return (ERROR);
  if (cmd_graphic_welcome_cases(sock) == ERROR)
    return (ERROR);
  if (cmd_graphic_welcome_teams(sock) == ERROR)
    return (ERROR);
  if (cmd_graphic_welcome_players(sock) == ERROR)
    return (ERROR);
  return (cmd_graphic_welcome_eggs(sock));
}
