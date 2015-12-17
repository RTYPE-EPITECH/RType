//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:44:12 2015 Probola
// Last update Wed Dec 16 18:33:54 2015 Probola
//

#include			"RTexture.hpp"
#include			<stdexcept>
#include			<iostream>

RTexture::RTexture(const std::string &file)
{
  if (!_texture.loadFromFile(file))
    {
      std::cout << "file:" << file << std::endl;
      std::string e = "Cannot load ";
      e += file;
      throw std::runtime_error(e);
    }
}

RTexture::~RTexture()
{
  std::cout << "ICI C SUPP" << std::endl;
}
