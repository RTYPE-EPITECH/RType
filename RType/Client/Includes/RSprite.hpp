/*
// Sprite.hpp for RType in /home/Volto/Rendu/RType/client/inc
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Nov 24 16:32:34 2015 Probola
** Last update Tue Dec 22 17:21:45 2015 Jérémy MATHON
*/

#ifndef				_RSPRITE_HPP_
# define			_RSPRITE_HPP_

#include			<iostream>
#include			<stdexcept>
#include			"TextureFactory.hpp"
#include		        "SFML.hpp"
#include		        "SFML/Audio.hpp"
#include	        	"SFML/Config.hpp"
#include			"SFML/Graphics.hpp"
#include		        "SFML/Network.hpp"
#include	                "SFML/System.hpp"
#include			"SFML/Window.hpp"
#include			"EObject.hpp"

class				TextureFactory;

class				RSprite
{
  TextureFactory		* _textureFactory;
  /* Découpage des textures */
  float				x;
  float				y;
  /**/
public:
  sf::Sprite			_sprite;

  RSprite(EObject, float, float);
  ~RSprite();
  void				setPosition(float x, float y);
};

#endif
