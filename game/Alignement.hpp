#ifndef ALIGNEMENT_HPP
# define ALIGNEMENT_HPP

# include "Pawn.hpp"
# include "Board.hpp"
# include <vector>
// class Pawn;
// class Board;
class Alignement
{
public:
	Alignement( void );
	Alignement( Pawn* p1, Pawn* p2, Board* currentBoard );
 	~Alignement( void );
	Alignement( Alignement const & src );

	Alignement &	operator=( Alignement const & rhs );

	int			isAligned(std::pair<int, int> key, Board* currentBoard);

	int		getNbr();
	int		getNx();
	int		getPx();
	int		getNy();
	int		getPy();
	Pawn*	getPawnBegin();
	Pawn*	getPawnEnd();


	void		setPawnBegin(Pawn* pawn);
	void		setPawnEnd(Pawn* pawn);
	void		setNbr(int nbr);

private:
	Pawn*					_pawnBegin;
	Pawn*					_pawnEnd;
	int						_nx;
	int 					_ny;
	int 					_px;
	int 					_py;
	int 					_nbr;
};

#endif