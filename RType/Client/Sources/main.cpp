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
    while (ui.isOpen())
      {
		  if (!texturefactory->setAssets())
			  break;
	ui.clear();
	ui.update("test", PLAYER, 100, 100);
	ui.display();
      }
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
  }
#ifdef _WIN32
  getchar();
#endif
}
