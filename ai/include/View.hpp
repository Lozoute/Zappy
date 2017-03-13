//
// View.hpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 19:36:16 2015 florian hellegouarch
// Last update Sun Jul  5 17:30:54 2015 florian hellegouarch
//

#ifndef VIEW_HPP_
# define VIEW_HPP_

# include <string>
# include <iostream>
# include <vector>
# include <array>
# include <list>
# include <sstream>
# include <mutex>
# include <chrono>
# include <condition_variable>
# include "ProtocolParser.hpp"
# include "IaClientException.hpp"
# include "Random.hpp"
# include "Client.hpp"

class						View
{
public:
  enum						objectType
    {
      Food = 0,
      Linemate = 1,
      Deraumere = 2,
      Sibur = 3,
      Mendiane = 4,
      Phiras = 5,
      Thystame = 6,
      Player = 7
    };

  enum						pathAction
    {
      TakeFood = 0,
      TakeLinemate = 1,
      TakeDeraumere = 2,
      TakeSibur = 3,
      TakeMendiane = 4,
      TakePhiras = 5,
      TakeThystame = 6,
      Incantation = 7,
      Forward = 8,
      Left = 9,
      Right = 10
    };

  static const int				nbObject = 8;
  static const int				nbAction = nbObject + 3;
  static const std::string			objectName[nbObject];
  typedef std::array<unsigned char, nbObject>	Square;
  typedef std::list<pathAction>			Path;

private:
  std::vector<Square>				view;
  int						nbLine;
  char						updateNb;
  std::mutex					mutex;
  std::condition_variable			condVar;

  int						countLines();
  int						getLineStart(int l) const;

  int						getPathRec(int line,
							   unsigned char *ressources,
							   Path &p) const;
  int						countRessources(unsigned char *ressources,
								const Square &s) const;
  void						getRessources(unsigned char *ressources,
							      const Square &s, Path &p) const;
  void						signal();

public:
  View();
  ~View();

  Path						getPath(const unsigned char *ressources);
  void						update(const std::string &msg);
  void						waitUpdate(char lastUpdate);

  static bool					isUpdate(const std::string &msg);
  static int					getId(const std::string &msg);
  static void					showPath(const Path &p);

  const Square					&operator[](int i) const;
  const Square					&operator[](objectType t) const;

  const Square					&getSquare(int line, int n) const;
  const Square					&getCurrentSquare() const;
  int						getNbLine() const;
  int						getLineSize(int l) const;
  int						getNbSquare() const;
  char						getUpdateNb() const;
};

std::ostream					&operator<<(std::ostream &os,
							    const View &view);

#endif // !VIEW_HPP_
