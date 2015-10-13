#include "OpenGlLib.hpp"

static void	error_callback( int error, const char * description )
{
	std::cerr << "error[code: "<< error << "]: " << description << std::endl;
}

OpenGlLib::OpenGlLib( void )
{
	glfwSetErrorCallback( error_callback );
	if ( ! glfwInit() )
		std::cerr << "error: failed instanciate OpenglLib !" << std::endl;
	return ;
}

OpenGlLib::~OpenGlLib( void )
{
	return ;
}

bool		OpenGlLib::isCloseRequest( void ) const
{
	return ( glfwWindowShouldClose( this->_window ) );
}

bool		OpenGlLib::createWindow( int height, int width, std::string title)
{
	this->_window = glfwCreateWindow( height, width, title.c_str(), NULL, NULL );
	if ( ! this->_window )
	{
		std::cerr << "error: glfwCreateWindow" << std::endl;
		glfwTerminate();
		return ( false );
	}
	glClearColor( 0.2f, 0.2f, 0.2f, 1.f );
	glfwMakeContextCurrent( this->_window );
	glfwSwapInterval(1);
	// glfwSetKeyCallback( this->_window, key_callback );
	return ( true );
}

bool		OpenGlLib::refreshWindow( void )
{
	glfwSwapBuffers( this->_window );
	return ( true );
}

bool		OpenGlLib::destroyWindow( void )
{
	glfwDestroyWindow( this->_window );
	glfwTerminate();
	return ( true );
}

bool		OpenGlLib::clearWindow( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClearColor( 0.2f, 0.2f, 0.2f, 1.f );
	return ( true );
}