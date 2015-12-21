//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:34:58 2015 Probola
// Last update Wed Dec 16 19:32:49 2015 Probola
//

#include			"TextureFactory.hpp"
#include			<stdexcept>
#include			<iostream>
#include			<string>

TextureFactory::TextureFactory() {}

TextureFactory::~TextureFactory() {}

TextureFactory *	TextureFactory::getInstance()
{
  static TextureFactory * i = new TextureFactory();
  return i;
}

bool			TextureFactory::initialize(const std::string &name, const std::string &file)
{
  if (!_exist(name))
    {
      try {
	RTexture		*text = new RTexture(file);
	if (text != 0)
	  this->_stack[name] = text;
	else
	  return false;
      }
      catch (const std::runtime_error & e)
	{
	  std::cerr << e.what() << std::endl;
	  return false;
	}
    }
  return true;
}

bool			TextureFactory::_exist(const std::string &name)
{
  if (this->_stack.count(name) == 0)
    return false;
  return true;
}

bool			TextureFactory::setAssets()
{
  int			nbr = 1;

  while (nbr < 45)
    {
      if (nbr != 4 && nbr != 6 && nbr != 15)
	if (!initialize(std::to_string(nbr), "Z:/rendu/RType/RType/Client/Assets/r-typesheet" + std::to_string(nbr)+ ".gif"))
	  return (false);
      nbr++;
    }
  return true;
}
