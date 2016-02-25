#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include "Player.hpp"
# include "Board.hpp"
// # include "Pawn.hpp"
# include "Possibility.hpp"
# include "Alignement.hpp"
# include <vector>

class Computer : public Player
{
public:
	Computer( void );
 	Computer( int name );
	virtual ~Computer( void );
	Computer( Computer const & src );

	Computer &	operator=( Computer const & rhs );

	Possibility*						play(Board* currentBoard);

	void								getSons(bool bill);
	void								emptyAround(int x, int y, bool bill);
	void								createSon(int x, int y);
	void								createGrandSon(int x, int y);
	void								displaySons();
	void								lookAround(int x, int y, bool bill);
	void								setWeight(int x, int y);
	int 								spyAround(int x, int y);
	int 								spyOpponent(int x, int y, Pawn* currentPawn);
	// int 								inAlignementWay(Alignement* alignement, Pawn* currentPawn);
	bool 								spaceDisp(Alignement* alignement, int nbr);
	int 								observeAround(int x, int y);
	int 								observeOwn(int x, int y, Pawn* currentPawn);
	int 								getGrandSonsMin(Possibility* son);
	Possibility* 						getSonsMax();
	int									countAlignements(int x, int y);
	int 								riskCapture(Alignement* alignement);

private:
	Board* 						_currentBoard;
	Possibility*				_tmp;

public:
	std::vector<Possibility*> 	_sons;
	std::vector<Possibility*> 	_sonsDisplay;

};

#endif