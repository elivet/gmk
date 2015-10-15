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

std::pair<int, int>			Computer::play()
{
	std::cout << "Computer playing" << std::endl;
	std::pair<int, int> key = std::make_pair(1, 3);
	return key;
}