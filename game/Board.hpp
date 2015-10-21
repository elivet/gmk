#ifndef BOARD_HPP
# define BOARD_HPP

# include "Pawn.hpp"
# include <map>
# include <vector>
# include "../engine/OpenGlLib.hpp"

class Board
{
public:
	Board( void );
 	~Board( void );
	Board( Board const & src );

	Board &	operator=( Board const & rhs );

	void	insert(std::pair<int, int> xy, int player);
	void	erase(std::pair<int, int> xy);
	void	displayPawns( void );
	Pawn*	findPawn( int x, int y);
	bool 	checkwin();
	void	checkAround(std::map<std::pair<int,int>, Pawn*>::iterator it);
	int 	checkFriend(int x, int y, std::pair<int, int> key);
	std::vector<std::pair<int, int> > 	checkOpponent(int x, int y, std::pair<int, int> key);
	std::vector<std::pair<int, int> >		checkTrap(std::pair<int, int> key, std::pair<int, int> key2);
	int 	checkAlignement(std::pair<int, int> key, std::pair<int, int> key2);
	std::vector<std::pair<int, int> >	checkCapture(int x, int y);


	std::map<std::pair<int,int>, Pawn*>		getPawns();
	int 									getWin();

	int					render( OpenGlLib *	_renderLib );

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;
	int										_win;
};

#endif