#include "Alignement.hpp"
// #include "Pawn.hpp"
Alignement::Alignement( void )
{
	return ;
}

Alignement::Alignement( Pawn* p1, Pawn* p2 )
{
	this->_pawnBegin = p1;
	this->_pawnEnd = p2;

	this->_px = p1->getX() - p2->getX();
	this->_py = p1->getY() - p2->getY();
	this->_nx = p2->getX() - p1->getX();
	this->_ny = p2->getY() - p1->getY();
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

int			Alignement::isAligned(std::pair<int, int> key, Board* currentBoard)
{

	std::pair<int,int> currentKey = std::make_pair(_pawnBegin->getX() + this->_px, _pawnBegin->getY() + this->_py); // check si cest bien dans le bon sens maybe linverse
	std::pair<int,int> currentKey2 = std::make_pair(_pawnEnd->getX() + this->_nx, _pawnEnd->getY() + this->_ny); // check si cest bien dans le bon sens maybe linverse
	if (currentKey.first == key.first && currentKey.second == key.second)  
	{
		std::cout << "isAligned6 YAAAAAAASSSSSSSSSSSS IS ALIGNEDDDDDD YAAAAAAASSSSSSSSSSSS" << std::endl;

		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);
		this->_pawnBegin = newPawn;
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
		return 1;
	}
	if (currentKey2.first == key.first && currentKey2.second == key.second)
	{
		std::cout << "isAligned6 YAAAAAAASSSSSSSSSSSS IS ALIGNEDDDDDD YAAAAAAASSSSSSSSSSSS" << std::endl;

		Pawn*	newPawn = currentBoard->findPawn(key.first, key.second);
		this->_pawnEnd = newPawn;
		newPawn->_alignements.push_back(this);
		newPawn->getPlayer()->_alignements.push_back(this);
		return 1;
	}
	return 0;
}