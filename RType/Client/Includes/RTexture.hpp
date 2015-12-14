//
// Texture.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:50:02 2015 Probola
// Last update Mon Dec  7 00:58:18 2015 Probola
//

#ifndef				_RTEXTURE_HPP_
# define			_RTEXTURE_HPP_

class				RTexture
{
  sf::Texture			_texture;
  std::string			_name;

public:
  RTexture(const std::string &name, const std::string &file);
  ~RTexture();
};

#endif
