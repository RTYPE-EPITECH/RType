//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Tue Dec  1 16:34:07 2015 Probola
//

#include			"Sprite.hpp"

Sprite::Sprite()
{
  _sprite = NULL;
}

Sprite::~Sprite()
{

}

bool				Sprite::initializeSprite(Texture *text, std::string &name, int x, int y, int trans)
{
  _sprite = new sf::Sprite;
  if (!_sprite.setTexture(text))
    {
      std::cerr << "Cannot load " << name << std::endl;
      return false;
    }
  if (!_sprite.setTextureRect(sf::IntRect(x, y, 32, 32)))
    {
      std::cerr << "Cannot load " << name << std::endl;
      return false;
    }
  return true;
}

void				Sprite::displaySprite()
{
  
}
