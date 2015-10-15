#ifndef OPENGL_LIB_HPP
# define OPENGL_LIB_HPP
# include <GLFW/glfw3.h>
# include <iostream>

# define SCREEN 30

class OpenGlLib
{
public:
	OpenGlLib( void );
	~OpenGlLib( void );

	enum e_key
	{
		ESC,
		RIGHT,
		LEFT,
		UP,
		DOWN,
		F1,
		F2,
		F3,
		D,
		A,
		W,
		S,
		SIZEOF
	};

	virtual bool		isCloseRequest( void ) const;
	virtual bool		createWindow( int height, int width, std::string title);
	virtual bool		refreshWindow( void );
	virtual bool		destroyWindow( void );
	virtual bool		clearWindow( void );
	virtual void		updateKeys( void );
	virtual	bool		isKeyPressed( e_key ) const;
	virtual void		drawSquare( int posX, int posY, int size, int color ) const;
	virtual void		drawLine( float x1, float y1, float x2, float y2, int color ) const;

	static void			key_callback( GLFWwindow * window, int key, int scancode, int action, int mods );
	static bool			keys[SIZEOF];

private:
	GLFWwindow * _window;
};

#endif