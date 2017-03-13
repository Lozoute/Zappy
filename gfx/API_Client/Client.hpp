//
// Client.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_GUI
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 19:10:03 2015 jordan sabbah
// Last update Sat Jul  4 15:39:58 2015 jordan sabbah
//

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include "IClient.hpp"
# include "Window.hpp"
# include "Loader.hpp"
# include "SafeQueue.hpp"
# include "InfoClient.hpp"
# include "GameEngine.hpp"
# include "API_Thread_C.hpp"
# include "Protocol.hpp"

class ServerCommand;

class Client : public IClient{
private:
  typedef ServerCommand*	Commands;
  typedef void		(Client::*ptr)(int);
  bool			_connected;
  GameEngine		_engine;
  Protocol		_socket;
  Thread		_thread;
  Window		_window;
  InfoClient		_info;
  SafeQueue<Commands>	_queue;
  friend void		*connection_routine(Client *);
  int			redraw();
  void			move(int);
  void			zoom(int);
  void			switchTeams(int);
  void			Null(int);
  void			send_response();
public:
  Client();
  Client(int, std::string const &);
  virtual ~Client();
  virtual bool		connect(int, std::string const &);
  virtual void		display();
};

#endif // !CLIENT_HPP_
