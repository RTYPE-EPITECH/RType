//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Tue Dec 15 15:33:07 2015 Probola
//

#include			"RSprite.hpp"

RSprite::RSprite(const std::string &TextureName, float x, float y)
{
  this->_sprite.setTexture(this->_textureFactory->_stack[TextureName]->_texture, false);
  this->_sprite.setPosition(x, y);
}

RSprite::~RSprite()
{

}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
