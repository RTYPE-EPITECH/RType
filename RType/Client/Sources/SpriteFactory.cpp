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

      RSprite			*sprite = new RSprite(type, x, y);
      if (sprite != 0)
	_stack[name] = sprite;
      else
	return false;
    }
  return true;
}

bool		SpriteFactory::_exist(const std::string &name)
{
  if (this->_stack.count(name) == 0)
    return false;
  return true;
}

std::vector<RSprite *> SpriteFactory::getAllSprite()
{
	std::vector<RSprite *> tmp;
	for (std::map<std::string, RSprite*>::iterator i = _stack.begin();
	i != _stack.end();
	++i)
	{
		tmp.push_back(i->second);
		//sf::Vector2f pos = i->second->_sprite.getPosition();
		//std::cout << "[Sprite : ]" << i->first << " " << pos.x << "," << pos.y << std::endl;
	}
	return tmp;
}
