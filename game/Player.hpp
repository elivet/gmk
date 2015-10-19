#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Board.hpp"

class Player
{
public:
	Player( void );
	Player( int name );
 	virtual ~Player( void );
	Player( Player const & src );

	Player &	operator=( Player const & rhs );

	virtual std::pair<int, int>			play(Board* currentBoard);

	int			getName();


protected:
	int		_name;
	int		_capturedPawns;

};

#endif