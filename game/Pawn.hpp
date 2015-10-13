#ifndef PAWN_HPP
# define PAWN_HPP

class Pawn
{
public:
	Pawn( void );
 	~Pawn( void );
	Pawn( Pawn const & src );

	Pawn &	operator=( Pawn const & rhs );

private:
	int	const	_posX;
	int	const	_posY;
	int	const	_player;

};

#endif