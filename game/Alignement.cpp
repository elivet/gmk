#include "Alignement.hpp"
// #include "Pawn.hpp"
Alignement::Alignement( void )
{
	return ;
}

Alignement::Alignement( Pawn* p1, Pawn* p2, Board* currentBoard )
{
	this->_pawnBegin = p1;
	this->_pawnEnd = p2;
	this->_nbr = 2; // a changer ; peut etre 3 a la creation

	this->_px = p1->getX() - p2->getX();
	this->_py = p1->getY() - p2->getY();
	this->_nx = p2->getX() - p1->getX();
	this->_ny = p2->getY() - p1->getY();
	(void)currentBoard;
	return ;
}

Alignement::~Alignement( void )
{
	return ;
}

Alignement::Alignement( Alignement const & src )
{
	*this = src;
}

Alignement &	Alignement::operator=( Alignement const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

bool Alignement::operator==(Alignement &rhs)
{
	return (
			(
				(this->_pawnBegin == rhs.getPawnBegin() && this->_pawnEnd == rhs.getPawnEnd()) ||
				(this->_pawnBegin == rhs.getPawnEnd() && this->_pawnEnd == rhs.getPawnBegin())
			)
			&&
			(
				(
					(this->_nx == rhs.getNx() && this->_ny == rhs.getNy()) &&
					(this->_px == rhs.getPx() && this->_py == rhs.getPy())  
				)
				||
				(
					(this->_nx == rhs.getNy() && this->_ny == rhs.getNx()) &&
					(this->_px == rhs.getPy() && this->_py == rhs.getPx()) 
				)
			)
			&&
				this->_nbr == rhs.getNbr()
		);
}

void		Alignement::deleteAlignement(Alignement *align, Board* currentBoard) // replace + que deleta
{
	std::cout << "Alignement::deleteAlignement 1" << std::endl;

	Pawn *tmp = align->_pawnBegin;

	tmp->deleteAlignement(align);
	tmp->_alignements.push_back(this);

	while (tmp->getX() != align->_pawnEnd->getX() || tmp->getY() != align->_pawnEnd->getY())
	{
		std::pair<int, int> currentKey = std::make_pair(tmp->getX()+ align->getNx(), tmp->getY() + align->getNy());
		tmp = currentBoard->findPawn(currentKey.first, currentKey.second);
		tmp->deleteAlignement(align);
		tmp->_alignements.push_back(this);
	}
	std::cout << "Alignement::deleteAlignement 2" << std::endl;

	//delete du player
}

void 		Alignement::joinAlignements(Alignement *align, Pawn *current, Board* currentBoard)
{
	std::cout << "Alignement::joinAlignements 1" << std::endl;

	if (this->_pawnBegin == current)
	{
		if (align->getPawnBegin() == current)
		{
			this->_pawnBegin = align->getPawnEnd();
		}
		else if (align->getPawnEnd() == current)
		{
			this->_pawnBegin = align->getPawnBegin();
		}
	}
	else if (this->_pawnEnd == current)
	{
		if (align->getPawnBegin() == current)
		{
			this->_pawnEnd = align->getPawnEnd();
		}
		else if (align->getPawnEnd() == current)
		{
			this->_pawnEnd = align->getPawnBegin();
		}
	}
	this->_nbr += align->getNbr() - 1; // met pas -2 cest pas normal
	deleteAlignement(align, currentBoard);
	std::cout << "Alignement::joinAlignements 2" << std::endl;
}

void		Alignement::checkJoinAlignements(Pawn *current, Board* currentBoard) // ! peut etre n et p inverses
{
	std::cout << "Alignement::checkJoinAlignements 1" << std::endl;
	for (unsigned int i = 0; i < current->getAlignements().size(); i++)
	{
		if (this->_nx == current->getAlignements()[i]->getNx() &&
			this->_ny == current->getAlignements()[i]->getNy() &&
			this->_py == current->getAlignements()[i]->getPy() &&
			this->_px == current->getAlignements()[i]->getPx()) // si le pion a deja un alignement sur le meme vecteur, joindre les alignements
		{
			joinAlignements(current->getAlignements()[i], current, currentBoard);
			return ;
		}
		if (this->_nx == current->getAlignements()[i]->getPx() &&
			this->_ny == current->getAlignements()[i]->getPy() &&
			this->_py == current->getAlignements()[i]->getNy() &&
			this->_px == current->getAlignements()[i]->getNx()) // si le pion a deja un alignement sur le meme vecteur, joindre les alignements
		{
			joinAlignements(current->getAlignements()[i], current, currentBoard);
			return ;
		}
	}
	std::cout << "Alignement::checkJoinAlignements 2" << std::endl;
	return ;
}

int			Alignement::isAligned(std::pair<int, int> key, Board* currentBoard) // prblm ici en joignant un alignement a un pion solo
{
	std::cout << "Alignement::isAligned 1" << std::endl;
	std::pair<int,int> currentKey = std::make_pair(_pawnBegin->getX() + this->_px, _pawnBegin->getY() + this->_py); // check si cest bien dans le bon sens maybe linverse
	std::pair<int,int> currentKey2 = std::make_pair(_pawnEnd->getX() + this->_nx, _pawnEnd->getY() + this->_ny); // check si cest bien dans le bon sens maybe linverse
	
	if (currentKey.first == key.first && currentKey.second == key.second)  
	{
		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);

		this->_pawnBegin = newPawn;
		this->_nbr++;
		checkJoinAlignements(newPawn, currentBoard);
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
		return 1;
	}
	if (currentKey2.first == key.first && currentKey2.second == key.second)
	{
		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);
		this->_pawnEnd = newPawn;
		this->_nbr++;
		checkJoinAlignements(newPawn, currentBoard);
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
		return 1;
	}
	std::cout << "Alignement::isAligned 2" << std::endl;
	return 0;
}

int			Alignement::getNbr()
{
	return this->_nbr;
}

int			Alignement::getNx()
{
	return this->_nx;
}

int			Alignement::getPx()
{
	return this->_px;
}

int			Alignement::getNy()
{
	return this->_ny;
}

int			Alignement::getPy()
{
	return this->_py;
}

Pawn*		Alignement::getPawnBegin()
{
	return this->_pawnBegin;
}

Pawn*		Alignement::getPawnEnd()
{
	return this->_pawnEnd;
}

void		Alignement::setPawnBegin(Pawn* pawn)
{
	_pawnBegin = pawn;
	return ;
}

void		Alignement::setPawnEnd(Pawn* pawn)
{
	_pawnEnd = pawn;
	return ;
}

void		Alignement::setNbr(int nbr)
{
	_nbr = nbr;
	return ;
}

void		Alignement::toString()
{
	std::cout << "alignement BEGIN = x:"
		<< this->_pawnBegin->getX() << "/y:"
		<< this->_pawnBegin->getY() << " END = x:"
		<< this->_pawnEnd->getX() << "/y:"
		<< this->_pawnEnd->getY()
		<< std::endl;
}










