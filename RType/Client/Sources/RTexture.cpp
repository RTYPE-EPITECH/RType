//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:44:12 2015 Probola
// Last update Fri Dec 18 21:46:09 2015 Probola
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

RTexture::~RTexture() {}
