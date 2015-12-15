//
// TextureFactory.hpp for RType in /home/Volto/Rendu/RType/client
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Mon Dec  7 00:53:03 2015 Probola
// Last update Tue Dec 15 15:58:34 2015 Probola
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

public:
 std::map<std::string, RTexture *>	_stack;

  TextureFactory();
  ~TextureFactory();
  bool					initialize(const std::string &, const std::string &);
  bool					setAssets();
};

#endif
