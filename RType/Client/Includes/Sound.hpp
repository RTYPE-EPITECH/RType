//
// Sound.hpp for RType in /home/Volto/Rendu/RType/client/inc
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Fri Nov 20 13:27:06 2015 Probola
// Last update Tue Dec 15 17:57:49 2015 Probola
//

#ifndef					_SOUND_HPP_
# define				_SOUND_HPP_

#include				<iostream>
#include				<SFML/Audio.hpp>

class					Sound
{
private:
  sf::Music				*_music;
  sf::SoundBuffer			*_buffer;
  sf::Sound				*_sound;

public:
  Sound();
  ~Sound();
  bool					initializeSound(const std::string &, bool, float, float);
  bool					initializeMusic(const std::string &, bool);
  void					playSound();
  void					playMusic();
};

#endif
