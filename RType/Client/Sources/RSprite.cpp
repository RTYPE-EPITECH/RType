//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Mon Dec 21 16:43:22 2015 Probola
//

#include			<string>
#include			"RSprite.hpp"

RSprite::RSprite(EObject type, float x, float y)
{
  _textureFactory = TextureFactory::getInstance();

  static bool				check = true;
  static std::map<EObject, int *>	gen;
  int					player[4] = {100, 0, 33, 25};
  int					missile[4] = {0, 0, 0, 0};
  int					obstacle[4] = {0, 0, 0, 0};
  int					monster[4] = {0, 0, 0, 0};

  if (check)
    {
      gen[PLAYER] = player;
      gen[MISSILE] = missile;
      gen[OBSTACLE] = obstacle;
      gen[MONSTER] = monster;
      check = false;
    }
  if (gen.count(type) > 0)
    {
      this->_sprite.setTexture(this->_textureFactory->_stack[type]->_texture, false);
      this->_sprite.setTextureRect(sf::IntRect(gen[type][0], gen[type][1], gen[type][2], gen[type][3]));
      this->_sprite.setPosition(x, y);
      this->_sprite.setScale(2, 2);
    }
  else
    throw std::runtime_error(std::string("Texture does not exist : " + Tools::NumberToString((int)type)) + " x : " + Tools::NumberToString((int)x) + " y " + Tools::NumberToString((int)y));
}

RSprite::~RSprite() {}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
