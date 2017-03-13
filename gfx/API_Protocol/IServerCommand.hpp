//
// IServerCommand.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun 20 15:23:50 2015 jordan sabbah
// Last update Sat Jul  4 15:13:02 2015 jordan sabbah
//

#ifndef ISERVERCOMMAND_HPP_
# define ISERVERCOMMAND_HPP_

# include <string>
# include <vector>
# include "Orientation.hpp"

class IServerCommand{
public:
    enum Command{
    BJR,
    MSZ,
    BCT,
    TNA,
    PNW,
    PPO,
    PLV,
    PIN,
    PEX,
    PBC,
    PIC,
    PIE,
    PFK,
    PDR,
    PGT,
    PDI,
    ENW,
    EHT,
    EBO,
    EDI,
    SGT,
    SEG,
    SMG,
    SUC,
    SBP
  };
  enum Type{
    INT,
    STRING,
  };
public:
  virtual ~IServerCommand(){}
  virtual IServerCommand::Command		get_command() const = 0;
  virtual std::string const			&get_response() const = 0;
  virtual std::vector<std::string> const	&get_params() const = 0;
  virtual int					to_Int(std::string const &) const = 0;
  virtual Orientation				to_Orientation(std::string const &) const = 0;
  virtual std::string	const			&to_String(std::string const &) const = 0;
  virtual std::string const			&get_info() const = 0;
  virtual void					set_info(std::string const &) = 0;
};

#endif // !ISERVERCOMMAND_HPP_
