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

	std::cout << "NEW ALIGNEMENT: _pawnBegin" << std::endl;
	_pawnBegin->toString();
	std::cout << "NEW ALIGNEMENT: _pawnEnd" << std::endl;
	_pawnEnd->toString();


	this->_px = p1->getX() - p2->getX();
	this->_py = p1->getY() - p2->getY();
	this->_nx = p2->getX() - p1->getX();
	this->_ny = p2->getY() - p1->getY();
	currentBoard->_alignements.push_back(this);
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
	currentBoard->deleteAlignementFromBoard(align);
}

void 		Alignement::joinAlignements(Alignement *align, Pawn *current, Board* currentBoard)
{
	std::cout << "Alignement::joinAlignements IN" << std::endl;
	std::cout << "Alignement::joinAlignements 1 _pawnBegin->toString()" << std::endl;
	_pawnBegin->toString();
	std::cout << "Alignement::joinAlignements 1 _pawnEnd->toString()" << std::endl;
	_pawnEnd->toString();
	std::cout << "Alignement::joinAlignements 1 nbr: " << _nbr << std::endl;

	std::cout << "Alignement::joinAlignements 1 align->getPawnBegin()->toString()" << std::endl;
	align->getPawnBegin()->toString();
	std::cout << "Alignement::joinAlignements 1 align->getPawnEnd()->toString()" << std::endl;
	align->getPawnEnd()->toString();
	std::cout << "Alignement::joinAlignements 1 nbr: " << align->getNbr() << std::endl;




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

	std::cout << "Alignement::joinAlignements 1 _pawnBegin->toString()" << std::endl;
	_pawnBegin->toString();
	std::cout << "Alignement::joinAlignements 1 _pawnEnd->toString()" << std::endl;
	_pawnEnd->toString();
	std::cout << "Alignement::joinAlignements 1 nbr: " << _nbr << std::endl;

	deleteAlignement(align, currentBoard);
}

void		Alignement::checkJoinAlignements(Pawn *current, Board* currentBoard) // ! peut etre n et p inverses
{
	for (unsigned int i = 0; i < current->getAlignements().size(); i++)
	{
		if (this->_nx == current->getAlignements()[i]->getNx() &&
			this->_ny == current->getAlignements()[i]->getNy() &&
			this->_py == current->getAlignements()[i]->getPy() &&
			this->_px == current->getAlignements()[i]->getPx() &&
			(this->_pawnBegin != current->getAlignements()[i]->getPawnEnd() || this->_pawnEnd != current->getAlignements()[i]->getPawnBegin()) &&
			(this->_pawnBegin != current->getAlignements()[i]->getPawnBegin() || this->_pawnEnd != current->getAlignements()[i]->getPawnEnd())) // si le pion a deja un alignement sur le meme vecteur, joindre les alignements
		{
			joinAlignements(current->getAlignements()[i], current, currentBoard);
			return ;
		}
		if (this->_nx == current->getAlignements()[i]->getPx() &&
			this->_ny == current->getAlignements()[i]->getPy() &&
			this->_py == current->getAlignements()[i]->getNy() &&
			this->_px == current->getAlignements()[i]->getNx()  &&
			(this->_pawnBegin != current->getAlignements()[i]->getPawnEnd() || this->_pawnEnd != current->getAlignements()[i]->getPawnBegin()) &&
			(this->_pawnBegin != current->getAlignements()[i]->getPawnBegin() || this->_pawnEnd != current->getAlignements()[i]->getPawnEnd())) // si le pion a deja un alignement sur le meme vecteur, joindre les alignements
		{
			joinAlignements(current->getAlignements()[i], current, currentBoard);
			return ;
		}
	}
	return ;
}

int			Alignement::isAligned(std::pair<int, int> key, Board* currentBoard) // prblm ici en joignant un alignement a un pion solo
{
	// std::cout << "Alignement::isAligned 1 _pawnBegin->toString()" << std::endl;
	// _pawnBegin->toString();
	// std::cout << "Alignement::isAligned 1 _pawnEnd->toString()" << std::endl;
	// _pawnEnd->toString();

	// std::cout << "Alignement::isAligned 1" << std::endl;

	std::pair<int,int> currentKey = std::make_pair(_pawnBegin->getX() + this->_px, _pawnBegin->getY() + this->_py); // check si cest bien dans le bon sens maybe linverse
	std::pair<int,int> currentKey2 = std::make_pair(_pawnEnd->getX() + this->_nx, _pawnEnd->getY() + this->_ny); // check si cest bien dans le bon sens maybe linverse
	
	// std::cout << "Alignement::isAligned 2" << std::endl;
	if (currentKey.first == key.first && currentKey.second == key.second)  
	{


		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);

		this->_pawnBegin = newPawn;
		this->_nbr++;
	std::cout << "Alignement::isAligned 3 nbr: " << _nbr << std::endl;
		checkJoinAlignements(newPawn, currentBoard);
	// std::cout << "Alignement::isAligned 4" << std::endl;
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
	// std::cout << "Alignement::isAligned 5" << std::endl;
		std::cout << "Alignement::isAligned join _pawnBegin: " << std::endl;
		_pawnBegin->toString();
		std::cout << "Alignement::isAligned join _pawnEnd: " << std::endl;
		_pawnEnd->toString();
		return 1;
	}
	if (currentKey2.first == key.first && currentKey2.second == key.second)
	{
	// std::cout << "Alignement::isAligned 6" << std::endl;
		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);
		this->_pawnEnd = newPawn;
		this->_nbr++;
	std::cout << "Alignement::isAligned 7 nbr: " << _nbr << std::endl;
		checkJoinAlignements(newPawn, currentBoard);
	// std::cout << "Alignement::isAligned 8" << std::endl;
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
	// std::cout << "Alignement::isAligned 9" << std::endl;
		std::cout << "Alignement::isAligned join _pawnBegin: " << std::endl;
		_pawnBegin->toString();
		std::cout << "Alignement::isAligned join _pawnEnd: " << std::endl;
		_pawnEnd->toString();
		return 1;
	}
	// std::cout << "Alignement::isAligned 10" << std::endl;
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










