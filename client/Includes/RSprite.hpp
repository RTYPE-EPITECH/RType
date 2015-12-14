//
// Sprite.hpp for RType in /home/Volto/Rendu/RType/client/inc
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Nov 24 16:32:34 2015 Probola
// Last update Mon Dec 14 10:15:44 2015 Probola
//

#ifndef				_RSPRITE_HPP_
# define			_RSPRITE_HPP_

#include			<iostream>
#include			"TextureFactory.hpp"
#include                "SFML.hpp"
#include                "SFML/Audio.hpp"
#include                "SFML/Config.hpp"
#include                "SFML/Graphics.hpp"
#include                "SFML/Network.hpp"
#include                "SFML/System.hpp"
#include                "SFML/Window.hpp"

class				RSprite
{
  sf::Sprite			_sprite;
  TextureFactory		*_textureFactory;

public:
  RSprite(const std::string &, const std::string &, float, float);
  ~RSprite();
  void				setPosition(float x, float y);
};

#endif
