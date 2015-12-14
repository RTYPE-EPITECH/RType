//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:34:58 2015 Probola
// Last update Sat Dec 12 18:05:31 2015 Probola
//

#include			"TextureFactory.hpp"

TextureFactory::Texture()
{

}

TextureFactory::~Texture()
{

}

bool			TextureFactory::initialize(const std::string &name, const std::string &file)
{
  if (!exist(name))
    {
      Texture		*text(name, file);
      if (text != 0)
	this->_stack[name] = text;
      else
	return false;
    }
  return true;
}

bool			TextureFactory::_exist(const std::string &name)
{
  if (this->_stack.count(file) == 0)
    return false;
  return true;
}

bool			TextureFactory::setAssets()
{
  int			i = 0;
  std::string		FileToLoad = "client/Assets/r-typesheet";

  while (i < 45)
    {
      initialize(FileToLoad + NumberToString(i) + ".gif";
      i++;
    }
}
