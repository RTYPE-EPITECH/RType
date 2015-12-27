//
// Sprite.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Dec  1 16:09:36 2015 Probola
// Last update Sun Dec 27 22:12:50 2015 Probola
//

#include			<string>
#include			"RSprite.hpp"

RSprite::RSprite(EObject type, float x, float y)
{
  _textureFactory = TextureFactory::getInstance();

  static bool				check = true;
  static std::map<EObject, int *>	gen;
  int					player[4] = { 100, 0, 35, 18 };
  int					missile[4] = { 167, 138, 48, 15 };
  int					obstacle[4] = { 0, 71, 32, 32 };
  int					monster[4] = { 76, 52, 59, 48 };
  int					little_monster[4] = { 33, 33, 34, 33 };
  int					monster_ship[4] = { 0, 0, 34, 30 };
  
  // PIERRE : N'ESSAIE PAS CA, J'AI TEST, C'EST PAS CA LE PROBLEME ! <3
 /* int					*monster = new int[4];
  monster[0] = 0;
  monster[1] = 0;
  monster[2] = 0;
  monster[3] = 0;*/

  if (check)
    {
      gen[PLAYER] = player;
      gen[MISSILE] = missile;
      gen[OBSTACLE] = obstacle;
      gen[MONSTER] = monster;
      gen[LITTLE_MONSTER] = little_monster;
      gen[MONSTER_SHIP] = monster_ship;
      check = false;
    }
  if (gen.count(type) > 0)
    {
      this->_sprite.setTexture(this->_textureFactory->_stack.at(type)->_texture, false);
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
