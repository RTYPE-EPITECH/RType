//
// SpriteFactory.hpp for RType in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Nov 24 16:51:40 2015 Probola
// Last update Tue Dec 15 18:22:53 2015 Probola
//

#ifndef					_SPRITEFACTORY_HPP_
# define				_SPRITEFACTORY_HPP_

#include				<iostream>
#include				<map>

class					RSprite;

class					SpriteFactory
{
private:
  bool					_exist(const std::string &);

public:
  std::map<std::string, RSprite *>	_stack;

  SpriteFactory();
  ~SpriteFactory();
  bool					initialize(const std::string &, const std::string &, float x, float y);
};

#endif
