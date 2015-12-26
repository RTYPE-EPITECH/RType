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
#include		"Tools.hpp"

int				main(int ac, char **av) {  
  if (ac != 4)
	  std::cerr << "Usage : " << av[0] << "[ip] [portConnexion] [portGame]" << std::endl;
  else
  {
	  try {
		  Network *ntw = new Network();
		  ntw->init(av[1], Tools::charToNumber<int>(av[2]), Tools::charToNumber<int>(av[3]));
		  ntw->run();
	  }
	  catch (const std::exception &msg) {
		  std::cout << msg.what() << std::endl;
	  }
  }
#ifdef _WIN32
  getchar();
#endif
}
