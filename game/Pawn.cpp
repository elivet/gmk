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

bool Pawn::operator==(Pawn &rhs)
{
	return (this->_player->getName() == rhs.getPlayer()->getName() &&
		this->_x == rhs.getX() &&
		this->_y == rhs.getY()
	);
}

// bool Pawn::operator==( Pawn const &rhs) const
// {
// 	return (this->_player->getName() == rhs.getPlayer()->getName())// &&
// 		// (*this)._x == other->getX() &&
// 		// (*this)._y == other->getY());
// }

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

void	Pawn::deleteAlignement(Alignement* al)
{
	std::cout << "ERASEALGINEMENT START al " <<std::endl;
	al->toString();	
	std::cout << "ERASEALGINEMENT IIIINNN _alignements.size(): " << _alignements.size() << std::endl;
	for (unsigned int i = 0; i < _alignements.size(); i++)
	{
			std::cout << "ERASEALGINEMENT LOOP _alignements[i] " <<std::endl;
		_alignements[i]->toString();
		if (_alignements[i] == al)
		{
			std::cout << "ERASEALGINEMENT SIIIIIIIZE: " << _alignements.size() << std::endl;
			_alignements.erase(_alignements.begin() + i);
			std::cout << "ERASEALGINEMENT SIIIIIIIZE2: " << _alignements.size() << std::endl;
		}

	}
}

void Pawn::toString()
{
	std::cout << "Pawn x:" << this->_x << " ,y:" << this->_y << std::endl;
}