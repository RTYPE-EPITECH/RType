//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Mon Dec 14 17:46:34 2015 Pierre Noel
//

#include			"SFML.hpp"

sf::RenderWindow win(sf::VideoMode(800, 600), "RType");

SFML::SFML()
{
  win.setFramerateLimit(60);
}

SFML::~SFML()
{

}

bool				SFML::isOpen()
{
  return win.isOpen();
}

void				SFML::endLoop()
{
  win.clear();
  win.display();
}

ACTION				SFML::getInput()
{
  int				nbr = 0;
  std::string			screenshot = "screenshot";
  sf::Event			Event;

  if (win.pollEvent(Event))
    {
      if (Event.key.code == sf::Keyboard::Escape)
	win.close();
      /* if (Event.key.code == sf::Keyboard::F1)
	{
	  sf::Image				Screen = win.capture();
	  Screen.saveToFile(screenshot + NumberToString(nbr) + ".jpg");
	  nbr++;
	  }*/
    }
  return UNKNOW;
}

void	SFML::update(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (this->_spritefactory->initialize(name, TextureName, x, y) == true)
    this->_spritefactory->_stack[name]->setPosition(x, y);
  win.draw(this->_spritefactory->_stack[name]->_sprite);
}
