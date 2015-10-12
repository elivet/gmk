#include "../includes/Player.hpp"

Player::Player( void )
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