//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Sun Dec  6 23:20:45 2015 Probola
//

#include			"RSprite.hpp"

RSprite::RSprite(const std::string &TextureName, const std::string &ObjName, float x, float y)
{
  this->_sprite.setTexture(this->_textureFactory->_stack[name]);
  this->_sprite.setPosition(x, y);
  this->_ObjName = ObjName;
}

RSprite::~RSprite()
{

}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
