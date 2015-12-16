//
// SpriteFactory.cpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Sun Dec  6 23:24:03 2015 Probola
// Last update Tue Dec 15 18:24:00 2015 Probola
//

#include			"SpriteFactory.hpp"
#include				"RSprite.hpp"

SpriteFactory::SpriteFactory()
{
}

SpriteFactory::~SpriteFactory()
{

}

bool		SpriteFactory::initialize(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (!_exist(name))
    {
      RSprite			*sprite = new RSprite(TextureName, x, y);
      if (sprite != 0)
	_stack[name] = sprite;
      else
	return false;
    }
  return true;
}

bool		SpriteFactory::_exist(const std::string &name)
{
  std::cout << name << std::endl;
  if (this->_stack.count(name) == 0)
    return false;
  return true;
}
