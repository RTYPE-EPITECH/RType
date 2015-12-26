//
// SpriteFactory.cpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Sun Dec  6 23:24:03 2015 Probola
// Last update Wed Dec 16 19:08:49 2015 Probola
//

#include				"SpriteFactory.hpp"
#include				"RSprite.hpp"

SpriteFactory::SpriteFactory() {}

SpriteFactory::~SpriteFactory() {}

bool		SpriteFactory::initialize(const std::string &name, EObject type, float x, float y)
{
  if (!_exist(name))
    {
		std::cout << "[SpriteFactory::initialize] sprite " << name << "doesn't exist" << std::endl;
      RSprite			*sprite = new RSprite(type, x, y);
      if (sprite != 0)
	_stack[name] = sprite;
      else
	return false;
    }
  std::cout << "[SpriteFactory::initialize] sprite " << name << " exists" << std::endl;
  return true;
}

bool		SpriteFactory::_exist(const std::string &name)
{
  if (this->_stack.count(name) == 0)
    return false;
  return true;
}
