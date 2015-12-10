//
// SFML.hpp for RType in /home/Volto/Rendu/RType/client/Includes
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 18:53:48 2015 Probola
// Last update Mon Dec  7 00:33:04 2015 Probola
//

#ifndef				_SFML_HPP_
# define			_SFML_HPP_

#include			"Sprite.hpp"
#include			"SFML/RenderWindow.hpp"

class				SFML
{
  sf::RenderWindow		win(sf::videoMode(800, 800, 32), "RType");
  SpriteFactory			*_spritefactory;
  SoundFactory			*_soundfactory;

public:
  SFML();
  ~SFML();
  void				loop();
  void				update(const std::string &, int, int);
};

#endif
