#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include "Player.hpp"
# include "Board.hpp"
# include "Computer.hpp"

class Gomoku
{
public:
	Gomoku( void );
	Gomoku( bool comp );
 	~Gomoku( void );
	Gomoku( Gomoku const & src );

	Gomoku &	operator=( Gomoku const & rhs );

	void		play();
	void		turns(Player* p1, Player* p2);

private:
	Board*		_currentBoard;
	Player*		_player1;
	Player*		_player2;

};

#endif