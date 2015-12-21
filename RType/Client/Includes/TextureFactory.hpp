//
// TextureFactory.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:53:03 2015 Probola
// Last update Mon Dec 21 15:26:19 2015 Probola
//

#ifndef					_TEXTUREFACTORY_HPP_
# define				_TEXTUREFACTORY_HPP_

#include				"EObject.hpp"
#include				"RTexture.hpp"
#include				"Tools.hpp"

class					RTexture;

class					TextureFactory
{
  private:
   bool					_exist(EObject);
  TextureFactory();
  TextureFactory(const TextureFactory &);
  TextureFactory & operator=(const TextureFactory &);
public:
  std::map<EObject, RTexture *>		_stack;

  static TextureFactory *		getInstance();
  ~TextureFactory();
  bool					initialize(EObject, const std::string &);
  bool					setAssets();
};

#endif
