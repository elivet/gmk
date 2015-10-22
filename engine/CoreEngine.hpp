#ifndef CORE_ENGINE_HPP
# define CORE_ENGINE_HPP
# include <iostream>
# include <sys/time.h>
# include <unistd.h>
# include "OpenGlLib.hpp"
# include "../core/GameObject.hpp"
# include "../game/Gomoku.hpp"

# define SECOND		(1000000.0)

class CoreEngine
{
public:
	CoreEngine( float fps );
	CoreEngine( CoreEngine const & src );
	~CoreEngine( void );

	CoreEngine &			operator=( CoreEngine const & rhs );

	bool					start( void );
	bool					stop( void );
	void					setFPS( int fps );
	// int						update( double delta );
	// int						render( void ) const;
	int						setRunnig( int state );
	int						setGame( Gomoku *game );


private:
	CoreEngine( void );

	double						getTime( void );
	void *						_handle;
	float						_fps;
	bool						_isRunning;
	Gomoku*						_game;
	OpenGlLib*					_renderLib;

};

#endif