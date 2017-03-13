//
// Client.cpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sun Jun 21 19:22:02 2015 jordan sabbah
// Last update Sun Jul  5 18:33:31 2015 jordan sabbah
//

#include <unistd.h>
#include "Client.hpp"
#include "ServerCommand.hpp"

Client::Client(int port, std::string const &host)
  : _info(_engine)
{
  connect(port, host);
}

Client::Client()
  :_info(_engine)
{
}

Client::~Client(){
  _thread.join();
}

void	Client::display(){
  Window::Event	event = Window::Event::None;
  ptr		tab[] = {&Client::move, &Client::move, &Client::move, &Client::move,
			 &Client::zoom, &Client::zoom, &Client::switchTeams, &Client::Null};
  sf::Clock	clock;
  int	const	&speed = _engine.get_speed();
  ServerCommand	*task;

  while ((event = _window.event_handler()) != Window::Event::Close){
    if (_engine.get_end())
      _info.set_winner(_engine.get_winner());
    (this->*tab[event])(event);
    if ((task = _queue.get())){
      _engine.update(task);
      delete task;
    }
    if (clock.getElapsedTime() >= sf::microseconds(10000 / speed) && redraw())
      clock.restart();
  }
  _engine.end();
  _thread.stop();
}


void	Client::move(int arg){
  return _engine.move(static_cast<Map::MOVE>(arg));
}

void	Client::zoom(int arg){
  return _engine.zoom(static_cast<Map::ZOOM>(arg - Window::Event::WheelUp));
}

void	Client::switchTeams(int){
  _info.switch_team();
  return _engine.switch_team();
}

void	Client::Null(int){
  return ;
}

int	Client::redraw(){
  _window.clear();
  _engine.drawGame(_window);
  _info.draw_info(_window);
  _window.display();
  return 1;
}

void	Client::send_response(){
  ServerCommand *task;

  if (!(task = _engine.get_pending()))
    return ;
  if (!_socket.send(task))
    throw Error("could not send data to server", "Client::send_response()");
  delete task;
}

void	*connection_routine(Client *client){
  try
    {
      ServerCommand	*task;
      while (!client->_window.is_quit() && !client->_engine.get_end()){
	if (!(task = client->_socket.poll()))
	  break ;
	client->_queue.put(task);
	if (client->_engine.is_pending())
	  client->send_response();
      }
    }
  catch (Error const &e)
    {
      std::cerr << "error: " << e.what() << " in " << e.who() << std::endl;
    }
  client->_engine.end();
  return NULL;
}

bool	Client::connect(int port, std::string const &host){
  if (!_socket.connect(port, host)){
    _window.quit();
    _engine.end();
    std::cerr << "could not open socket, try with different parameters"<< std::endl;
    return false;
  }
  _thread.init(reinterpret_cast<IThread::Routine>(&connection_routine), this);
  _connected = true;
  return true;
}

extern "C" IClient *get_Client(){
    return (new Client);
  }
