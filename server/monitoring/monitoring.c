/*
** monitoring.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 21:48:10 2015 Thibaud Auzou
** Last update Sat Jul  4 18:22:16 2015 Thibaud Auzou
*/

#include "server.h"

int		monitor_environment(void)
{
  fd_set	read_s;
  fd_set	write_s;
  int		max;
  int		ret;

  while (server_running())
    {
      cycle_need_to_be_executed();
      choose_fd(&max, &read_s, &write_s);
      if ((ret = select(max, &read_s, &write_s, NULL, get_cycle())) == -1)
	log_err("ERROR [select monitor_environment] :", 1, 1);
      do_read_and_write(&read_s, &write_s);
      if (cycle_execute(GET, 0))
	print_debug();
    }
  return (clean_everything());
}

void		choose_fd(int *max, fd_set *read_s, fd_set *write_s)
{
  t_list	**sockets;
  t_list	*it;
  t_socket	*elem;

  sockets = get_list_socket();
  *max = 0;
  FD_ZERO(read_s);
  FD_ZERO(write_s);
  for (it = *sockets; it != NULL; it = it->_next)
    {
      if ((elem = it->_elem) != NULL)
	{
	  if (cycle_execute(GET, 0) && elem->_socket_type == CLIENT
	      && elem->_application._type == IA
	      && !elem->_blocked && application_exec_cycle(elem) == ERROR)
	    elem->_blocked = 1;
	  if (elem->_read_func != NULL && !elem->_blocked)
	    FD_SET(elem->_fd, read_s);
	  if (elem->_buff._msg != NULL && elem->_write_func != NULL)
	    FD_SET(elem->_fd, write_s);
	  *max = (*max <= elem->_fd ? elem->_fd + 1 : *max);
	}
    }
}

void		do_read_and_write(fd_set *read_s, fd_set *write_s)
{
  t_list	**sockets;
  t_list	*it;
  t_list	*next;
  t_socket	*elem;
  int		e;

  sockets = get_list_socket();
  for (it = *sockets; it != NULL; it = next)
    {
      next = it->_next;
      if (it->_elem != NULL)
	{
	  elem = it->_elem;
	  if ((e = do_read(elem, read_s)) == ERROR)
	    socket_client_disconnect(elem);
	  if (e != ERROR && (e = do_write(elem, write_s)) == ERROR)
	    socket_client_disconnect(elem);
	  if (e != ERROR && elem->_blocked && !elem->_buff._msg)
	    socket_client_disconnect(elem);
	}
    }
}

int		do_read(t_socket *elem, fd_set *read_s)
{
  int		e;

  if (!elem || !read_s)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (FD_ISSET(elem->_fd, read_s) && elem->_read_func)
    {
      e = elem->_read_func(elem);
      if (e == ERROR)
	return (ERROR);
      if (e == NOK)
	elem->_blocked = 1;
      return (e);
    }
  return (OK);
}

int		do_write(t_socket *elem, fd_set *write_s)
{
  if (!elem || !write_s)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (FD_ISSET(elem->_fd, write_s) && elem->_write_func)
    {
      if (elem->_write_func(elem) == ERROR)
	return (ERROR);
    }
  return (OK);
}
