#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Board.hpp"

class Player
{
public:
	Player( void );
	Player( int name, int color );
 	virtual ~Player( void );
	Player( Player const & src );

	Player &	operator=( Player const & rhs );

	virtual std::pair<int, int>			play(Board* currentBoard);

	int			getName() const;
	int			getColor() const;


protected:
	int		_name;
	int		_capturedPawns;
	int		_color;

};

#endif