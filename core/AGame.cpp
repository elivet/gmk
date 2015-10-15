#include "CoreEngine.hpp"
#include "GameObject.hpp"
#include "AGame.hpp"

int			AGame::addObject( GameObject * object )
{
	object->setGame(this);
	object->init();
	this->_objects.push_back( object );
	return ( true );
}

int			AGame::update( double delta )
{
	for ( size_t i = 0; i < this->_objects.size(); i++ )
		this->_objects[i]->update( lib, delta );
	return ( true );
}

int			AGame::render( ) const
{
	for ( size_t i = 0; i < this->_objects.size(); i++ )
		this->_objects[i]->render( lib );
	return ( true );
}

int			AGame::isRunnig( void )
{
	return ( this->_isRunning );
}

int			AGame::setRunnig( int state )
{
	this->_isRunning = state;
	return true;
}

void		AGame::setCore( CoreEngine *core )
{
	this->_core = core;
}

CoreEngine*	AGame::getCore( void )
{
	return this->_core;
}
