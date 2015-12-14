//
// SpriteFactory.hpp for RType in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Nov 24 16:51:40 2015 Probola
// Last update Sun Dec  6 23:33:12 2015 Probola
//

#ifndef					_SPRITEFACTORY_HPP_
# define				_SPRITEFACTORY_HPP_

#include				"RSprite.hpp"

class					SpriteFactory
{
private:
  std::map<std::string, RSprite *>	_stack;
  bool					_exist(const std::string &);

public:
  SpriteFactory();
  ~SpriteFactory();
  bool					initialize(std::string &, std::string &);
};

#endif
