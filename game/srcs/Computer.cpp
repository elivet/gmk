#include "../includes/Computer.hpp"

Computer::Computer( void )
{
	return ;
}

Computer::~Computer( void )
{
	return ;
}

Computer::Computer( Computer const & src )
{
	*this = src;
}

Computer &	Computer::operator=( Computer const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}