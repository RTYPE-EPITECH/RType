/*
** Game.cpp for Game in /home/mathon_j/rendu/RType/client/Sources
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:48:33 2015 Jérémy MATHON
// Last update Mon Dec 14 17:58:39 2015 Pierre Noel
*/

#include	"Game.hpp"

#ifdef	WIN32
# include	"WMutex.hpp"
#else
# include	"UMutex.hpp"
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
  _mutexInput = new WMutex();
  _mutexOutput = new WMutex();
#else
  _mutexInput = new UMutex();
  _mutexOutput = new UMutex();
#endif

  if(!(this->_mutexInput->initialize()))
    return false;
  if(!(this->_mutexOutput->initialize()))
    return false;
  this->time.start();
  try {
    thread_t.initialize(&loop, this);
  }
  catch(const std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return false;
  }
  return true;
}

static void	*Game::loop(void * arg)
{
  Game *_this = reinterpret_cast<Game *>(arg);
  SFML display;

  // check si la partie est commencée
  while ()
    {
      // Reçoit idGame idPlayer
      // Appel update (init des sprites)
      // Si reçoit Packet : OK Server a tout envoyé
      //     Client crée packet : CLIENT OK Partie commencée
      //     Changer la condition pour dire que le client démarre
    }
  while (display.isOpen())
    {
      ACTION  a = display.getInput();
      //addOutput
      // Récupérer les Input
      // les mettre dans protocole et update
      display.endLoop();
    }
  return arg;
}

void		Game::getInput(ACTION input)
{
  this->_mutexInput->lock();
  this->input.push_back(input);
  this->_mutexInput->unlock();
}

void		Game::getOutput(ACTION output)
{
  this->_mutexOutput->lock();
  this->output.push_back(output);
  this->_mutexOutput->unlock();
}

void		Game::addInput(ACTION input)
{
}

void		Game::addOutput(ACTION output)
{
}
