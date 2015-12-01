//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/RType/server/src
// 
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
// 
// Started on  Tue Nov 17 18:34:01 2015 Florent BEAURAIN
// Last update Tue Dec  1 15:01:35 2015 Pierre Noel
//

#include		<iostream>
#include		"Network.hpp"
#include		"Tools.hpp"

int    			main(int argc, char **argv) {
  Network		network;
  bool			error = 0;
  try {
    if (argc == 2){
      network.init(argv[1]);
      network.run();
    }
    else
      {
	std::cerr << "Usage " << argv[0] << " [port] " << std::endl;
	error = 1;
      }
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
    error = 1;
#ifndef WIN_32
#else
    getchar();
#endif
  }
  return error;
}
