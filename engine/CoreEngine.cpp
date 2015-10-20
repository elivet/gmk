#include <cstdlib>
#include <dlfcn.h>
#include "CoreEngine.hpp"

CoreEngine::CoreEngine( float fps ) :
	_fps( fps ),
	_isRunning( false )
{
	_renderLib = new OpenGlLib();
	return ;
}

CoreEngine::CoreEngine( CoreEngine const & src )
{
	*this = src;
	return ;
}

CoreEngine::~CoreEngine( void )
{
	return ;
}

CoreEngine &	CoreEngine::operator=( CoreEngine const & rhs )
{
	if ( this != &rhs )
	{
	}
	return ( * this );
}

double			CoreEngine::getTime( void )
{
	struct timeval		tv;

	gettimeofday( &tv, NULL );
	return ( tv.tv_sec + (double)tv.tv_usec / SECOND );
}

bool			CoreEngine::start( void )
{
	double		startFrame;
	double		endFrame;
	double		dt;
	int			sleep;

	if ( this->_isRunning == true )
	{
		std::cerr << "CoreEngine alrady running !" << std::endl;
		return ( false );
	}
	// if ( this->_game == NULL )
	// {
	// 	std::cerr << "CoreEngine need a game !" << std::endl;
	// 	return ( false );
	// }
	if ( ! this->_renderLib->createWindow( 850, 850, "Gomoku" ) )
	{
		std::cerr << "Failed to create window !" << std::endl;
		return ( false );
	}
	dt = 1 / this->_fps;
	this->_isRunning = true;
	// this->_game->init();
	// while ( this->_isRunning && this->_game->isRunnig())
	while (this->_isRunning)
	{
		startFrame = this->getTime();
		this->_renderLib->updateKeys();
		this->_renderLib->clearWindow();
		if ( this->_renderLib->isCloseRequest())
		{
			this->stop();
			break ;
		}

		// this->_game->update( this->_renderLib, dt );
		this->render();

		this->_renderLib->refreshWindow();

		endFrame = this->getTime();
		dt = (endFrame - startFrame);
		sleep = (SECOND / this->_fps) - (dt * SECOND);
		if ( sleep > 0 )
			usleep( sleep );
		else
			usleep( 1 );
	}
	this->stop();
	return ( true );
}

int			CoreEngine::update( double delta )
{
	for ( size_t i = 0; i < this->_objects.size(); i++ )
		this->_objects[i]->update( _renderLib, delta );
	return ( true );
}

int			CoreEngine::render( void ) const
{
	for ( size_t i = 0; i < this->_objects.size(); i++ )
		this->_objects[i]->render( _renderLib );
	return ( true );
}

int			CoreEngine::setRunnig( int state )
{
	this->_isRunning = state;
	return true;
}

int			CoreEngine::addObject( GameObject * object )
{
	object->setCoreEngine(this);
	object->init();
	this->_objects.push_back( object );
	return ( true );
}

bool			CoreEngine::stop( void )
{
	if ( ! this->_isRunning )
		return ( false );
	this->_renderLib->destroyWindow();
	this->_isRunning = false;
	return ( true );
}

void			CoreEngine::setFPS( int fps )
{
	this->_fps = fps;
}