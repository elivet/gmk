#ifndef CORE_ENGINE_HPP
# define CORE_ENGINE_HPP
# include <iostream>
# include <sys/time.h>
# include <unistd.h>
# include "OpenGlLib.hpp"
# include "../core/GameObject.hpp"

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
	int						update( double delta );
	int						render( void ) const;
	int						setRunnig( int state );
	int						addObject( GameObject * object );


private:
	CoreEngine( void );

	double						getTime( void );
	void *						_handle;
	float						_fps;
	bool						_isRunning;
	std::vector<GameObject *>	_objects;
	OpenGlLib *					_renderLib;

};

#endif