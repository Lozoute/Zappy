/*
** log_file.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jun 26 01:12:48 2015 Thibaud Auzou
** Last update Fri Jul  3 13:47:20 2015 Thibaud Auzou
*/

#include "server.h"

static FILE		*log_file(t_wrap_action action)
{
  static FILE		*_log = NULL;

  if (action == GET && _log == NULL)
    {
      if ((_log = fopen(LOG_FILE, "w")) == NULL)
	print_error("ERROR [fopen log_file]: ", 1);
    }
    else if (action == DESTROY && _log != NULL)
      {
	fclose(_log);
	_log = NULL;
      }
  return (_log);
}

FILE			*log_file_init(void)
{
  FILE			*file;

  if ((file = log_file(GET)) == NULL)
    return (NULL);
  log_evt("START LOG");
  return (file);
}

FILE			*get_log_file(void)
{
  return (log_file(GET));
}

void			log_file_destroy(void)
{
  log_file(DESTROY);
}
