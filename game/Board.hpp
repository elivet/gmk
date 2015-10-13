#ifndef BOARD_HPP
# define BOARD_HPP

# include "Pawn.hpp"
# include <map>

class Board
{
public:
	Board( void );
 	~Board( void );
	Board( Board const & src );

	Board &	operator=( Board const & rhs );

	void	insert(int x, int y, int player);
	void	displayPawns( void );
	Pawn*	findPawn( int x, int y);

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;

};

#endif