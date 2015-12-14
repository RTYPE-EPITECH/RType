/*
** Game.cpp for Game in /home/mathon_j/rendu/RType/client/Sources
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:48:33 2015 Jérémy MATHON
** Last update Tue Dec  1 11:38:22 2015 Jérémy MATHON
*/

#include	"Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

bool		Game::init()
{
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
}

static	void	*Game::loop(void *)
{
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
