//
// SFML.hpp for RType in /home/Volto/Rendu/RType/client/Includes
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 18:53:48 2015 Probola
// Last update Thu Dec  3 16:22:06 2015 Probola
//

#ifndef				_SFML_HPP_
# define			_SFML_HPP_

#include			"Sprite.hpp"
#include			<SFML/Window.hpp>

class				SFML
{
  sf::window			_window;
  SpriteFactory			*_spritefactory;
  SoundFactory			*_soundfactory;

public:
  SFML();
  ~SFML();
  bool				 initialize(int size_x, int size_y, std::string &name);
  void				update(const std::string &, int, int);
};

#endif
