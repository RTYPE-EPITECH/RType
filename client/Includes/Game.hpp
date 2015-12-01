/*
** Game.hpp for Game in /home/mathon_j/rendu/RType/client/Includes
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:47:59 2015 Jérémy MATHON
** Last update Tue Dec  1 11:27:05 2015 Jérémy MATHON
*/

#ifndef GAME_HPP_
# define GAME_HPP_

# include	<iostream>
# include	<vector>
# include	"Protocole.hpp"
# include	"IMutex.hpp"
# include	"IThread.hpp"
# include	"ITimer.hpp"

class	Game : public Network
{
private:
  vector<char *>	input;
  vector<char *>	output;
  IMutex		*_mutexInput;
  IMutex		*_mutexOutput;
  IThread		thread_t;
  ITimer		time;

public:
  Game();
  ~Game();
  bool			init();
  static	void	*loop(void *);
  void			getInput(ACTION input);
  void			getOutput(ACTION output);
  void			addInput(ACTION input);
  void			addOutput(ACTION output);
};

#endif /* !GAME_HPP_ */
