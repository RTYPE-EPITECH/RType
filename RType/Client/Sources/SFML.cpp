//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Mon Dec 14 14:21:19 2015 Probola
//

#include			"SFML.hpp"

SFML::SFML()
{
  this->win = sf::VideoMode(800, 800, 32);
  this->win.setFramerateLimit(60);
}

SFML::~SFML()
{

}

void				SFML::loop()
{
  int				nbr = 0;
  std::string			screenshot = "screenshot";
  sf::Event			Event;

  while (win.pollEvent(Event))
    {
      if (Event.key.code == sf::Keyboard::Escape)
	win.close();
      if (Event.key.code == sf::Keyboard::F1)
	{
	  sf::Image				Screen = win.capture();
	  Screen.saveToFile(screenshot + NumberToString(nbr) + ".jpg");
	  nbr++;
	}
      win.clear();
      win.display();
    }
}

void				SFML::update(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (this->_spritefactory->initialize(name, TextureName, x, y) == true)
    this->_spritefactory->_stack[name]->setPosition(x, y);
  win.display(this->_spritefactory->_stack[name]->_sprite);
}
