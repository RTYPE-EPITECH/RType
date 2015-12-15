//
// SoundFactory.cpp for RType in /home/Volto/Rendu/RType/client/src
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:34:30 2015 Probola
// Last update Tue Dec 15 17:58:42 2015 Probola
//

#include				"SoundFactory.hpp"

SoundFactory::SoundFactory()
{
}

SoundFactory::~SoundFactory()
{
}

bool					SoundFactory::initialize(const std::string &file, bool loop, float start, float volume)
{
  if (!_exist(file))
    {
      Sound		*sound = _load(file, loop, start, volume);
      if (sound != 0)
	_stack[file] = sound;
      else
	return false;
    }
  return true;
}

bool					SoundFactory::play(const std::string &file)
{
  if (_exist(file))
    {
      _stack[file]->playSound();
      return true;
    }
  if (initialize(file, false, 0, 100))
    {
      _stack[file]->playSound();
      return true;
    }
  return false;
}

bool					SoundFactory::_exist(const std::string &file)
{
  if (this->_stack.count(file) == 0)
    return false;
  return true;
}

Sound					*SoundFactory::_load(const std::string &file, bool loop, float start, float volume)
{
  Sound					*tmp = new Sound();

  if (!tmp->initializeSound(file, loop, start, volume))
    {
      std::cerr << "Cannot load the sound " << file << std::endl;
      return (0);
    }
  return tmp;
}
