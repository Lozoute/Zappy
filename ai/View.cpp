//
// View.cpp for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai
// 
// Made by florian hellegouarch
// Login   <helleg_f@epitech.net>
// 
// Started on  Sat Jun 20 19:43:53 2015 florian hellegouarch
// Last update Sun Jul  5 17:29:46 2015 florian hellegouarch
//

#include "View.hpp"

const std::string		View::objectName[View::nbObject] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "joueur"
  };

View::View()
{
  nbLine = 0;
  updateNb = 0;
}

View::~View()
{ }

View::Path			View::getPath(const unsigned char *ressources)
{
  unsigned char			ressourcesTmp[nbObject];
  Path				p;

  for (int i = 0; i < nbObject; i++)
    ressourcesTmp[i] = ressources[i];
  if (getNbSquare() < 1)
    {
      IaClientException::showError("no data to get path");
      return p;
    }
  getPathRec(0, ressourcesTmp, p);
  return p;
}

int				View::getPathRec(int line, unsigned char *ressources,
						 Path &p) const
{
  unsigned char			ressourcesTmp[nbObject];
  unsigned char			ressourcesTmpL[nbObject];
  unsigned char			ressourcesTmpR[nbObject];
  int				pointsForward = countRessources(ressources,
								getSquare(line, 0));
  int				pointsLeft = pointsForward;
  int				pointsRight = pointsForward;
  int				lineSize = getLineSize(line);
  Path				forwardPath;

  for (int i = 0; i < nbObject; i++)
    ressourcesTmp[i] = ressources[i];
  getRessources(ressourcesTmp, getSquare(line, 0), p);
  for (int i = 0; i < nbObject; i++)
    {
      ressourcesTmpL[i] = ressourcesTmp[i];
      ressourcesTmpR[i] = ressourcesTmp[i];
    }
  if (nbLine - 1 > line)
    pointsForward += getPathRec(line + 1, ressourcesTmp, forwardPath);
  for (int i = -1; i >= -lineSize / 2; i--)
    pointsLeft += countRessources(ressourcesTmpL, getSquare(line, i));
  for (int i = 1; i <= lineSize / 2; i++)
    pointsRight += countRessources(ressourcesTmpR, getSquare(line, i));
  if (pointsForward >= pointsLeft && pointsForward >= pointsRight)
    {
      if (nbLine - 1 != line)
	p.push_back(View::Forward);
      for (pathAction a : forwardPath)
	p.push_back(a);
      return pointsForward;
    }
  else if (pointsLeft > pointsRight
	   || (pointsLeft == pointsRight && Random::getBool()))
    {
      p.push_back(View::Left);
      for (int i = -1; i >= -lineSize / 2; i--)
	{
	  p.push_back(View::Forward);
	  getRessources(ressources, getSquare(line, i), p);
	}
      return pointsLeft;
    }
  else
    {
      p.push_back(View::Right);
      for (int i = 1; i <= lineSize / 2; i++)
	{
	  p.push_back(View::Forward);
	  getRessources(ressources, getSquare(line, i), p);
	}
      return pointsRight;
    }
}

int				View::countRessources(unsigned char *ressources,
						      const Square &s) const
{
  int				count = 0;

  if (s[Player] >= 2)
    return 0;
  if (ressources[Food])
    count += s[Food];
  for (int i = Linemate; i <= Thystame; i++)
    {
      if (ressources[i] > s[i])
	{
	  ressources[i] -= s[i];
	  count += s[i];
	}
      else
	{
	  count += ressources[i];
	  ressources[i] = 0;
	}
    }
  return count;
}

void				View::getRessources(unsigned char *ressources,
						    const Square &s, Path &p) const
{
  if (s[Player] >= 2)
    return ;
  if (ressources[Food])
    for (int i = 0; i < s[Food]; i++)
      p.push_back(TakeFood);
  for (int i = Linemate; i <= Thystame; i++)
    {
      if (ressources[i] > s[i])
	{
	  for (int j = 0; j < s[i]; j++)
	    p.push_back(static_cast<View::pathAction>(i));
	  ressources[i] -= s[i];
	}
      else
	{
	  for (int j = 0; j < ressources[i]; j++)
	    p.push_back(static_cast<View::pathAction>(i));
	  ressources[i] = 0;
	}
    }
}

void				View::signal()
{
  condVar.notify_one();
}

void				View::waitUpdate(char lastUpdate)
{
  std::unique_lock<std::mutex>	lock(mutex);
  std::chrono::seconds		timeLimit(Client::getTimeout());

  while (updateNb == lastUpdate)
    {
      if (condVar.wait_for(lock, timeLimit)
	  == std::cv_status::timeout)
	throw IaClientException("timeout", "View::waitUpdate");
    }
}

void				View::update(const std::string &msg)
{
  std::unique_lock<std::mutex>	lock(mutex);
  std::string			s = ProtocolParser::removeChars("{}", msg);
  std::istringstream		iss(s);
  unsigned int			nbSquare = 1;

  for (char c : msg)
    if (c == ',')
      nbSquare++;
  if (nbSquare > view.size())
    {
      view.resize(nbSquare);
      nbLine = countLines();
    }
  for (unsigned int i = 0; i < nbSquare; i++)
    {
      Square			&sqr = view[i];

      for (int j = 0; j < nbObject; j++)
	sqr[j] = 0;
      std::getline(iss, s, ',');
      std::istringstream	issLine(s);
      while (issLine.good())
	{
	  issLine >> s;
	  int			id = getId(s);
	  if (id != -1)
	    sqr[id]++;
	}
    }
  updateNb++;
  lock.unlock();
  signal();
}

bool				View::isUpdate(const std::string &msg)
{
  std::string			rmChars("{},");
  std::string			s(msg);
  int				i = 0;

  for (char c : s)
    {
      if (rmChars.find(c) != std::string::npos)
	s[i] = ' ';
      i++;
    }
  std::istringstream		iss(s);
  while (iss.good())
    {
      iss >> s;
      if (getId(s) == -1)
	return false;
    }
  return true;
}

int				View::getId(const std::string &msg)
{
  int				i = 0;

  while (i < nbObject)
    {
      if (objectName[i] == msg)
	return i;
      i++;
    }
  return -1;
}

void				View::showPath(const Path &p)
{
  static const std::string	actionStr[nbAction] =
    {
      "take food",
      "take linemate",
      "take deraumere",
      "take sibur",
      "take mendiane",
      "take phiras",
      "take thystame",
      "incantation",
      "move forward",
      "turn left",
      "turn right"
    };

  std::cout << "path:" << std::endl;
  for (View::pathAction a : p)
    std::cout << '\t' << actionStr[static_cast<int>(a)] << std::endl;
}

int				View::getNbSquare() const
{
  return view.size();
}

int				View::countLines()
{
  int				i = 0;
  int				n = 1;
  int				size = view.size();

  while (size > 0)
    {
      size -= n;
      n += 2;
      i++;
    }
  if (size < 0)
    return i - 1;
  return i;
}

int				View::getLineStart(int l) const
{
  return l * l;
}

int				View::getNbLine() const
{
  return nbLine;
}

int				View::getLineSize(int l) const
{
  return l * 2 + 1;
}

const View::Square		&View::getSquare(int line, int n) const
{
  return view[getLineStart(line) + getLineSize(line) / 2 + n];
}

const View::Square		&View::getCurrentSquare() const
{
  if (view.size() < 1)
    throw IaClientException("invalid view size", "View::getCurrentSquare");
  return view[0];
}

char				View::getUpdateNb() const
{
  return updateNb;
}

const View::Square		&View::operator[](int i) const
{
  return view[i];
}

const View::Square		&View::operator[](View::objectType t) const
{
  return view[static_cast<int>(t)];
}

std::ostream			&operator<<(std::ostream &os, const View &view)
{
  int				n = view.getNbSquare();

  os << n << " visibles squares" << std::endl;
  for (int i = 0; i < n; i++)
    {
      const View::Square	&sqr = view[i];

      std::cout << "square " << (i + 1) << '/' << n << ':';
      for (int j = 0; j < View::nbObject; j++)
	{
	  os << ' ';
	  os << View::objectName[j] << ": ";
	  os << static_cast<int>(sqr[j]);
	}
      os << std::endl;
    }
  return os;
}
