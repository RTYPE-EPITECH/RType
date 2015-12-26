/*
** Game.hpp for Game in /home/mathon_j/rendu/RType/client/Includes
** 
** Made by Jérémy MATHON
** Login   <mathon_j@mathonj>
** 
** Started on  Wed Nov 25 11:47:59 2015 Jérémy MATHON
** Last update Tue Dec 15 17:30:33 2015 Jérémy MATHON
*/

#ifndef GAME_HPP_
# define GAME_HPP_

# include	<iostream>
# include	<vector>
# include	<stdexcept>
# include	"Protocole.hpp"
# include	"SFML.hpp"
# include	"IMutex.hpp"
# include	"IThread.hpp"
# include	"ITimer.hpp"
# include	"StateConnexion.hpp"

/*
typedef enum {
		BEGINNING,
		CONNECT_OK,
		PARAMETERS_SET,
		RESPONSE_SET,
		ID_SET,
		POSITION_PACKET_SET
}		ESTATE;
*/

class	Game {
private:
  std::vector<const char *>	input;
  std::vector<const char *>	output;
  IMutex		*_mutexGame;
  IThread		*thread_t;
  ITimer		*time;
  SFML			*_display;
  bool			_start;
  int			_idGame;
  int			_idPlayer;
  Protocole		_protocole;
  ESTATE		_state;

public:
  Game();
  ~Game();
  bool			init();
  static	void	*loop(void *);
  std::vector<const char *>	getInput();
  std::vector<const char *>	getOutput();

  bool			haveInput();
  bool			haveOutput();

  ESTATE		getState(void);
  void			addInput(const char *input);
  void			addOutput(const char *output);
  void			initConnexion(void);
  bool			getStart();
  void			setStart(bool ret);
  void			setDisplaySFML(SFML *);

  bool			isOpen();
};

#endif /* !GAME_HPP_ */
