/*
** Game.cpp for Game in /home/mathon_j/rendu/RType/client/Sources
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:48:33 2015 Jérémy MATHON
** Last update Sat Dec 26 22:27:16 2015 Jérémy MATHON
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
	_start = false;
  if(!(this->_mutexGame->initialize()))
    return false;
  this->time->start();
	this->_state = BEGINNING;
  try {
    thread_t->initialize(&loop, this);
  }
  catch (const std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return false;
  }
  return true;
}

void	Game::initConnexion(void) {
	std::vector<const char *>	_lastInput;
	std::vector<const char *>	_lastOutput;
	// check si la partie est commencée
	while (getStart() == false)
	{
		// CONNECT PACKET
		if (_state == BEGINNING) {
			this->_protocole._createConnectPacket();
			this->addOutput(this->_protocole._getLastPacket());
			std::cout << "SEND CONNECT PACKET" << std::endl;
			this->_state = CONNECT_OK;
		}
		_lastInput = this->getInput();
		//	std::cout << "[Game::loop] : input.size = " << _lastInput.size() << std::endl;
		for (unsigned int i = 0; i < _lastInput.size(); i++) {
			this->_protocole._setNewPacket(_lastInput.at(i));

			std::cout << "[Game::loop] : _getHeader.opcode = " << (int)this->_protocole._getHeaderOpcode() << std::endl;
			// RESPONSE PACKET SEND
			if (this->_protocole._getHeaderOpcode() == 0 && this->_protocole._getResponseOpcode() == 0 && this->_state == CONNECT_OK) {
				this->_protocole._createParametersPacket(0, 0);
				this->addOutput(this->_protocole._getLastPacket());
				std::cout << "SEND PARAMETERS PACKET" << std::endl;
				this->_state = PARAMETERS_SET;
			}

			// IDENTIFIANT PACKET
			if (this->_protocole._getHeaderOpcode() == 10 && this->_state == PARAMETERS_SET) {
				this->_idGame = this->_protocole._getIdentifiantNbGame();
				this->_idPlayer = this->_protocole._getIdentifiantIdPlayer();
				this->_protocole._setId(this->_idPlayer);
				this->_protocole._createResponsePacket(NONE);
				this->addOutput(this->_protocole._getLastPacket());
				std::cout << "RECEIVE ID PACKET" << std::endl;
				this->_state = ID_SET;
			}

			// INIT SPRITE PACKET
			if (this->_protocole._getHeaderOpcode() == 4 && this->_state == ID_SET) {
				this->setDisplaySFML(new SFML());
				std::cout << "RECEIVE " << this->_protocole._getArrayPositionLenght() << "sprites" << std::endl;
				for (unsigned int i = 0; i < this->_protocole._getArrayPositionLenght(); i++)
					this->_display->update(std::string((char *)(this->_protocole._getPositionSpriteData(i))),
						(EObject)(this->_protocole._getPositionType(i)),
						(float)(this->_protocole._getPositionPosX(i)),
						(float)(this->_protocole._getPositionPosY(i)));
				this->_protocole._createResponsePacket(NONE);
				this->addOutput(this->_protocole._getLastPacket());
				std::cout << "RECEIVE INIT SPRITE PACKET" << std::endl;
				this->_state = POSITION_PACKET_SET;
			}

			/*// LISTPOSITIONPACKET -- inutile
			if (this->_protocole._getHeaderOpcode() == 4 && this->_state == POSITION_PACKET_SET) {
				for (unsigned int i = 0; i < this->_protocole._getArrayPositionLenght(); i++)
					this->_display->update(std::string((char *)(this->_protocole._getPositionSpriteData(i))),
						(EObject)(this->_protocole._getPositionType(i)),
						(float)(this->_protocole._getPositionPosX(i)),
						(float)(this->_protocole._getPositionPosY(i)));
			}*/
		}
		if (this->_state == POSITION_PACKET_SET && !this->haveOutput())
		{
			this->setStart(true);
			std::cout << "The game is launched" << std::endl;
			this->_protocole._createPingPacket();
			this->addOutput(this->_protocole._getLastPacket());
			this->addOutput(this->_protocole._getLastPacket());
			this->addOutput(this->_protocole._getLastPacket());
			this->addOutput(this->_protocole._getLastPacket());
			this->addOutput(this->_protocole._getLastPacket());
		}
	}
}

void	*Game::loop(void * arg)
{
  std::cout << "Game is running ..." << std::endl;
  Game *_this = reinterpret_cast<Game *>(arg);  
  try {
    _this->initConnexion();
  }
  catch (const std::runtime_error & e)
    {
      std::cerr << "[Connexion INIT] " << e.what() << std::endl;
      return NULL;
    }
  std::vector<const char *> _lastInput;
  _lastInput.clear();
  while (_this->_display->isOpen())
    {
      if(_lastInput.size() == 0)
	_lastInput = _this->getInput();
      if (_lastInput.size() > 0) {
	std::cout << "[Game::loop] vector::size = " << _lastInput.size() << std::endl;
	_this->_protocole._setNewPacket(_lastInput[_lastInput.size()]);

	// POSITIONPACKET
	if (_this->_protocole._getHeaderOpcode() == 4) {
	  std::cout << "[Game::Loop::positionPacket] : taille tableau sprite : " << (int)_this->_protocole._getArrayPositionLenght() << std::endl;
	  for (int i = 0; i < (int)_this->_protocole._getArrayPositionLenght(); i++)
	    _this->_display->update(std::string((char *)(_this->_protocole._getPositionSpriteData(i))),
				    (EObject)(_this->_protocole._getPositionType(i)),
				    (float)(_this->_protocole._getPositionPosX(i)),
				    (float)(_this->_protocole._getPositionPosY(i)));
	}

	// DEADENTITYPACKET
	if (_this->_protocole._getHeaderOpcode() == 10) {
	  std::cout << "[Game::Loop::DeadEntityPacket]" << std::endl;
	  _this->_display->update(std::string((char *)(_this->_protocole._getDeadEntityNameData())),
				  (EObject)(_this->_protocole._getDeadEntityType()), (float)-1, (float)-1);
	}
      }
      ACTION  a = _this->_display->getInput();
      if (a != UNKNOW_ACTION)
	{
	  _this->_protocole._createActionPacket(a);
	  _this->addOutput(_this->_protocole._getLastPacket());
	}
      //_this->_protocole._createPingPacket();
      //_this->addOutput(_this->_protocole._getLastPacket());
      _this->_display->clear();
      _this->_display->display();
    }
  return arg;
}

ESTATE		Game::getState() {
	return _state;
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

std::vector<const char *>	Game::getInput()
{
  std::vector<const char *>	tmp;

  this->_mutexGame->lock();
  tmp = this->input;
  this->input.clear();
  this->_mutexGame->unlock();
  return (tmp);
}

std::vector<const char*>	Game::getOutput()
{
  std::vector<const char *>	tmp;

  this->_mutexGame->lock();
  tmp = this->output;
  this->output.clear();
  this->_mutexGame->unlock();
  return (tmp);
}

void		Game::addInput(const char *input)
{
  this->_mutexGame->lock();
  this->input.push_back(input);
  this->_mutexGame->unlock();
}

void		Game::addOutput(const char *output)
{
  this->_mutexGame->lock();
  this->output.push_back(output);
  this->_mutexGame->unlock();
}

void		Game::setDisplaySFML(SFML * sfml)
{
	_display = sfml;
	//_display->Intro();
}

bool			Game::haveInput()
{
	bool tmp = false;
	this->_mutexGame->lock();
	if (this->input.size() > 0)
		tmp = true;
	this->_mutexGame->unlock();
	return (tmp);
}

bool			Game::haveOutput()
{
	bool tmp = false;
	this->_mutexGame->lock();
	if (this->output.size() > 0)
		tmp = true;
	this->_mutexGame->unlock();
	return (tmp);
}
