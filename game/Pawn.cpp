#include "Pawn.hpp"
// #include "Alignement.hpp"

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