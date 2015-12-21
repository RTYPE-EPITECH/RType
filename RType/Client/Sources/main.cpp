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
    ui.clear();
    std::cout << "on entre dans l'intro" << std::endl;
    ui.Intro();
    std::cout << "on sort de l'intro" << std::endl;
    while (ui.isOpen())
      {
	texturefactory->setAssets();
	ui.clear();
	ui.update("bite", PLAYER, 100, 100);
	ui.update("bite", MONSTER, 200, 200);
	ui.update("bite", OBSTACLE, 300, 300);
	ui.display();
      }
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
  }
}
