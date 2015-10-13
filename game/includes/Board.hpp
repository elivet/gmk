#ifndef BOARD_HPP
# define BOARD_HPP

#include "../includes/Pawn.hpp"

class Board
{
public:
	Board( void );
 	~Board( void );
	Board( Board const & src );

	Board &	operator=( Board const & rhs );

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;

};

#endif