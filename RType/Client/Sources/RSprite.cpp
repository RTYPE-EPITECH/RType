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
  int					player[4] = { 0, 0, 0, 0 };
  int					missile[4] = { 0, 0, 0, 0 };
  int					obstacle[4] = { 0, 0, 0, 0 };
  int					monster[4] = { 42, 43, 44, 45 };

  // PIERRE : N'ESSAIE PAS CA, J'AI TEST, C'EST PAS CA LE PROBLEME ! <3
 /* int					*monster = new int[4];
  monster[0] = 0;
  monster[1] = 0;
  monster[2] = 0;
  monster[3] = 0;*/

  if (check)
    {
		std::cout << "[Rsprite::RSprite] : check ok" << std::endl;
      gen[PLAYER] = player;
      gen[MISSILE] = missile;
      gen[OBSTACLE] = obstacle;
      gen[MONSTER] = monster;
      check = false;
    }
  if (gen.count(type) > 0)
    {
		std::cout << "[RSprite::RSprite] : gen[type][0] : " << (int)gen[type][0] << std::endl;
		std::cout << "[RSprite::RSprite] : gen[type][1] : " << (int)gen[type][1] << std::endl;
		std::cout << "[RSprite::RSprite] : gen[type][2] : " << (int)gen[type][2] << std::endl;
		std::cout << "[RSprite::RSprite] : gen[type][3] : " << (int)gen[type][3] << std::endl;
      this->_sprite.setTexture(this->_textureFactory->_stack.at(type)->_texture, false);
	  std::cout << "[RSprite::RSprite] : Texture set" << std::endl;
	  this->_sprite.setTextureRect(sf::IntRect(gen[type][0], gen[type][1], gen[type][2], gen[type][3]));
	  std::cout << "[RSprite::RSprite] : TextureRect set" << std::endl;
      this->_sprite.setPosition(x, y);
	  std::cout << "[RSprite::RSprite] : Position set" << std::endl;
      this->_sprite.setScale(2, 2);
	  std::cout << "[RSprite::RSprite] : Scale set" << std::endl;
    }
  else
    throw std::runtime_error(std::string("Texture does not exist : " + Tools::NumberToString((int)type)) + " x : " + Tools::NumberToString((int)x) + " y " + Tools::NumberToString((int)y));
}

RSprite::~RSprite() {}

void				RSprite::setPosition(float x, float y)
{
  this->_sprite.setPosition(x, y);
}
