#include "Pawn.hpp"
#include "Alignement.hpp"

Pawn::Pawn( void )
{
	return ;
}

Pawn::Pawn( Player* player, int x, int y) : _player( player ), _x(x), _y(y)
{
	// std::cout << "PAWN CONST: " << _player->getName() << std::endl;
	return ;
}

Pawn::~Pawn( void )
{
	return ;
}

Pawn::Pawn( Pawn const & src )
{
	*this = src;
}

Pawn &	Pawn::operator=( Pawn const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

Player*		Pawn::getPlayer()
{
	return this->_player;
}

int		Pawn::getX()
{
	return this->_x;
}

int		Pawn::getY()
{
	return this->_y;
}

std::vector<Alignement*>		Pawn::getAlignements()
{
	return _alignements;
}

void	Pawn::replaceAlignement(Alignement* al1, Alignement* al2)
{
	for (unsigned int i = 0; i < _alignements.size(); i++)
	{
		if (_alignements[i]->getPawnBegin()->getX() == al1->getPawnBegin()->getX() && _alignements[i]->getPawnBegin()->getY() == al1->getPawnBegin()->getY()
			&& _alignements[i]->getPawnEnd()->getX() == al1->getPawnEnd()->getX() && _alignements[i]->getPawnEnd()->getY() == al1->getPawnEnd()->getY())
		{
			_alignements[i] = al2;
			return ;	
		}
	}
	return ;
}

void Pawn::toString()
{
	std::cout << "Pawn x:" << this->_x << " ,y:" << this->_y << std::endl;
}