//
// Texture.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:50:02 2015 Probola
// Last update Mon Dec 14 10:17:21 2015 Probola
//

#ifndef				_RTEXTURE_HPP_
# define			_RTEXTURE_HPP_

#include                "SFML.hpp"
#include                "SFML/Audio.hpp"
#include                "SFML/Config.hpp"
#include                "SFML/Graphics.hpp"
#include                "SFML/Network.hpp"
#include                "SFML/System.hpp"
#include                "SFML/Window.hpp"

class				RTexture
{
  sf::Texture			_texture;
  std::string			_name;

public:
  RTexture(const std::string &name, const std::string &file);
  ~RTexture();
};

#endif
