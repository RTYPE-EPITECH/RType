//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:34:58 2015 Probola
// Last update Tue Dec 15 17:57:09 2015 Probola
//

#include			"TextureFactory.hpp"

TextureFactory::TextureFactory()
{

}

TextureFactory::~TextureFactory()
{

}

bool			TextureFactory::initialize(const std::string &name, const std::string &file)
{
  if (!_exist(name))
    {
      RTexture		*text = new RTexture(file);
      if (text != 0)
	this->_stack[name] = text;
      else
	return false;
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
  
  return false;
}
