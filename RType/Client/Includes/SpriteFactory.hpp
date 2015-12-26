//
// SpriteFactory.hpp for RType in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Nov 24 16:51:40 2015 Probola
// Last update Wed Dec 16 19:09:59 2015 Probola
//

#ifndef					_SPRITEFACTORY_HPP_
# define				_SPRITEFACTORY_HPP_

#include				<iostream>
#include				<map>
#include				"EObject.hpp"
#include 			<vector>

class					RSprite;

class					SpriteFactory
{
private:
  bool					_exist(const std::string &);

public:
  std::map<std::string, RSprite *>	_stack;

  SpriteFactory();
  ~SpriteFactory();
  std::vector<RSprite *> getAllSprite();
  bool					initialize(const std::string &, EObject, float x, float y);
};

#endif
