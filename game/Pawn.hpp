#ifndef PAWN_HPP
# define PAWN_HPP

# include <iostream>
# include <vector>
// # include "Alignement.hpp"
class Alignement;
class Pawn
{
public:
	Pawn( void );
	Pawn( int player, int x, int y );
 	~Pawn( void );
	Pawn( Pawn const & src );

	Pawn &	operator=( Pawn const & rhs );

	int		getPlayer();
	int		getX();
	int		getY();
	std::vector<Alignement*>		getAlignements();

private:
	int							_player;
	int							_x;
	int							_y;
public:
	std::vector<Alignement*>	_alignements;
};

#endif