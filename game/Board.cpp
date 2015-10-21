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

void		Board::erase(std::pair<int, int> xy)
{
	std::cout << "erasePawn x: " << xy.first << " y: " << xy.second << std::endl;
	_pawns.erase(xy);
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

std::vector<std::pair<int, int> > 	Board::checkTrap(std::pair<int, int> key, std::pair<int, int> key2)
{
	int nx = key2.first - key.first;
	int ny = key2.second - key.second;
	int player = findPawn(key.first, key.second)->getPlayer();
	int opponent = findPawn(key2.first, key2.second)->getPlayer();
	std::vector<std::pair<int, int> > capturedPawns;

	std::pair<int, int> currentKey = std::make_pair(key2.first + nx, key2.second + ny);
	if (findPawn(currentKey.first, currentKey.second) && findPawn(currentKey.first, currentKey.second)->getPlayer() == opponent)
	{
		currentKey = std::make_pair(currentKey.first + nx, currentKey.second + ny);
		if (findPawn(currentKey.first, currentKey.second) && findPawn(currentKey.first, currentKey.second)->getPlayer() == player)
		{
			capturedPawns.push_back(key2);
			capturedPawns.push_back(currentKey);
		}
	}
	return capturedPawns;
}

int 		Board::checkFriend(int x, int y, std::pair<int, int> key)
{
	std::pair<int, int> key2 = std::make_pair(x, y);

	if (findPawn(x, y))
		return (checkAlignement(key, key2));
	return 0;
}

std::vector<std::pair<int, int> >	Board::checkOpponent(int x, int y, std::pair<int, int> key)
{
	std::vector<std::pair<int, int> > capturedPawns;
	std::pair<int, int> key2 = std::make_pair(x, y);
	Pawn	*tmpPawn;

	if ((tmpPawn = findPawn(x, y)) != NULL)
	{
		if (tmpPawn->getPlayer() != _pawns[key]->getPlayer())
			return (checkTrap(key, key2));
	}
	return capturedPawns;
}

void		Board::checkAround(std::map<std::pair<int,int>, Pawn*>::iterator it)
{
	std::pair<int, int> key = std::make_pair(it->first.first, it->first.second);

	if (checkFriend(it->first.first - 1, it->first.second, key) == 0)
		checkFriend(it->first.first + 1, it->first.second, key);

	if (checkFriend(it->first.first - 1, it->first.second - 1, key) == 0)
		checkFriend(it->first.first + 1, it->first.second + 1, key);

	if (checkFriend(it->first.first - 1, it->first.second + 1, key) == 0)
		checkFriend(it->first.first + 1, it->first.second - 1, key);

	if (checkFriend(it->first.first, it->first.second + 1, key) == 0)
		checkFriend(it->first.first, it->first.second - 1, key);
	return ;
}

std::vector<std::pair<int, int> >		Board::checkCapture(int x, int y)
{
	std::vector<std::pair<int, int> >	tmp;
	std::vector<std::pair<int, int> >	tmp2;
	std::pair<int, int> key = std::make_pair(x, y);

	tmp = checkOpponent(x - 1, y, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x + 1, y, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x - 1, y - 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x + 1, y + 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x - 1, y + 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x + 1, y - 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x, y + 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
	tmp = checkOpponent(x, y - 1, key);
	if (tmp.size() > 0)
		tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());

	return tmp2;
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

int 			Board::getWin()
{
	return _win;
}

int					Board::render( OpenGlLib *	_renderLib )
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
		int x = it->first.first;
		int y = it->first.second;

		if (it->second->getPlayer())
			_renderLib->drawCircle(x, y, 1, 0xFFFFFF);
		else
			_renderLib->drawCircle(x, y, 1, 0x000000);
	}
	return (true);
}





















