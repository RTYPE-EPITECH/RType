//
// SFML.hpp for RType in /home/Volto/Rendu/RType/client/Includes
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 18:53:48 2015 Probola
// Last update Sun Dec 27 21:46:11 2015 Probola
//

#ifndef				_SFML_HPP_
# define			_SFML_HPP_

#include	                "SFML.hpp"
#include		        "SFML/Audio.hpp"
#include			"SFML/Config.hpp"
#include		        "SFML/Graphics.hpp"
#include			"SFML/Network.hpp"
#include			"SFML/System.hpp"
#include			"SFML/Window.hpp"
#include			"Protocole.hpp"
#include			"EObject.hpp"
#include			<vector>

class				SpriteFactory;
class				SoundFactory;

class				SFML
{
  sf::RenderWindow		win;
  SpriteFactory			*_spritefactory;
  SoundFactory			*_soundfactory;
  sf::Clock			_clock;
  sf::Time			_time;
  float				back_x = 0;
	std::vector<std::string> list;

public:
  sf::Sprite			background;
  sf::Texture			backText;
  sf::Music			music;

  SFML();
  ~SFML();
  void				clear();
  void				display();
  bool				isOpen();
  ACTION			getInput();
  void				drawAll();
  void				update(const std::string &, EObject, float, float);
  void				Intro();
  float				getTimeElapsed();
  void				scroll();
  void				playMusic();
};

#endif
