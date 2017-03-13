/*
** cmd_ia_voir.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Jun 29 15:04:01 2015 Thibaud Auzou
** Last update Fri Jul  3 14:45:46 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_voir(t_socket *sock)
{
  t_application	*app;
  char		*buff;
  int		size;
  int		i;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  size = BUFF_SIZE * 4;
  if ((buff = malloc(sizeof(char) * size)) == NULL)
    return (log_err("ERROR [malloc cmd_ia_voir]: ", 1, 1));
  memset(buff, 0, size);
  buff[0] = '{';
  size -= 4;
  for (i = 0; i <= app->_lvl; ++i)
    if (cmd_ia_voir_line(app, &buff, &size, i) == ERROR)
      {
	free(buff);
	return (ERROR);
      }
  strcat(buff, "}\n");
  return (add_msg_to_buffer_nodup(&(sock->_buff), buff));
}

int		cmd_ia_voir_line(t_application *app,
				 char **buff,
				 int *size,
				 int line)
{
  t_direction	dir;
  int		x;
  int		y;
  int		i;

  dir = (app->_direction + 1) % 4;
  if (app->_direction == TOP || app->_direction == LEFT)
    x = (app->_x - line) % get_size_x();
  else
    x = (app->_x + line) % get_size_x();
  if (app->_direction == TOP || app->_direction == RIGHT)
    y = (app->_y - line) % get_size_y();
  else
    y = (app->_y + line) % get_size_y();
  for (i = 0; i < ((line * 2) + 1); ++i)
    {
      if (line > 0 && cmd_ia_voir_strcat(buff, size, ", ") == ERROR)
	return (ERROR);
      if (cmd_ia_voir_case(buff, size, x, y) == ERROR)
	return (ERROR);
      cmd_ia_avance_update_coord(&x, &y, dir);
    }
  return (OK);
}

int		cmd_ia_voir_case(char **buff, int *size, int x, int y)
{
  t_list	**kase;
  t_list	*it;

  if ((kase = board_get_at_coord(x, y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *kase; it != NULL; it = it->_next)
    {
      if (it != *kase && cmd_ia_voir_strcat(buff, size, " ") == ERROR)
	return (ERROR);
      if (cmd_ia_voir_type(buff, size, it->_elem) == ERROR)
	return (ERROR);
    }
  return (OK);
}

int		cmd_ia_voir_type(char **buff, int *size, t_item *i)
{
  if (!buff || !(*buff) || !size || !i)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (i->_type == PLAYER)
    return (cmd_ia_voir_strcat(buff, size, "joueur"));
  else if (i->_type == FOOD)
    return (cmd_ia_voir_strcat(buff, size, "nourriture"));
  else if (i->_type == ROCK)
    return (cmd_ia_voir_strcat(buff, size, ((t_rock *)(i->_item))->_name));
  return (OK);
}

int		cmd_ia_voir_strcat(char **buff, int *size, char *str)
{
  char		*new;

  if (!buff || !(*buff) || !size || !str)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (*size < (int)(strlen(str) + 3))
    {
      *size = strlen(*buff) + BUFF_SIZE;
      if ((new = malloc(sizeof(char) * (*size))) == NULL)
	return (log_err("ERROR [malloc cmd_ia_voir_strcat]: ", 1, 1));
      memset(new, 0, *size);
      *size -= (strlen(*buff) + 3);
      strcpy(new, *buff);
      free(*buff);
      *buff = new;
    }
  strcat(*buff, str);
  *size -= strlen(str);
  return (OK);
}
