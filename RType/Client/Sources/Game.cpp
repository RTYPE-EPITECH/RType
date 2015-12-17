/*
** Game.cpp for Game in /home/mathon_j/rendu/RType/client/Sources
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:48:33 2015 Jérémy MATHON
** Last update Tue Dec 15 17:29:23 2015 Jérémy MATHON
*/

#include	"Game.hpp"

#ifdef	WIN32
# include	"WMutex.hpp"
# include	"WTimer.hpp"
# include	"WThread.hpp"
#else
# include	"UMutex.hpp"
# include	"UTimer.hpp"
# include	"UThread.hpp"
#endif

Game::Game()
{
}

Game::~Game()
{
}

bool		Game::init()
{
 #ifdef	WIN32
  _mutexGame = new WMutex();
  thread_t = new WThread();
  time = new WTimer();
#else
  _mutexGame = new UMutex();
  thread_t = new UThread();
  time = new UTimer();
#endif

  this->setStart(false);
  if(!(this->_mutexGame->initialize()))
    return false;
  this->time->start();
  try {
    thread_t->initialize(&loop, this);
  }
  catch (const std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return false;
  }
  return true;
}

void	*Game::loop(void * arg)
{
  Game *_this = reinterpret_cast<Game *>(arg);
  SFML display;
  std::vector<char *>	_lastInput;
  std::vector<char *>	_lastOutput;

  // check si la partie est commencée
  while (_this->getStart() == false)
    {
      _lastInput = _this->getInput();
      // Reçoit idGame idPlayer
      // Appel update (init des sprites)
      // Si reçoit Packet : OK Server a tout envoyé
      //     Client crée packet : CLIENT OK Partie commencée
      _this->setStart(true);
    }
  while (display.isOpen())
    {
      _lastInput = _this->getInput();
      ACTION  a = display.getInput();
      _this->_protocole._createActionPacket(a);
      _this->addOutput(_this->_protocole._getLastPacket());
      //display.endLoop();
    }
  return arg;
}

bool		Game::getStart()
{
  bool		ret;

  this->_mutexGame->lock();
  ret = this->_start;
  this->_mutexGame->unlock();
  return (ret);
}

void		Game::setStart(bool ret)
{
  this->_mutexGame->lock();
  this->_start = ret;
  this->_mutexGame->unlock();
}

std::vector<char *>	Game::getInput()
{
  std::vector<char *>	tmp;

  this->_mutexGame->lock();
  tmp = this->input;
  this->input.clear();
  this->_mutexGame->unlock();
  return (tmp);
}

std::vector<char*>	Game::getOutput()
{
  std::vector<char *>	tmp;

  this->_mutexGame->lock();
  tmp = this->output;
  this->output.clear();
  this->_mutexGame->unlock();
  return (tmp);
}

void		Game::addInput(char *input)
{
  this->_mutexGame->lock();
  this->input.push_back(input);
  this->_mutexGame->unlock();
}

void		Game::addOutput(char *output)
{
  this->_mutexGame->lock();
  this->output.push_back(output);
  this->_mutexGame->unlock();
}
