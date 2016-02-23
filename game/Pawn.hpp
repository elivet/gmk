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
	bool 	operator==(Pawn &rhs);
	bool 	operator!=(Pawn &rhs);
	//bool 	operator==(Pawn const &other) const;

	Player*							getPlayer();
	int								getX();
	int								getY();
	std::vector<Alignement*>		getAlignements();
	void							replaceAlignement(Alignement* al1, Alignement* al2);
	void							deleteAlignement(Alignement* al);
	void							toString();
	void							setIsWinnerAlignement();
	bool							getIsInWinnerAlignement();

private:
	Player*						_player;
	int							_x;
	int							_y;
	bool						_isWinnerAlignement;
public:
	std::vector<Alignement*>	_alignements;
};

#endif