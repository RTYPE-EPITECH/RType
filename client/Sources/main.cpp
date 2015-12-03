#include		"Network.hpp"
#include		"SFML.hpp"

int				main(void) {
  Network		ntw;
  SFML			ui;

  try {
    ntw.init("127.0.0.1", 4242);
    ntw.run();
    ui.initialize(800, 800, "RType");
  }
  catch (const std::exception &msg) {
    std::cout << msg.what() << std::endl;
  }
}
