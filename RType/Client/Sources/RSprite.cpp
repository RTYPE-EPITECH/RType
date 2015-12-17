//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Wed Dec 16 22:28:18 2015 Probola
//

#include			<string>
#include			"RSprite.hpp"

RSprite::RSprite(EObject type, float x, float y)
{
  _textureFactory = TextureFactory::getInstance();

  static bool			check = true;
  static std::map<EObject, int>	gen;

  if (check)
    {
      gen[PLAYER] = 1;
      gen[MISSILE] = 2;
      gen[OBSTACLE] = 3;
      gen[MONSTER] = 4;
      check = false;
    }
  if (gen.count(type) > 0)
    {
      this->_sprite.setTexture(this->_textureFactory->_stack[std::to_string(gen[type])]->_texture, false);
      this->_sprite.setTextureRect(sf::IntRect(100, 0, 25, 25));
      this->_sprite.setPosition(x, y);
    }
  else
    throw std::runtime_error("Texture does not exist.");
}

RSprite::~RSprite() {}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
