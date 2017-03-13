/*
** buffer.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jun 18 18:56:46 2015 Thibaud Auzou
** Last update Tue Jun 30 02:36:05 2015 Thibaud Auzou
*/

#include "server.h"

void		buffer_init(t_buffer *buff)
{
  memset(buff->_read_buff, 0, BUFF_SIZE);
  buff->_read_pos = 0;
  buff->_msg = NULL;
}

void		buffer_copy(t_buffer *b, char *str)
{
  int		i;

  if (b && str)
    {
      for (i = 0; str[i]; ++i)
	{
	  b->_read_buff[b->_read_pos] = str[i];
	  b->_read_pos = (b->_read_pos + 1) % (BUFF_SIZE * 2);
	}
      b->_read_buff[b->_read_pos] = 0;
    }
}

void		buffer_str_copy(char *dest, char *src, int size)
{
  int		i;

  if (dest && src && size > 0)
    {
      for (i = 0; i < size; ++i)
	dest[i] = src[i];
    }
}

char		*buffer_split(t_buffer *buff, char *sep)
{
  static char	_buff[BUFF_SIZE];
  char		*substr;
  int		size;
  int		len;

  if ((substr = strstr(buff->_read_buff, sep)) == NULL)
    return (NULL);
  if ((size = substr - buff->_read_buff) > 0)
    {
      ++substr;
      strncpy(_buff, buff->_read_buff, size % BUFF_SIZE);
      _buff[size % BUFF_SIZE] = 0;
      len = strlen(substr);
      buffer_str_copy(buff->_read_buff, substr, (BUFF_SIZE * 2) - size - 1);
      buff->_read_pos = len;
      return (_buff);
    }
  buffer_str_copy(buff->_read_buff, buff->_read_buff + 1, (BUFF_SIZE * 2) - 1);
  buff->_read_pos = 0;
  return (NULL);
}
