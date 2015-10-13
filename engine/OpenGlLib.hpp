#ifndef OPENGL_LIB_HPP
# define OPENGL_LIB_HPP
# include <GLFW/glfw3.h>
# include <iostream>

class OpenGlLib
{
public:
	OpenGlLib( void );
	~OpenGlLib( void );

	virtual bool		isCloseRequest( void ) const;
	virtual bool		createWindow( int height, int width, std::string title);
	virtual bool		refreshWindow( void );
	virtual bool		destroyWindow( void );
	virtual bool		clearWindow( void );

private:
	GLFWwindow * _window;
};

#endif