//
// Texture.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:50:02 2015 Probola
// Last update Thu Nov 26 19:15:54 2015 Probola
//

#ifndef				_TEXTURE_HPP_
# define			_TEXTURE_HPP_

class				Texture
{
private:
  sf::Texture			_texture;

  bool				_exist(std::string &);
  Texture			*_load(std::string &);

public:
  Texture();
  ~Texture();
  bool				initializeTexture(std::string &);
};

#endif
