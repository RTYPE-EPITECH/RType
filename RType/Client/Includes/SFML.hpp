//
// SFML.hpp for RType in /home/Volto/Rendu/RType/client/Includes
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 18:53:48 2015 Probola
// Last update Tue Dec 15 15:59:45 2015 Probola
//

#ifndef				_SFML_HPP_
# define			_SFML_HPP_

#include			"SpriteFactory.hpp"
#include			"SoundFactory.hpp"
#include	                "SFML.hpp"
#include		        "SFML/Audio.hpp"
#include			"SFML/Config.hpp"
#include		        "SFML/Graphics.hpp"
#include			"SFML/Network.hpp"
#include			"SFML/System.hpp"
#include			"SFML/Window.hpp"
#include			"Protocole.hpp"

class				SpriteFactory;
class				SoundFactory;

class				SFML
{
  sf::RenderWindow		win;
  SpriteFactory			*_spritefactory;
  SoundFactory			*_soundfactory;

public:
  SFML();
  ~SFML();
  void				endLoop();
  bool				isOpen();
  ACTION			getInput();
  void				update(const std::string &, const std::string &, float, float);
};

#endif
