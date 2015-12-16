//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Tue Dec 15 19:01:41 2015 Probola
//

#include			"RSprite.hpp"

RSprite::RSprite(const std::string &TextureName, float x, float y)
{
  _textureFactory = TextureFactory::getInstance();
  if (this->_textureFactory->_stack.count(TextureName) > 0)
    {
      sf::Texture u = this->_textureFactory->_stack[TextureName]->_texture;
      this->_sprite.setTexture(u, false);
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
