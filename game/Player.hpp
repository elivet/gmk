#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Board.hpp"
// # include "Alignement.hpp"
# include "Pawn.hpp" 
class Pawn;
class Alignement;
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

	int			getName() const;
	int			getColor() const;


protected:
	int										_name;
	int										_capturedPawns;
	int										_color;
public:
	std::vector<Alignement*>				_alignements;

};

#endif