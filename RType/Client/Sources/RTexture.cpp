//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:44:12 2015 Probola
// Last update Tue Dec 15 18:57:10 2015 Probola
//

#include			"RTexture.hpp"
#include			<stdexcept>

RTexture::RTexture(const std::string &file)
{
  if (!_texture.loadFromFile(file))
    {
      std::string e = "Cannot load ";
      e += file;
      throw std::runtime_error(e);
    }
}

RTexture::~RTexture()
{

}
