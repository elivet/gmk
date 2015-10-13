#ifndef PAWN_HPP
# define PAWN_HPP

# include <iostream>

class Pawn
{
public:
	Pawn( void );
	Pawn( int player );
 	~Pawn( void );
	Pawn( Pawn const & src );

	Pawn &	operator=( Pawn const & rhs );

	int		getPlayer();

private:
	int		_player;

};

#endif