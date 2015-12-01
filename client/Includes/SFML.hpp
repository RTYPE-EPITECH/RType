//
// SFML.hpp for RType in /home/Volto/Rendu/RType/client/Includes
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Thu Nov 26 18:53:48 2015 Probola
// Last update Thu Nov 26 19:10:23 2015 Probola
//

#ifndef				_SFML_HPP_
# define			_SFML_HPP_

#include			<SFML/Window.hpp>

class				SFML
{
  sf::window			window;

public:
  SFML();
  ~SFML();
  bool				 initialize(int size_x, int size_y, std::string &name);
  //update();
};

#endif
