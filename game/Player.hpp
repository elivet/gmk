#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Board.hpp"
// # include "Alignement.hpp"
# include "Pawn.hpp" 
class Pawn;
class Alignement;
class Computer;
class Player
{
public:
	Player( void );
	Player( int name, int color );
 	virtual ~Player( void );
	Player( Player const & src );

	Player &	operator=( Player const & rhs );

	std::pair<int, int>			play(Board* currentBoard, std::pair<int, int> xy);
	bool						referee(Board* currentBoard, std::pair<int, int> xy);
	bool						isDoubleThree(Board* currentBoard, std::pair<int, int> key);
	bool						isDoubleThreeForVector(Board* board, std::pair<int, int> key, std::pair<int, int> v);

	int			getName() const;
	int			getColor() const;

	void		setOpponent(Player* opponent);

protected:
	int										_name;
	int										_color;
	Player*									_opponent;
public:
	std::vector<Alignement*>				_alignements;
	int										_capturedPawns;
	Computer*								_assistant;

};

#endif