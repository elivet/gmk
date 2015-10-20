#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include "Player.hpp"
# include "Board.hpp"
# include "Computer.hpp"
#include "../engine/OpenGlLib.hpp"
#include "../core/GameObject.hpp"

class Gomoku: public GameObject
{
public:
	Gomoku( void );
	Gomoku( bool comp );
 	~Gomoku( void );
	Gomoku( Gomoku const & src );

	Gomoku &	operator=( Gomoku const & rhs );

	void		play();
	void		turns(Player* p1, Player* p2);

	virtual int					update( OpenGlLib *	_renderLib, double delta );
	virtual int					render( OpenGlLib *	_renderLib ) const;

private:
	Board*		_currentBoard;
	Player*		_player1;
	Player*		_player2;

};

#endif