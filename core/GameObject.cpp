#include "GameObject.hpp"
#include "../engine/CoreEngine.hpp"

GameObject::GameObject( void )
{
	return ;
}

GameObject::~GameObject( void )
{
	return ;
}

GameObject::GameObject( GameObject const & src )
{
	*this = src;
}

GameObject &	GameObject::operator=( GameObject const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

void						GameObject::setCoreEngine(CoreEngine * coreEngine)
{
	_coreEngine = coreEngine;
}


void		GameObject::setPos( Vec2i pos )
{
	this->_pos = pos;
	return ;
}

CoreEngine*						GameObject::getCoreEngine( void ) const
{
	return ( this->_coreEngine );
}

void						GameObject::init( void )
{

}

Vec2i		GameObject::getPos(void)
{
	return this->_pos;
}