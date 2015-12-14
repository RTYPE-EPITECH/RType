//
// SoundFactory.hpp for probol_c in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:22:47 2015 Probola
// Last update Fri Nov 20 13:26:38 2015 Probola
//

#ifndef					__SOUND_FACTORY_HPP__
# define				__SOUND_FACTORY_HPP__

#include				"Sound.hpp"

class					SoundFactory
{
  std::map<std::string, Sound *>	_stack;

private:
  bool					_exist(const std::string &);
  Sound					*_load(const std::string &, bool, int, int);
public:
  SoundFactory();
  ~SoundFactory();

  bool					initialize(const std::string &, bool, int, int);
  bool					play(const std::string &);
};

#endif				/* __SOUND_FACTORY_HPP_ */

