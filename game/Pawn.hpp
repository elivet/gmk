#ifndef PAWN_HPP
# define PAWN_HPP

# include <iostream>
# include <vector>
#include "Player.hpp"
// # include "Alignement.hpp"
class Alignement;
// class Player;
class Pawn
{
public:
	Pawn( void );
	Pawn( Player* player, int x, int y );
 	~Pawn( void );
	Pawn( Pawn const & src );

	Pawn &	operator=( Pawn const & rhs );

	Player*							getPlayer();
	int								getX();
	int								getY();
	std::vector<Alignement*>		getAlignements();

private:
	Player*						_player;
	int							_x;
	int							_y;
public:
	std::vector<Alignement*>	_alignements;
};

#endif