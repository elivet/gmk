#include "Computer.hpp"

Computer::Computer( void )
{
	this->_name = 2;
	this->_capturedPawns = 0;
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