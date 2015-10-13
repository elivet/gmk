#include "Board.hpp"

Board::Board( void )
{
	return ;
}

Board::~Board( void )
{
	return ;
}

Board::Board( Board const & src )
{
	*this = src;
}

Board &	Board::operator=( Board const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
} 

void		Board::insert(int x, int y, int player)
{
	Pawn	*pawn = new Pawn(player);
	std::pair<int, int> key = std::make_pair(x, y);
	_pawns[key] = pawn;
	return ;
}

void		Board::displayPawns( void )
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
		std::cout << "x: " << it->first.first << " y: " << it->first.second << " player: " << it->second->getPlayer() << std::endl;
	}

}

Pawn*		Board::findPawn( int x, int y)
{
	std::pair<int, int> key = std::make_pair(x, y);
	std::map<std::pair<int,int>, Pawn*>::iterator it = _pawns.find( key );
	if ( it != _pawns.end() )
	{
		return ( it->second );
	}
	return ( NULL );
}