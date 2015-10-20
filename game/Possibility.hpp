#ifndef POSSIBILITY_HPP
# define POSSIBILITY_HPP

# include "Board.hpp"
# include <iostream>
# include <vector>
# include <map>

class Possibility
{
public:
	Possibility( void );
	Possibility( int x, int y, int player );
 	~Possibility( void );
	Possibility( Possibility const & src );

	Possibility &	operator=( Possibility const & rhs );

	void		insert(int x, int y, int player);

	int											getX( void );
	int											getY( void );
	std::map<std::pair<int,int>,Possibility*>	getGrandSons( void );
	void										setWeight(Board* currentBoard);

private:
	int							_player;
	// int							_weight;
	int							_x;
	int							_y;
	Board*						_currentBoard;
public:
	std::map<std::pair<int,int>,Possibility*> 	_grandSons;

};

#endif