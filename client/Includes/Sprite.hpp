//
// Sprite.hpp for RType in /home/Volto/Rendu/RType/client/inc
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Nov 24 16:32:34 2015 Probola
// Last update Tue Dec  1 16:13:38 2015 Probola
//

#ifndef				_SPRITE_HPP_
# define			_SPIRTE_HPP_

#include			<iostream>

class				Sprite
{
private:
  sf::Sprite			_sprite;

public:
  Sprite();
  ~Sprite();
  bool				initializeSprite(std::string &, std::string &);
  void				displaySprite();
};

#endif
