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
#include		"TextureFactory.hpp"

int				main(void) {
  TextureFactory	*texturefactory = TextureFactory::getInstance();
  SFML			ui;

  try {
    //ntw.init("127.0.0.1", 4242);
    //ntw.run();
    texturefactory->setAssets();
    while (ui.isOpen())
      {
	ui.endLoop();
	ui.update("Test", "first", 100, 100);
	sleep(1);
      }
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
  }
}
