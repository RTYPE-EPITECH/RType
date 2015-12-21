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

#ifdef	_WIN32
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
 #ifdef	_WIN32
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
  this->_state = BEGINNING;
  this->_display = new SFML();
  return true;
}

void	*Game::loop(void * arg)
{
  Game *_this = reinterpret_cast<Game *>(arg);
  std::vector<char *>	_lastInput;
  std::vector<char *>	_lastOutput;
  // check si la partie est commencée
  while (_this->getStart() == false)
    {
		_lastInput = _this->getInput();
		for (unsigned int i = 0; i < _lastInput.size(); i++) {
			_this->_protocole._setNewPacket(_lastInput.at(i));
			
			// CONNECT PACKET
			if (_this->_state == BEGINNING) {
				_this->_protocole._createConnectPacket();
				_this->addOutput(_this->_protocole._getLastPacket());
				_this->_state = CONNECT_OK;
			}

			// RESPONSE PACKET SEND
			if (_this->_protocole._getHeaderOpcode() == 0 && _this->_protocole._getResponseOpcode() == 0 && _this->_state == CONNECT_OK) {
				_this->_protocole._createParametersPacket(0, 0);
				_this->addOutput(_this->_protocole._getLastPacket());
				_this->_state = PARAMETERS_SET;
			}

			// IDENTIFIANT PACKET
			if (_this->_protocole._getHeaderOpcode() == 9) {
				_this->_idGame = _this->_protocole._getIdentifiantNbGame();
				_this->_idPlayer = _this->_protocole._getIdentifiantIdPlayer();
				_this->_protocole._createResponsePacket(NONE);
				_this->addOutput(_this->_protocole._getLastPacket());
				_this->_state = ID_SET;
			}

			// LISTPOSITIONPACKET
			if (_this->_protocole._getHeaderOpcode() == 4) {
				for (unsigned int i = 0; i < _this->_protocole._getArrayPositionLenght(); i++)
					_this->_display->update(std::string((char *)(_this->_protocole._getPositionSpriteData(i))),
						(EObject)(_this->_protocole._getPositionType(i)),
						(float)(_this->_protocole._getPositionPosX(i)),
						(float)(_this->_protocole._getPositionPosY(i)));
			}
			_this->_protocole._createResponsePacket(NONE);
			_this->addOutput(_this->_protocole._getLastPacket());
			_this->_state = POSITION_PACKET_SET;
		}
      // Reçoit idGame idPlayer
      // Appel update (init des sprites)
      // Si reçoit Packet : OK Server a tout envoyé
      //     Client crée packet : CLIENT OK Partie commencée*
	  if (_this->_state == POSITION_PACKET_SET)
		  _this->setStart(true);
    }

  while (_this->_display->isOpen())
    {
      _lastInput = _this->getInput();
      ACTION  a = _this->_display->getInput();
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
