//
// main.cpp for main.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/RType/server/src
// 
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
// 
// Started on  Tue Nov 17 18:34:01 2015 Florent BEAURAIN
// Last update Tue Nov 17 18:34:22 2015 Florent BEAURAIN
//

#include		"Network.hpp"

int    			main(int argc, char **argv) {
	Network		network;

	try {
		network.init();
		network.run();
	}
	return 0;
}
