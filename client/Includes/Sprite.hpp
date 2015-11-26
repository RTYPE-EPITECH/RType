//
// Sprite.hpp for RType in /home/Volto/Rendu/RType/client/inc
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Nov 24 16:32:34 2015 Probola
// Last update Tue Nov 24 16:51:17 2015 Probola
//

#ifndef				_SPRITE_HPP_
# define			_SPIRTE_HPP_

#include			<iostream>

class				Sprite
{
private:
  sf::Sprite			sprite;

public:
  bool				initializeSprite(std::string &, std::string &);
  void				displaySprite();
};

#endif
