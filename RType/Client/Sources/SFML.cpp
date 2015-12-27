//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Sun Dec 27 17:51:52 2015 Probola
//

#include			"SFML.hpp"
#include			"SpriteFactory.hpp"
#include			"SoundFactory.hpp"
#include			"RSprite.hpp"
#ifndef _WIN32
#include			<unistd.h>
#endif


SFML::SFML()
{
	std::cout << "Windows SFML Laucnhed " << std::endl;
  _spritefactory = new SpriteFactory();
  _soundfactory = new SoundFactory();
  TextureFactory	*texturefactory = TextureFactory::getInstance();
  texturefactory->setAssets();
//  (void)texturefactory;
  win.create(sf::VideoMode(800, 600), "RType");
  win.setFramerateLimit(60);
}

SFML::~SFML() {}

bool				SFML::isOpen()
{
  return win.isOpen();
}

void				SFML::clear()
{
  win.clear();
}

void				SFML::display()
{
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
      switch (Event.type)
	{
	  // window closed
	case sf::Event::Closed:
	  win.close();
	  break;

	  // key pressed
	case sf::Event::KeyPressed:
	  if (Event.key.code == sf::Keyboard::Escape)
	    {
	      win.close();
	      return UNKNOW_ACTION;
	    }
	  if (gen.count(Event.key.code) > 0)
	    return gen[Event.key.code];

	  // we don't process other types of events
	default:
	  break;
	}
    }
  return UNKNOW_ACTION;
}

void				SFML::update(const std::string &name, EObject type, float x, float y)
{
  if (this->_spritefactory->initialize(name, type, x, y) == true) {
    //std::cout << "[SFML::update] : initialize" << std::endl;
    this->_spritefactory->_stack[name]->_sprite->setPosition(x, y);
  }
  win.draw(this->_spritefactory->_stack[name]->_sprite);
}

void				SFML::Intro()
{
  sf::Texture			text;
  sf::Sprite			sprite;
  sf::Event			event;

#ifndef _WIN32
  text.loadFromFile("RType/Client/Assets/intro.gif");
#else
  text.loadFromFile("Assets/intro.gif");
#endif
  sprite.setTexture(text);
  sprite.setPosition(0, 0);
  win.draw(sprite);
  while (isOpen())
    {
      _clock.restart();
      if (win.pollEvent(event))
	{
	  if (event.type == sf::Event::KeyPressed)
	    break;
	  if (event.type == sf::Event::Closed)
            win.close();
	}
      win.clear();
      win.draw(sprite);
      win.display();
    }
}


void				SFML::drawAll()
{
  std::vector<RSprite *> tmp = _spritefactory->getAllSprite();
  for (unsigned int i = 0; i < tmp.size(); i++)
    {
      win.draw(tmp[i]->_sprite);
    }
}

float				SFML::getTimeElapsed()
{
  return (this->_time.asSeconds());
}
