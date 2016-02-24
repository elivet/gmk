#include "Board.hpp"
#include "Pawn.hpp"
#include "Alignement.hpp"

Board::Board( void ): _win(0), _gameEnded(false)
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

void		Board::determinePawnBegin(Alignement* alignement) // plutot linverse ? se retracte dune case 
{
	std::pair<int,int> currentKey = std::make_pair(alignement->getPawnBegin()->getX() + alignement->getNx(), alignement->getPawnBegin()->getY() + alignement->getNy()); // check si cest bien dans le bon sens maybe linverse
	alignement->setPawnBegin(findPawn(currentKey.first, currentKey.second));
	alignement->setNbr(alignement->getNbr()-1);
	if (alignement->getNbr() <= 1)
		deleteAlignement(alignement);
	return ;
}

void		Board::determinePawnEnd(Alignement* alignement)// plutot linverse ? se retracte dune case 
{
	std::pair<int,int> currentKey = std::make_pair(alignement->getPawnEnd()->getX() + alignement->getPx(), alignement->getPawnEnd()->getY() + alignement->getPy()); // check si cest bien dans le bon sens maybe linverse
	alignement->setPawnEnd(findPawn(currentKey.first, currentKey.second));
	alignement->setNbr(alignement->getNbr()-1);
	if (alignement->getNbr() <= 1)
		deleteAlignement(alignement);
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

void		Board::deleteAlignement(Alignement *align)
{
	if (!align || !align->getPawnBegin() || !align->getPawnEnd())
	{
		//std::cout << "PRBLM >>>>>>>>>>>>>>>>>>>>>>         Board::deleteAlignement 1 ALIGN NULL" << std::endl;
		return ;
	}

	Pawn *tmp = align->getPawnBegin();

	tmp->deleteAlignement(align);

	while (tmp && (tmp->getX() != align->getPawnEnd()->getX() || tmp->getY() != align->getPawnEnd()->getY()))
	{
		std::pair<int, int> currentKey = std::make_pair(tmp->getX()+ align->getNx(), tmp->getY() + align->getNy());
		tmp = findPawn(currentKey.first, currentKey.second);
		// if (!tmp)
		// 	std::cout << "PRBLM >>>>>>>>>>>>>>>>>>>>>>>>>            Board::deleteAlignement !tmp" << std::endl;
		tmp->deleteAlignement(align);
	}
	deleteAlignementFromBoard(align);
}

void		Board::erasePawnInsideAlignement(Alignement *align, Pawn* pawn)
{
	Pawn* tmp = align->getPawnBegin();
	std::pair<int, int> currentKey;
	int top = 0;

	while (tmp && tmp != pawn)
	{
		currentKey = std::make_pair(tmp->getX() + align->getNx(), tmp->getY() + align->getNy());
		tmp = findPawn(currentKey.first, currentKey.second);
		top++;
	}
	if ( tmp && top >= 2)
	{
		currentKey = std::make_pair(tmp->getX() + align->getPx(), tmp->getY() + align->getPy());
		tmp = findPawn(currentKey.first, currentKey.second);
		new Alignement(align->getPawnBegin(), tmp, this);
	}
	tmp = align->getPawnEnd();
	top = 0;
	while (tmp && tmp != pawn)
	{
		currentKey = std::make_pair(tmp->getX() + align->getPx(), tmp->getY() + align->getPy());
		tmp = findPawn(currentKey.first, currentKey.second);
		top++;
	}
	if ( tmp && top >= 2)
	{
		currentKey = std::make_pair(tmp->getX() + align->getNx(), tmp->getY() + align->getNy());
		tmp = findPawn(currentKey.first, currentKey.second);
		new Alignement(tmp, align->getPawnEnd(), this);
	}
	deleteAlignement(align);
	return ;
}


void		Board::erase(std::pair<int, int> xy)
{
	Pawn* pawn = findPawn(xy.first, xy.second);

	// if (!pawn)
	// 	std::cout << "PRBLM >>>>>>>>>>>>>>>>>>>>>>>>>>>>            Board::erase" << std::endl;

	unsigned int stop = pawn->_alignements.size();
	unsigned int j = 0;

	while ( j < stop)
	{
		if (pawn->_alignements[j]->getPawnBegin()->getX() == pawn->getX() && pawn->_alignements[j]->getPawnBegin()->getY() == pawn->getY())
		{
			determinePawnBegin(pawn->_alignements[j]);
			j++;
		}
		else if (pawn->_alignements[j]->getPawnEnd()->getX() == pawn->getX() && pawn->_alignements[j]->getPawnEnd()->getY() == pawn->getY())
		{
			determinePawnEnd(pawn->_alignements[j]);
			j++;
		}
		else
		{
			erasePawnInsideAlignement(pawn->_alignements[j], pawn);
			if (stop == pawn->_alignements.size())
				j++;
			stop =  pawn->_alignements.size();
		}
	}
	_pawns.erase(xy);
	return ;
}

void		Board::displayPawns( void )
{
	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
		if (it->second == NULL)
			std::cout << "PLAYER IS NULL DANS DISLPAY PAWNS" << std::endl;
		if (it->second->getPlayer()->getName() != 1 && it->second->getPlayer()->getName() != 2)
			std::cout << "PLAYER HAS NO NAME DANS DISLPAY PAWNS" << std::endl;
		else
			std::cout << "x: " << it->first.first << " y: " << it->first.second << " player: " << it->second->getPlayer()->getName() << std::endl;
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
	// std::cout << "Board::checkCapture 1" << std::endl;
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
	// std::cout << "Board::checkCapture 2" << std::endl;

	return tmp2;
}

bool		Board::isPawnInAlignement(Pawn *p, Alignement *al)
{
	Pawn *tmp = al->getPawnBegin();
	while (tmp != al->getPawnEnd())
	{
		if (tmp == p)
			return true;
		tmp = findPawn(tmp->getX() + al->getNx(), tmp->getY() + al->getNy());
	}
	return (tmp == p);
}

bool		Board::checkWinCaptureAroundPawn(Pawn *p, Alignement *al, int x, int y)
{
	// <=
	Pawn* neighbour = findPawn(p->getX() + x, p->getY() + y);

	if (neighbour != NULL && !isPawnInAlignement(neighbour, al))
	{
		if (neighbour->getPlayer()->getName() == p->getPlayer()->getName())
		{
			Pawn *second = findPawn(neighbour->getX() + x , neighbour->getY() + y);
			if (second != NULL && second->getPlayer()->getName() != p->getPlayer()->getName())
			{	
				int new_x = p->getX() - x;		
				int new_y = p->getY() - y;	
				Pawn *empty = findPawn(new_x, new_y);
				if (!empty && new_x >= 0 && new_x <= 18 && new_y >= 0 && new_y <= 18)
				{	
					//std::cout << "space is empty" << std::endl;
					return false;				
				}
			}
		}
		else if (neighbour->getPlayer()->getName() != p->getPlayer()->getName() && neighbour)
		{
			Pawn *second = findPawn(p->getX() - x , p->getY() - y);
			if (second != NULL && second->getPlayer()->getName() == p->getPlayer()->getName())
			{
				int new_x = second->getX() - x;		
				int new_y = second->getY() - y;
				Pawn *empty = findPawn(new_x, new_y);
				if (!empty && new_x >= 0 && new_x <= 18 && new_y >= 0 && new_y <= 18)
				{	
					//std::cout << "space is empty" << std::endl;
					return false;				
				}
			}
		}
	}
	return true;
}

bool		Board::checkWinCapturePawn(Pawn *p, Alignement *al)
{
	//left
	if (!checkWinCaptureAroundPawn(p, al, -1, 0))
		return false;
	//right
	if (!checkWinCaptureAroundPawn(p, al, 1, 0))
		return false;
	//bottom left
	if (!checkWinCaptureAroundPawn(p, al, -1, -1))
		return false;
	//top right
	if (!checkWinCaptureAroundPawn(p, al, 1, 1))
		return false;
	//top left
	if (!checkWinCaptureAroundPawn(p, al, -1, 1))
		return false;
	//bottom right
	if (!checkWinCaptureAroundPawn(p, al, 1, -1))
		return false;
	//top
	if (!checkWinCaptureAroundPawn(p, al, 0, 1))
		return false;
	//bottom
	if (!checkWinCaptureAroundPawn(p, al, 0, -1))
		return false;

	return true;
}

bool		Board::checkWinCapture(Alignement *al)
{
	Pawn *tmp = al->getPawnBegin();
	int i = 0;
	while (tmp != al->getPawnEnd())
	{
		//std::cout << "Pawn" << i << ": " << tmp->getX() << " - " << tmp->getY() << std::endl;
		if (!checkWinCapturePawn(tmp, al))
			return false;
		tmp = findPawn(tmp->getX() + al->getNx(), tmp->getY() + al->getNy());
		// if (!tmp)
		// 	std::cout << "PRBLM >>>>>>>>>>>>>>>>>>>>>>>                                 Board::checkWinCapture !tmp" << std::endl;
		i++;
	}
	std::cout << "Pawn" << i << ": " << tmp->getX() << " - " << tmp->getY() << std::endl;
	//cehcking last Pawn because its eclude from the loop with the condition of tmp != al->getPawnEnd()
	return checkWinCapturePawn(tmp, al);
	//return true;
}

bool 		Board::checkwin(Player* player1, Player* player2)
{
	for (unsigned int i = 0; i < _alignements.size(); i++)
	{
		if (_alignements[i]->getNbr() >= 5)
		{
			if (checkWinCapture(_alignements[i]))
			{
				std::cout << "WINNNERNNENRNNENRNRNENRNNRENRNRNRNRN" << std::endl;
				_win = _alignements[i]->getPawnBegin()->getPlayer()->getName();

				//******************************//
				//Color Winning alignement
				Pawn *tmp = _alignements[i]->getPawnBegin();
				while (tmp != _alignements[i]->getPawnEnd())
				{
					tmp->setIsWinnerAlignement();
					tmp = findPawn(tmp->getX() + _alignements[i]->getNx(), tmp->getY() + _alignements[i]->getNy());
				}
				tmp->setIsWinnerAlignement();
				//******************************//
				return true;
			}
		}
		// checkCapture
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

void		Board::setGameEnded()
{
	this->_gameEnded = true;
}

void		Board::createAlignement(Pawn* neighbour, std::pair<int,int> key)
{
	Pawn* current = findPawn(key.first, key.second);
	Alignement* 	newAlignement = new Alignement(neighbour, current, this);
	newAlignement->checkJoinAlignements(findPawn(key.first, key.second), this);
	// current->_alignements.push_back(newAlignement);
	// neighbour->_alignements.push_back(newAlignement);
	// _alignements.push_back(newAlignement);
	return ;
}

void		Board::deleteAlignementFromBoard(Alignement* align)
{
	for (unsigned int i = 0; i < _alignements.size(); i++)
	{
		if (_alignements[i] == align)
			_alignements.erase(_alignements.begin() + i);
	}
	return ;
}

void		Board::findAlignement(Pawn* neighbour, std::pair<int,int> key)
{
	int top = 0;	

	for (unsigned int i = 0; i < neighbour->getAlignements().size(); i++) // on parcourt les alignement du neighbour
	{
		top += neighbour->_alignements[i]->isAligned(key, this); // on le rajoute a un alignement deja existant dans isaligned
	}
	if (top == 0)
	{
		createAlignement(neighbour, key);
	}
	return ;
}

void		Board::checkNeighbour(std::pair<int,int> key1, std::pair<int,int> key2)
{
	Pawn	*tmpPawn;

	if ((tmpPawn = findPawn(key1.first, key1.second)) != NULL && _pawns[key2] != NULL)
	{
		if (tmpPawn->getPlayer()->getName() == _pawns[key2]->getPlayer()->getName())
			findAlignement(tmpPawn, key2);
	}
	return ;
}

bool		Board::isPairInsideBoard(int x, int y)
{
	return (x >= 0 && x <= 18 && y >= 0 && y <= 18);
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

	for(std::map<std::pair<int,int>, Pawn*>::iterator it=_pawns.begin() ; it!=_pawns.end() ; ++it)
	{
		int x = it->first.first;
		int y = it->first.second;

		if (!_gameEnded)
			_renderLib->drawCircle(x, y, 1, it->second->getPlayer()->getColor());
		else
		{
			
			if (_win == it->second->getPlayer()->getName())
			{
				if (it->second->getIsInWinnerAlignement())
					_renderLib->drawCircle(x, y, 1, 0xFF0000);
				else
					_renderLib->drawCircle(x, y, 1, 0x900000);
			}
			else
				_renderLib->drawCircle(x+0.1, y+0.1, 0.8, it->second->getPlayer()->getColor());

		}
	}

	if (_assist.first != -1 && _assist.second != -1)
	{
		_renderLib->drawCircle(_assist.first, _assist.second, 1, 0xFFD000);

	}
	return (true);
}





















