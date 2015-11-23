#include		"Network.hpp"

int				main(void) {
	Network		ntw;

	try {
		ntw.init("127.0.0.1", 4242);
		ntw.run();
	}
	catch (const std::exception &msg) {
		std::cout << msg.what() << std::endl;
	}
}