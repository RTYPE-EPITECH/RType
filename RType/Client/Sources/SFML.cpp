//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Mon Dec  7 01:13:00 2015 Probola
//

#include			"SFML.hpp"

SFML::SFML()
{

}

SFML::~SFML()
{

}

void				SFML::loop()
{
  int				nbr = 0;
  std::string			screenshot = "screenshot";

  while (App.IsOpened())
    {
      sf::Event			Event;
      while (win.GetEvent(Event))
	{
	  if (Event.Type == sf::Event::Closed)
	    win.close();
	  if (Event.Key.Code == sf::key::F1)
	    {
	      sf::Image		Screen = win.capture();
	      Screen.SaveToFile(screenshot + NumberToString(nbr) + ".jpg");
	      nbr++;
	    }
	  /*if (Event.Key.Code == sf::key::space)
	    {
	    _soundfactory->play("shoot.mp3");
	    }*/
	  win.clear();
	  win.Display();
	}
    }
}

void				SFML::update(const std::string &name, const std::string &TextureName, float x, float y)
{
  if (this->_spritefactory->initialize(name, TextureName, x, y) == true)
    this->_spritefactory->_stack[name]->setPosition(x, y);
  win.draw();
}
