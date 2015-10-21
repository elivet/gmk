#ifndef ALIGNEMENT_HPP
# define ALIGNEMENT_HPP

# include "Pawn.hpp"
# include <map>

class Alignement
{
public:
	Alignement( void );
 	~Alignement( void );
	Alignement( Alignement const & src );

	Alignement &	operator=( Alignement const & rhs );

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;
};

#endif