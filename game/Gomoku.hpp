#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include <iostream>
# include "Player.hpp"
# include "Board.hpp"
# include "Computer.hpp"
# include "../engine/OpenGlLib.hpp"
# include "../core/GameObject.hpp"

class CoreEngine;

class Gomoku: public GameObject
{
public:
	Gomoku( void );
 	~Gomoku( void );
	Gomoku( Gomoku const & src );

	Gomoku &	operator=( Gomoku const & rhs );


	// void						stockAlignement(Player* p1, Player* p2, std::pair<int, int> xy);

	void						init( void );
	void						play( void );
	// void						turns(Player* p1, Player* p2);
	void						endGame( void );
	bool						isClicked( void );
	void						endTurn( void );
	std::pair<int, int>			getPair( void );

	void						setCoreEngine( CoreEngine * coreEngine );
	CoreEngine*					getCoreEngine( void ) const;
	virtual int					update( OpenGlLib *	_renderLib, double delta );
	virtual int					render( OpenGlLib *	_renderLib ) const;

private:
	CoreEngine *				_coreEngine;
	Board*						_currentBoard;
	Player*						_player1;
	Player*						_player2;
	bool						_firstPlayerTurn;
	double *					_lastClick;

};

#endif