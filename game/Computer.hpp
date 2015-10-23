#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include "Player.hpp"
# include "Board.hpp"
// # include "Pawn.hpp"
# include "Possibility.hpp"
# include <vector>

class Computer : public Player
{
public:
	Computer( void );
 	virtual ~Computer( void );
	Computer( Computer const & src );

	Computer &	operator=( Computer const & rhs );

	std::pair<int, int>			play(Board* currentBoard);

	void								getSons(bool bill);
	void								emptyAround(int x, int y, bool bill);
	void								createSon(int x, int y);
	void								createGrandSon(int x, int y);
	void								displaySons();
	void								lookAround(int x, int y, bool bill);
	void								setWeight(int x, int y);

private:
	std::vector<Possibility*> 	_sons;
	Board* 						_currentBoard;
	Possibility*				_tmp;
};

#endif