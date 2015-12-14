//
// Sound.cpp for RType in /home/Volto/Rendu/RType/client/src
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:40:49 2015 Probola
// Last update Fri Nov 20 13:47:04 2015 Probola
//

#include				"Sound.hpp"

Sound::Sound()
{
  _buffer = NULL;
  _sound = NULL;
  _music = NULL;
}

Sound::~Sound()
{
  if (_music)
    {
      _music->stop();
      delete(_music);
    }
  if (_sound)
    {
      _sound->stop();
      delete(_sound);
    }
  if (_buffer)
    {
      delete(_buffer);
    }
}

bool					Sound::initializeSound(const std::string &file, bool loop, int start, int volume)
{
  _buffer = new sf::SoundBuffer;
  _sound = new sf::Sound;
  if (!_buffer->loadFromFile(file))
    {
      std::cerr << "Cannot load " << file << std::endl;
      return false;
    }
  _sound->setBuffer(*_buffer);
  _sound->setLoop(loop);
  _sound->setPlayingOffset(sf::seconds(start));
  _sound->setVolume(volume);
  return true;
}

void					Sound::playSound()
{
  _sound->play();
}

bool					Sound::initializeMusic(const std::string &file, bool loop)
{
  _music = new sf::Music;
  if (!_music->openFromFile(file))
    {
      std::cerr << "Cannot load " << file << std::endl;
      return false;
    }
  _music->setLoop(loop);
  _music->setVolume(20);
  return true;
}

void					Sound::playMusic()
{
  _music->play();
}
