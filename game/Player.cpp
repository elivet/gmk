#include "Player.hpp"

Player::Player( void ) : _name(1), _color(0x000000), _capturedPawns(0)
{
	return ;
}

Player::Player( int name, int color ) : _name(name), _color(color), _capturedPawns(0)
{
	return ;
}

Player::~Player( void )
{
	return ;
}

Player::Player( Player const & src )
{
	*this = src;
}

Player &	Player::operator=( Player const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

std::pair<int, int>		Player::play(Board* currentBoard, std::pair<int, int> xy)
{
	std::cout << this->_name << " playing" << std::endl;
	(void)currentBoard;
	return xy;
}

bool					Player::referee(Board* currentBoard, std::pair<int, int> key)
{
	int		x = key.first;
	int		y = key.second;

	if (x > 18 || x < 0 || y > 18 || y < 0)
	{
		std::cout << "DEHORS DE LA GRILLE PUTE" << std::endl;
		return ( false );
	}
	if (currentBoard->findPawn(x, y))
	{
		std::cout << "DEJA UN PION BIAAAATCH" << std::endl;
		return (false);
	}
	std::cout << "CEST OK MA CATIN DES ILES" << std::endl;
	return ( true );
}

int						Player::getName() const
{
	return this->_name;
}

int						Player::getColor() const
{
	return this->_color;
}

void				Player::setOpponent(Player* opponent)
{
	_opponent = opponent;
	return ;
}


