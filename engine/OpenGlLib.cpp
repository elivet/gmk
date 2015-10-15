#include "OpenGlLib.hpp"

bool	OpenGlLib::keys[SIZEOF] = {0};

static void	error_callback( int error, const char * description )
{
	std::cerr << "error[code: "<< error << "]: " << description << std::endl;
}

void		OpenGlLib::key_callback( GLFWwindow * window, int key, int scancode, int action, int mods )
{
	(void)scancode;
	(void)mods;
	static int keyLink[][2] =
	{
		{ESC, GLFW_KEY_ESCAPE},
		{RIGHT, GLFW_KEY_RIGHT},
		{LEFT, GLFW_KEY_LEFT},
		{UP, GLFW_KEY_UP},
		{DOWN, GLFW_KEY_DOWN},
		{F1, GLFW_KEY_1},
		{F2, GLFW_KEY_2},
		{F3, GLFW_KEY_3},
		{D, GLFW_KEY_D},
		{A, GLFW_KEY_A},
		{W, GLFW_KEY_W},
		{S, GLFW_KEY_S}
	};

	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GL_TRUE );
	for (int i = 0; i < SIZEOF; i++)
	{
		if ( key == keyLink[i][1] && action == GLFW_PRESS )
			OpenGlLib::keys[i] = true;
		// else if ( key == keyLink[i][1] && action == GLFW_RELEASE )
		// 	OpenglLib::keys[i] = false;
	}
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
	glfwSetKeyCallback( this->_window, key_callback );
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

void		OpenGlLib::updateKeys( void )
{
	for (int i = 0; i < SIZEOF; i++)
		OpenGlLib::keys[i] = false;
	glfwPollEvents();
	return ;
}

bool		OpenGlLib::isKeyPressed( e_key key ) const
{
	return ( OpenGlLib::keys[key] );
}














