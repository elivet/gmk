#include "Board.hpp"

Board::Board( void ): _win(0)
{
	return ;
}

Board::~Board( void )
{
	return ;
}

Board::Board( Board const & src )
{
	std::cout << "  +++++++++    NEW SON" << std::endl;
	*this = src;
}

Board &	Board::operator=( Board const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
} 

void		Board::insert(std::pair<int, int> xy, int player)
{
	std::cout << "insertPawn x: " << xy.first << " y: " << xy.second << std::endl;
	Pawn	*pawn = new Pawn(player);
	_pawns[xy] = pawn;
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

int 		Board::checkAlignement(std::pair<int, int> key, std::pair<int, int> key2)
{
	int count = 2;
	int px = key.first - key2.first;
	int py = key.second - key2.second;
	int nx = key2.first - key.first;
	int ny = key2.second - key.second;
	int player = findPawn(key.first, key.second)->getPlayer();

	std::pair<int, int> currentKey = std::make_pair(key2.first + nx, key2.second + ny);
	while (findPawn(currentKey.first, currentKey.second) && findPawn(currentKey.first, currentKey.second)->getPlayer() == player)
	{
		currentKey = std::make_pair(currentKey.first + nx, currentKey.second + ny);
		count++;
	}
	currentKey = std::make_pair(key.first + px, key.second + py);
	while (findPawn(currentKey.first, currentKey.second) && findPawn(currentKey.first, currentKey.second)->getPlayer() == player)
	{
		currentKey = std::make_pair(currentKey.first + px, currentKey.second + py);
		count++;
	}
	if (count >= 5)
		_win = findPawn(key.first, key.second)->getPlayer();
	return count;
}

int 		Board::checker(int x, int y, std::pair<int, int> key)
{
	std::pair<int, int> key2 = std::make_pair(x, y);

	if (findPawn(x, y))
		return (checkAlignement(key, key2));
	return 0;
}

void		Board::checkAround(std::map<std::pair<int,int>, Pawn*>::iterator it)
{
	std::pair<int, int> key = std::make_pair(it->first.first, it->first.second);

	if (checker(it->first.first - 1, it->first.second, key) == 0)
		checker(it->first.first + 1, it->first.second, key);

	if (checker(it->first.first - 1, it->first.second - 1, key) == 0)
		checker(it->first.first + 1, it->first.second + 1, key);

	if (checker(it->first.first - 1, it->first.second + 1, key) == 0)
		checker(it->first.first + 1, it->first.second - 1, key);

	if (checker(it->first.first, it->first.second + 1, key) == 0)
		checker(it->first.first, it->first.second - 1, key);
	return ;
}

bool 		Board::checkwin()
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
		checkAround(it);
		if (_win > 0)
		{
			std::cout << "IM A WINNER" << std::endl;
			return true;
		}
	}
	return false;
}

std::map<std::pair<int,int>, Pawn*>		Board::getPawns()
{
	return _pawns;
}


















