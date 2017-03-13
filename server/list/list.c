/*
** list.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 16:49:09 2015 Thibaud Auzou
** Last update Fri Jul  3 14:46:09 2015 Thibaud Auzou
*/

#include "server.h"

int			add_to_list_end(t_list **begin, void *elem)
{
  t_list		*it;
  t_list		*cursor;
  t_list		*new_link;

  if (begin == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((new_link = malloc(sizeof(t_list))) == NULL)
    return (log_err("ERROR [malloc add_to_list_end]: ", 1, 1));
  for (it = *begin, cursor = it; it != NULL; cursor = it, it = it->_next);
  new_link->_next = NULL;
  new_link->_prev = cursor;
  new_link->_elem = elem;
  if (cursor == NULL)
    *begin = new_link;
  else
    cursor->_next = new_link;
  return (OK);
}

int			add_to_list_begin(t_list **begin, void *elem)
{
  t_list		*new_link;

  if (begin == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((new_link = malloc(sizeof(t_list))) == NULL)
    return (log_err("ERROR [malloc add_to_list_begin]: ", 1, 1));
  new_link->_next = *begin;
  new_link->_prev = NULL;
  new_link->_elem = elem;
  if (*begin != NULL)
    (*begin)->_prev = new_link;
  *begin = new_link;
  return (OK);
}

int			rm_from_list(t_list **begin,
				     void *elem,
				     t_cmp_func compare_func,
				     t_del_func destroy_func)
{
  t_list		*it;

  if (begin == NULL || compare_func == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *begin; it != NULL; it = it->_next)
    if (compare_func(elem, it->_elem))
      {
	if (it->_next != NULL)
	  it->_next->_prev = it->_prev;
	if (it->_prev != NULL)
	  it->_prev->_next = it->_next;
	if (it == *begin)
	  *begin = it->_next;
        if (destroy_func && destroy_func(it->_elem) == ERROR)
	  return (ERROR);
	free(it);
	return (OK);
      }
  return (log_nok("EVT [RmFromList] Elem Not Found"));
}

void			*find_in_list(t_list **begin,
				      void* elem,
				      t_cmp_func compare_func)
{
  t_list		*it;

  if (begin == NULL || compare_func == NULL)
    return (NULL);
  for (it = *begin; it != NULL; it = it->_next)
    if (compare_func(elem, it->_elem))
      return (it->_elem);
  return (NULL);
}

int			destroy_list(t_list **begin,
				     t_del_func destroy_func)
{
  t_list		*it;
  t_list		*cursor;

  if (begin == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *begin, cursor = it; it != NULL; it = cursor)
    {
      cursor = it->_next;
      if (destroy_func && destroy_func(it->_elem) == ERROR)
	return (ERROR);
      free(it);
    }
  *begin = NULL;
  return (OK);
}
