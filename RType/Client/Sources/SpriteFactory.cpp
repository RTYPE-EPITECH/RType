//
// SpriteFactory.cpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Sun Dec  6 23:24:03 2015 Probola
// Last update Mon Dec  7 00:40:55 2015 Probola
//

#include			"SpriteFactory.hpp"

SpriteFactory::SpriteFactory()
{

}

SpriteFactory::~SpriteFactory()
{

}

bool		SpriteFactory::initialize(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (!exist(name))
    {
      RSprite			*sprite(name, TextureName, x, y);
      if (sprite != 0)
	_stack[name] = sprite;
      else
	return false;
    }
  return true;
}

bool		SpriteFactory::_exist(const std::string &name)
{
  if (this->_stack.count(file) == 0)
    return false;
  return true;
}
