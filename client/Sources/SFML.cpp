//
// SFML.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 19:08:36 2015 Probola
// Last update Thu Dec  3 16:28:47 2015 Probola
//

#include			"SFML.hpp"

SFML::SFML()
{

}

SFML::~SFML()
{

}

bool				SFML::initialize(int size_x, int size_y, std::string &name)
{
  this->window.create(sf::VideoMode(size_x, size_y), name);
}

void				SFML::update(const std::string &name, int x, int y)
{
  this->_spritefactory->_stack[name]->setPosition(sf::Vector2f(x, y));
}
