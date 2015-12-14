//
// TextureFactory.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:53:03 2015 Probola
// Last update Sat Dec 12 18:06:11 2015 Probola
//

#ifndef					_TEXTUREFACTORY_HPP_
# define				_TEXTUREFACTORY_HPP_

#include				"RTexture.hpp"
#include				"Tools.hpp"

class					TextureFactory
{
  private:
  std::map<std::string, RTexture *>	_stack;
  bool					_exist(const std::string &);

public:
  TextureFactory();
  ~TextureFactory();
  bool					initialize(const std::string &);
  bool					setAssets();
};

#endif
