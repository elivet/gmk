#ifndef BOARD_HPP
# define BOARD_HPP

# include "Pawn.hpp"
# include <map>

class Board
{
public:
	Board( void );
 	~Board( void );
	Board( Board const & src );

	Board &	operator=( Board const & rhs );

	void	insert(std::pair<int, int> xy, int player);
	void	displayPawns( void );
	Pawn*	findPawn( int x, int y);
	bool 	checkwin();
	void	checkAround(std::map<std::pair<int,int>, Pawn*>::iterator it);
	int 	checker(int x, int y, std::pair<int, int> key);
	int 	checkAlignement(std::pair<int, int> key, std::pair<int, int> key2);

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;
	int										_win;
};

#endif