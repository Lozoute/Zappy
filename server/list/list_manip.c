/*
** list_manip.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jun 19 23:32:45 2015 Thibaud Auzou
** Last update Wed Jun 24 21:24:45 2015 Thibaud Auzou
*/

#include "server.h"

void			list_pop_head(t_list **begin, t_del_func del)
{
  t_list		*tmp;
  t_list		*tmp2;

  if (begin && *begin)
    {
      tmp = *begin;
      if (tmp->_elem && del)
	del(tmp->_elem);
      tmp2 = tmp->_next;
      free(tmp);
      if (tmp2)
	tmp2->_prev = NULL;
      *begin = tmp2;
    }
}

void			*list_pop(t_list **begin,
				  void *elem,
				  t_cmp_func cmp_func)
{
  t_list		*it;

  if (begin == NULL || cmp_func == NULL)
    return (NULL);
  for (it = *begin; it != NULL; it = it->_next)
    if (cmp_func(elem, it->_elem))
      {
	if (it->_next != NULL)
	  it->_next->_prev = it->_prev;
	if (it->_prev != NULL)
	  it->_prev->_next = it->_next;
	if (it == *begin)
	  *begin = it->_next;
	free(it);
	return (elem);
      }
  return (NULL);
}
