/*
** buffer_msg.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 16:12:35 2015 Thibaud Auzou
** Last update Fri Jul  3 14:45:02 2015 Thibaud Auzou
*/

#include "server.h"

int		add_msg_to_buffer(t_buffer *buff, char *msg)
{
  char		*new;

  if (!buff || !msg)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((new = strdup(msg)) == NULL)
    return (log_err("ERROR [malloc add_msg_to_buffer]: ", 1, 1));
  return (add_to_list_end(&(buff->_msg), new));
}

int		add_msg_to_buffer_nodup(t_buffer *buff, char *msg)
{
  return (add_to_list_end(&(buff->_msg), msg));
}
