//
// Texture.cpp for RType in /home/Volto/Rendu/RType/client/Sources
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:34:58 2015 Probola
// Last update Mon Dec 21 16:31:13 2015 Probola
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

bool			TextureFactory::initialize(EObject type, const std::string &file)
{
	if (!_exist(type))
	{
		try {
			RTexture		*text = new RTexture(file);
			if (text != NULL)
				this->_stack[type] = text;
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

bool			TextureFactory::_exist(EObject type)
{
  if (this->_stack.count(type) == 0)
    return false;
  return true;
}

bool			TextureFactory::setAssets()
{
	std::cout << "[TextureFactory::setAssets] : init Assets " << std::endl;

#ifdef _WIN32

	// OK LE FICHIER EXISTE (LE _ACCESS PLANTE PAS) mais il veux pas load on sait pas pq..., enjoy <3
/*
	TCHAR buffer[4096];
	GetCurrentDirectory(4096, buffer);
	_tprintf(TEXT("[TextureFactory::setAssets] : getCurrentDirectorty : %s\n"), buffer);*/
	/*if (_access("C:\\Users\\dewael_a\\Documents\\RType\\RType\\Client\\Assets\\r-typesheet1.gif", 0) == -1)
		std::cout << "NIQUE TES PUTAINS DE MORT" << std::endl;*/
	if (!initialize(PLAYER, "Assets/r-typesheet1.gif"))
		return false;
	if (!initialize(MISSILE, "Assets/r-typesheet1.gif"))
		return false;
	if (!initialize(OBSTACLE, "Assets/r-typesheet39.gif"))
		return false;
	if (!initialize(MONSTER, "Assets/r-typesheet14.gif"))
		return false;
#else
  if (!initialize(PLAYER, "RType/Client/Assets/r-typesheet1.gif"))
    return false;
  if (!initialize(MISSILE, "RType/Client/Assets/r-typesheet1.gif"))
    return false;
  if (!initialize(OBSTACLE, "RType/Client/Assets/r-typesheet39.gif"))
    return false;
  if (!initialize(MONSTER, "RType/Client/Assets/r-typesheet14.gif"))
    return false;
#endif
  return true;
}
