#include		<iostream>
#include		<map>
#include		"Network.hpp"
#include		"SFML.hpp"
#include		"SFML/Audio.hpp"
#include		"SFML/Config.hpp"
#include		"SFML/Graphics.hpp"
#include		"SFML/Network.hpp"
#include		"SFML/System.hpp"
#include		"SFML/Window.hpp"

int				main(void) {
  SFML			ui;

  try {
    //ntw.init("127.0.0.1", 4242);
    //ntw.run();
   
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
  }
}
