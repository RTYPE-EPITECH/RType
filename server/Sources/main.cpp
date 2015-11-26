//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/RType/server/src
// 
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
// 
// Started on  Tue Nov 17 18:34:01 2015 Florent BEAURAIN
// Last update Thu Nov 26 13:12:08 2015 Pierre Noel
//

#include		<iostream>
#include		"Network.hpp"

int    			main(int argc, char **argv) {
	Network		network;

	try {
		network.init("4242");
		network.run();
	}
	catch (const std::exception &msg) {
		std::cout << msg.what() << std::endl;
		#ifndef WIN32
		#else
		getchar();
		#endif
	}
	return 0;
}
