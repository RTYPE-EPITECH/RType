//
// SpriteFactory.hpp for RType in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Nov 24 16:51:40 2015 Probola
// Last update Tue Nov 24 16:56:26 2015 Probola
//

#ifndef					_SPRITEFACTORY_HPP_
# define				_SPRITEFACTORY_HPP_

#include				"Sprite.hpp"

class					SpriteFactory
{
private:
  std::map<std::string, Sprite *>	_stack;

  bool					_exist(const std::string &);
  Sprite				*_load(const std::string &);

public:
  bool					initialize(std::string &, std::string &);
  bool					display(std::string &);
};

#endif
