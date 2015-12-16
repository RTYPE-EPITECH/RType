//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Wed Dec 16 19:29:13 2015 Probola
//

#include			"RSprite.hpp"

RSprite::RSprite(EObject type, float x, float y)
{
  _textureFactory = TextureFactory::getInstance();
  if (type == 1)
    {
      this->_sprite.setTexture(this->_textureFactory->_stack["1"]->_texture, false);
      this->_sprite.setTextureRect(sf::IntRect(100, 0, 25, 25));
      this->_sprite.setPosition(x, y);
    }
  else
    throw std::runtime_error("Texture does not exist.");
}

RSprite::~RSprite()
{

}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
