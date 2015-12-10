//
// Sprite.hpp for RType in /home/Volto/Rendu/RType/client/inc
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Nov 24 16:32:34 2015 Probola
// Last update Mon Dec  7 00:58:28 2015 Probola
//

#ifndef				_RSPRITE_HPP_
# define			_RSPRITE_HPP_

#include			<iostream>
#include			"Texture.hpp"

class				RSprite
{
  sf::Sprite			_sprite;
  TextureFactory		*_textureFactory;

public:
  RSprite(const std::string &, );
  ~RSprite();
  void				setPosition(float x, float y);
};

#endif
