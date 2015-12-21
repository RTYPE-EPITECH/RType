//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/RType/server/src
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Tue Nov 17 18:34:01 2015 Florent BEAURAIN
// Last update Tue Dec  1 15:01:35 2015 Pierre Noel
//

#include       <iostream>
#include       "Network.hpp"
#include       "Tools.hpp"

int    			main(int argc, char **argv) {
  Network		network;
  int			retur = 0;

  try {
     if (argc == 3) {
        network.init(argv[1], argv[2]);
        network.run();
     }
     else {
        std::cerr << "Usage ./" << argv[0] << " [port] [port] " << std::endl;
        retur = 1;
     }
  }
  catch (const std::runtime_error &msg) {
    std::cout << "[ERROR]" << msg.what() << std::endl;
    retur = 1;
  }
#ifdef _WIN32
  getchar();
#endif
  return retur;
}
