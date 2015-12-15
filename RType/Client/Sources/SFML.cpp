//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Tue Dec 15 16:25:55 2015 Probola
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
  std::string			screenshot = "screenshot";
  sf::Event			Event;
  static bool check  = true;
  static std::map<int, ACTION> gen;

  if (check)
    {
      gen[sf::Keyboard::Left] = LEFT;
      gen[sf::Keyboard::Right] = RIGHT;
      gen[sf::Keyboard::Up] = UP;
      gen[sf::Keyboard::Down] = DOWN;
      gen[sf::Keyboard::Space] = SHOOT;
      check = false;
    }
  if (win.pollEvent(Event))
    {
      if (Event.key.code == sf::Keyboard::Escape)
	{
	  win.close();
	  return UNKNOW_ACTION;
	}
      else
	if (gen.count(Event.key.code) > 0)
	  return gen[Event.key.code];
    }
  return UNKNOW_ACTION;
}

void	SFML::update(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (this->_spritefactory->initialize(name, TextureName, x, y) == true)
    this->_spritefactory->_stack[name]->setPosition(x, y);
  win.draw(this->_spritefactory->_stack[name]->_sprite);
}
