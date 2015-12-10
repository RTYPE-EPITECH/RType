//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:44:12 2015 Probola
// Last update Mon Dec  7 00:59:01 2015 Probola
//

#include			"RTexture.hpp"

RTexture::RTexture(const std::string &name, const std::string &file)
{
  _name = name;
  _texture.loadFromFile(file);
  // /!\ Ca peut fail ici, pense a throw ^^ // 
}

RTexture::~RTexture()
{

}
