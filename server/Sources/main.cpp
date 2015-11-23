//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/RType/server/src
// 
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
// 
// Started on  Tue Nov 17 18:34:01 2015 Florent BEAURAIN
// Last update Tue Nov 17 18:34:22 2015 Florent BEAURAIN
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
	}
	return 0;
}
