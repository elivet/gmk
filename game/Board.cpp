#include "Board.hpp"
#include "Pawn.hpp"
#include "Alignement.hpp"

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

void		Board::insert(std::pair<int, int> xy, Player* player)
{
	// std::cout << "XXXXXXXXXXXXXX                                             insertPawn x: " << xy.first << " y: " << xy.second << std::endl;
	if (player->getName() == 0)
		std::cout << " player DOESNT EXIST SHIT SHIT SHIT SHIT SHIT SHIT " <<  std::endl;
	Pawn	*pawn = new Pawn(player, xy.first, xy.second);
	_pawns[xy] = pawn;
	return ;
}

void		Board::determinePawnBegin(Alignement* alignement)
{
	std::pair<int,int> currentKey = std::make_pair(alignement->getPawnBegin()->getX() + alignement->getNx(), alignement->getPawnBegin()->getY() + alignement->getNy()); // check si cest bien dans le bon sens maybe linverse
	alignement->setPawnBegin(findPawn(currentKey.first, currentKey.second));
	alignement->setNbr(alignement->getNbr()-1);
	return ;
}

void		Board::determinePawnEnd(Alignement* alignement)
{
	std::pair<int,int> currentKey = std::make_pair(alignement->getPawnEnd()->getX() + alignement->getPx(), alignement->getPawnEnd()->getY() + alignement->getPy()); // check si cest bien dans le bon sens maybe linverse
	alignement->setPawnEnd(findPawn(currentKey.first, currentKey.second));
	alignement->setNbr(alignement->getNbr()-1);
	return ;
}

void 		Board::eraseAlignementFromPawnsBegin(Alignement* al1, Alignement* al2)
{
	if (al1->getPawnBegin() == NULL || al2->getPawnBegin() == NULL || al2->getPawnEnd() == NULL || al1->getPawnEnd() == NULL)
		return ;
	std::pair<int, int> currentKey = std::make_pair(al2->getPawnBegin()->getX() + al2->getNx(), al2->getPawnBegin()->getY() + al2->getNy());
	Pawn* pawn = findPawn(currentKey.first, currentKey.second);
	if (pawn == NULL)
		return ;
	while (pawn->getX() != al2->getPawnEnd()->getX() || pawn->getY() != al2->getPawnEnd()->getY())
	{
		pawn->replaceAlignement(al1, al2);
		currentKey = std::make_pair(currentKey.first + al2->getNx(), currentKey.second + al2->getNy());
		pawn = findPawn(currentKey.first, currentKey.second);
	}
	pawn->_alignements.push_back(al2);
	return ;
}


void		Board::erase(std::pair<int, int> xy)
{
	// std::cout << "Board::erase1" << std::endl;
	Pawn* pawn = findPawn(xy.first, xy.second);
	if (!pawn)
		return;
	// std::cout << "Board::erase2" << std::endl;
	for (unsigned int j = 0; j < pawn->_alignements.size(); j++)
	{
	// std::cout << "Board::erase3" << std::endl;
		if (pawn->_alignements[j]->getPawnBegin()->getX() == pawn->getX() && pawn->_alignements[j]->getPawnBegin()->getY() == pawn->getY())
		{
	// std::cout << "Board::erase4" << std::endl;
			determinePawnBegin(pawn->_alignements[j]);
		}
		else if (pawn->_alignements[j]->getPawnEnd()->getX() == pawn->getX() && pawn->_alignements[j]->getPawnEnd()->getY() == pawn->getY())
		{
	// std::cout << "Board::erase5" << std::endl;
			determinePawnEnd(pawn->_alignements[j]);
		}
		else
		{
	// std::cout << "Board::erase6.1" << std::endl;
			Alignement* clone = new Alignement(*_alignements[j]);			
	// std::cout << "Board::erase6.2" << std::endl;
			_alignements[j]->setPawnBegin(pawn);
	// std::cout << "Board::erase6.3" << std::endl;
			clone->setPawnEnd(pawn);
	// std::cout << "Board::erase6.4" << std::endl;
			eraseAlignementFromPawnsBegin(pawn->_alignements[j], clone);
	// std::cout << "Board::erase6.5" << std::endl;
			determinePawnBegin(pawn->_alignements[j]);
	// std::cout << "Board::erase6.6" << std::endl;
			determinePawnEnd(clone);
	// std::cout << "Board::erase6.7" << std::endl;
			pawn->getPlayer()->_alignements.push_back(clone);
	// std::cout << "Board::erase7" << std::endl;
		}
	}
	// std::cout << "Board::erase8" << std::endl;
	_pawns.erase(xy);
	// std::cout << "Board::erase9" << std::endl;
	return ;
}

void		Board::displayPawns( void )
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
	std::cout << "displayPawns loop begin" << std::endl;
		if (it->second == NULL)
			std::cout << "PLAYER IS NULL DANS DISLPAY PAWNS" << std::endl;
		if (it->second->getPlayer()->getName() != 1 && it->second->getPlayer()->getName() != 2)
			std::cout << "PLAYER HAS NO NAME DANS DISLPAY PAWNS" << std::endl;
		else
			std::cout << "x: " << it->first.first << " y: " << it->first.second << " player: " << it->second->getPlayer()->getName() << std::endl;
	std::cout << "displayPawns loop end" << std::endl;
	}
	std::cout << "displayPawns end" << std::endl;

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

std::vector<std::pair<int, int> > 	Board::checkTrap(std::pair<int, int> key, std::pair<int, int> key2)
{
	int nx = key2.first - key.first;
	int ny = key2.second - key.second;
	int player = findPawn(key.first, key.second)->getPlayer()->getName();
	int opponent = findPawn(key2.first, key2.second)->getPlayer()->getName();
	std::vector<std::pair<int, int> > capturedPawns;

	std::pair<int, int> currentKey = std::make_pair(key2.first + nx, key2.second + ny);
	if (findPawn(currentKey.first, currentKey.second) && findPawn(currentKey.first, currentKey.second)->getPlayer()->getName() == opponent)
	{
		std::pair<int, int> currentKey2 = std::make_pair(currentKey.first + nx, currentKey.second + ny);
		if (findPawn(currentKey2.first, currentKey2.second) && findPawn(currentKey2.first, currentKey2.second)->getPlayer()->getName() == player)
		{
			capturedPawns.push_back(key2);
			capturedPawns.push_back(currentKey);
		}
	}
	return capturedPawns;
}



std::vector<std::pair<int, int> >	Board::checkOpponent(int x, int y, std::pair<int, int> key)
{
	std::vector<std::pair<int, int> > capturedPawns;
	std::pair<int, int> key2 = std::make_pair(x, y);
	Pawn	*tmpPawn;

	if ((tmpPawn = findPawn(x, y)) != NULL)
	{
		if (tmpPawn->getPlayer()->getName() != _pawns[key]->getPlayer()->getName())
			return (checkTrap(key, key2));
	}
	return capturedPawns;
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

bool 		Board::checkwin(Player* player1, Player* player2)
{
	for (unsigned int i = 0; i < _alignements.size(); i++)
	{
		if (_alignements[i]->getNbr() >= 5)
		{
			std::cout << "WINNNERNNENRNNENRNRNENRNNRENRNRNRNRN" << std::endl;
			_win = _alignements[i]->getPawnBegin()->getPlayer()->getName();
			return true;
		}
	}
	if (player1->_capturedPawns >= 10)
	{
		_win = player1->getName();
		std::cout << "Player: " << _win << " win !" << std::endl;
		return true;
	}
	if (player2->_capturedPawns >= 10)
	{
		_win = player2->getName();
		std::cout << "Player: " << _win << " win !" << std::endl;
		return true;
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

void		Board::createAlignement(Pawn* neighbour, std::pair<int,int> key)
{
	Pawn* current = findPawn(key.first, key.second);
	Alignement* 	newAlignement = new Alignement(neighbour, current, this);
	neighbour->_alignements.push_back(newAlignement);
	current->_alignements.push_back(newAlignement);
	_alignements.push_back(newAlignement);
	return ;
}

void		Board::findAlignement(Pawn* neighbour, std::pair<int,int> key)
{
	std::cout << "##checking alignement ..." << std::endl;

	//TODO : j'ai pas tout compris la. A faire check le retour de getAlignements
	std::cout<< "NB alignements: " << neighbour->getAlignements().size() << std::endl;

	int top = 0;
	
	for (unsigned int i = 0; i < neighbour->getAlignements().size(); i++) // on parcourt les alignement du neighbour
	{
		top += neighbour->_alignements[i]->isAligned(key, this); // on le rajoute a un alignement deja existant dans isaligned
	}
	if (top == 0) // ne cree un alignement que si yen a pas??! hein ?
	{
		std::cout<< "creating an alignement while top is equal to:" << top << std::endl;
		createAlignement(neighbour, key); // a modifier car creation de deux alignements si *.*
	}
	return ;
}

void		Board::checkNeighbour(std::pair<int,int> key1, std::pair<int,int> key2)
{
	Pawn	*tmpPawn;

	if ((tmpPawn = findPawn(key1.first, key1.second)) != NULL && _pawns[key2] != NULL)
	{
		std::cout << "Board::checkNeighbour PL1: " << tmpPawn->getPlayer()->getName() << " PL2: " << _pawns[key2]->getPlayer()->getName() << std::endl;
		if (tmpPawn->getPlayer()->getName() == _pawns[key2]->getPlayer()->getName())
			findAlignement(tmpPawn, key2);
	}
	return ;
}

void		Board::stockAlignement(std::pair<int,int> xy)
{
	checkNeighbour(std::make_pair(xy.first - 1, xy.second), xy); //left
	checkNeighbour(std::make_pair(xy.first + 1, xy.second), xy); //right
	checkNeighbour(std::make_pair(xy.first - 1, xy.second - 1), xy); //bottom left
	checkNeighbour(std::make_pair(xy.first + 1, xy.second + 1), xy); //top right
	checkNeighbour(std::make_pair(xy.first - 1, xy.second + 1), xy); //top left
	checkNeighbour(std::make_pair(xy.first + 1, xy.second - 1), xy); //bottom right
	checkNeighbour(std::make_pair(xy.first, xy.second + 1), xy); //top
	checkNeighbour(std::make_pair(xy.first, xy.second - 1), xy); //bottom
	return ;
}

int					Board::render( OpenGlLib *	_renderLib )
{
	// std::cout << "Board::render1" << std::endl;
	for (int i = 1; i < 20; i++)
		_renderLib->drawLine(i, 1, i, 19, COLOR_BLACK);
	for (int i = 1; i < 20; i++)
		_renderLib->drawLine(1, i, 19, i, COLOR_BLACK);
	_renderLib->drawSquare(3.9, 3.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(9.9, 3.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(15.9, 3.9, 0.2, COLOR_BLACK);

	_renderLib->drawSquare(3.9, 9.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(9.9, 9.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(15.9, 9.9, 0.2, COLOR_BLACK);

	_renderLib->drawSquare(3.9, 15.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(9.9, 15.9, 0.2, COLOR_BLACK);
	_renderLib->drawSquare(15.9, 15.9, 0.2, COLOR_BLACK);
	// std::cout << "Board::render2 size: " << _pawns.size() << std::endl;

	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
	// std::cout << "Board::render3 X: " << it->first.first << " Y: " << it->first.second << std::endl;
	// std::cout << " name: " << it->second->getPlayer()->getName() << std::endl;
		int x = it->first.first;
		int y = it->first.second;

		_renderLib->drawCircle(x, y, 1, it->second->getPlayer()->getColor());
	}
	// std::cout << "Board::render4" << std::endl;
	return (true);
}





















