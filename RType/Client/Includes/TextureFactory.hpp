//
// TextureFactory.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:53:03 2015 Probola
// Last update Tue Dec 15 18:46:56 2015 Probola
//

#ifndef					_TEXTUREFACTORY_HPP_
# define				_TEXTUREFACTORY_HPP_

#include				"RTexture.hpp"
#include				"Tools.hpp"

class					RTexture;

class					TextureFactory
{
  private:
   bool					_exist(const std::string &);
  TextureFactory();
  TextureFactory(const TextureFactory &);
  TextureFactory & operator=(const TextureFactory &);
public:
  std::map<std::string, RTexture *>	_stack;

  static TextureFactory *		getInstance();
  ~TextureFactory();
  bool					initialize(const std::string &, const std::string &);
  bool					setAssets();
};

#endif
