#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include "Player.hpp"
# include "Board.hpp"
# include <vector>

class Computer : public Player
{
public:
	Computer( void );
 	virtual ~Computer( void );
	Computer( Computer const & src );

	Computer &	operator=( Computer const & rhs );

	virtual std::pair<int, int>			play(Board* currentBoard);

	void								getSons(Board* currentBoard);
	void								emptyAround(Board* currentBoard, int x, int y);
	// void								createSon(Board* currentBoard, int x, int y);
	void								displaySons();


private:
	std::vector<Board*>	_sons;
};

#endif