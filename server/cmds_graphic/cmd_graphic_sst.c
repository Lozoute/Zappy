/*
** cmd_graphic_sst.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 16:22:06 2015 Thibaud Auzou
** Last update Sun Jul  5 01:12:24 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_sst(t_socket *sock)
{
  char		*arg;
  int		val;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((arg = strtok(sock->_buff._args_buff, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  if ((val = atoi(arg)) < 1 || val > MAX_T)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  set_time(val);
  get_cycle_number(CLEAN);
  get_average_cycle(CLEAN, 0);
  cycle_delta(CLEAN, 0);
  first_cycle(CLEAN);
  return (cmd_graphic_sgt(sock));
}
