#include "OpenGlLib.hpp"
#include <math.h> 

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
	glfwWindowHint(GLFW_SAMPLES, 4);
	this->_window = glfwCreateWindow( height, width, title.c_str(), NULL, NULL );
	glViewport(0, 0, height, width);
	if ( ! this->_window )
	{
		std::cerr << "error: glfwCreateWindow" << std::endl;
		glfwTerminate();
		return ( false );
	}
	glClearColor( 0.33f, 0.56f, 0.91f, 1.f );
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

	unsigned long uColor = 0xFFc98e46; // #AARRGGBB format

    float fAlpha = (float)(uColor >> 24) / 0xFF;
    float fRed = (float)((uColor >> 16) & 0xFF) / 0xFF;
    float fGreen = (float)((uColor >> 8) & 0xFF) / 0xFF;
    float fBlue = (float)(uColor & 0xFF) / 0xFF;

	glClearColor(fRed, fGreen, fBlue, fAlpha);
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

void		OpenGlLib::setColor(int color)
{
	float r, g, b;
	r = (float)( (color & 0xFF0000) >> 16 ) / 255.f;
	g = (float)( (color & 0x00FF00) >> 8 ) / 255.f;
	b = (float)( (color & 0x0000FF) ) / 255.f;

	glColor3f( r, g, b );
}

// void		OpenGlLib::drawSquare( float posX, float posY, float size, int color ) const
// {
// 	float ratio;
// 	int width, height;
// 	glfwGetFramebufferSize( this->_window, &width, &height );
// 	ratio = width / (float) height;
// 	glViewport( 0, 0, width, height );
// 	glMatrixMode( GL_PROJECTION );
// 	glLoadIdentity();
// 	glOrtho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );
// 	glMatrixMode( GL_MODELVIEW );
// 	glLoadIdentity();
// 	glBegin( GL_TRIANGLES );
// 	setColor(color);
// 	ratio *= 20.0;
// 	// glVertex3f( -0.f + posX * size, -(-0.f + posY * size), 0.f );
// 	// glVertex3f( -0.f + posX * size, -(+1.f + posY * size), 0.f );
// 	// glVertex3f( +1.f + posX * size, -(+1.f + posY * size), 0.f );
// 	// glVertex3f( -0.f + posX * size, -(-0.f + posY * size), 0.f );
// 	// glVertex3f( +1.f + posX * size, -(-0.f + posY * size), 0.f );
// 	// glVertex3f( +1.f + posX * size, -(+1.f + posY * size), 0.f );
// 	glVertex3f( ((-0.f + posX) * size) / ratio, -((-0.f + posY) * size) / ratio, 0.f );
// 	glVertex3f( ((-0.f + posX) * size) / ratio, -((+1.f + posY) * size) / ratio, 0.f );
// 	glVertex3f( ((+1.f + posX) * size) / ratio, -((+1.f + posY) * size) / ratio, 0.f );
// 	glVertex3f( ((-0.f + posX) * size) / ratio, -((-0.f + posY) * size) / ratio, 0.f );
// 	glVertex3f( ((+1.f + posX) * size) / ratio, -((-0.f + posY) * size) / ratio, 0.f );
// 	glVertex3f( ((+1.f + posX) * size) / ratio, -((+1.f + posY) * size) / ratio, 0.f );
// 	// (void)posX;
// 	// (void)posY;
// 	// (void)size;
// 	// glVertex3f(-0.5f, 0.5f, -5.0f);
// 	// glVertex3f(-1.0f, 1.5f, -5.0f);
// 	// glVertex3f(-1.5f, 0.5f, -5.0f);

// 	glEnd();
// 	return ;
// }

// void		OpenGlLib::drawLine( float x1, float y1, float x2, float y2, int color ) const
// {
// 	float tmp;
// 	if (x2 < x1)
// 	{
// 		tmp = x2;
// 		x2 = x1;
// 		x1 = tmp;
// 	}
// 	if (y2 < y1)
// 	{
// 		tmp = y2;
// 		y2 = y1;
// 		y1 = tmp;
// 	}
// 	if (y1 == y2)
// 	{
// 		for (int x = x1; x <= x2; x++)
// 		{
// 			this->drawSquare(x, y1, 0.2, color);
// 		}
// 	}
// 	else
// 	{
// 		for (int y = y1; y <= y2; y++)
// 		{
// 			this->drawSquare(x1, y, 0.2, color);
// 		}
// 	}
// 	return ;
// }

// void		OpenGlLib::drawCircle( float cx, float cy, float size, int color ) const
// {
// 	int num_segments = 10;
// 	float theta = 2 * 3.1415926 / float(num_segments); 
// 	float tangetial_factor = tanf(theta);//calculate the tangential factor 

// 	float radial_factor = cosf(theta);//calculate the radial factor 
	
// 	float x = size;//we start at angle = 0 

// 	float y = 0; 
    
// 	glBegin(GL_LINE_LOOP);
// 	setColor(color);
// 	for(int ii = 0; ii < num_segments; ii++) 
// 	{ 
// 		glVertex2f(x + cx, y + cy);//output vertex 
        
// 		//calculate the tangential vector 
// 		//remember, the radial vector is (x, y) 
// 		//to get the tangential vector we flip those coordinates and negate one of them 

// 		float tx = -y; 
// 		float ty = x; 
        
// 		//add the tangential vector 

// 		x += tx * tangetial_factor; 
// 		y += ty * tangetial_factor; 
        
// 		//correct using the radial factor 

// 		x *= radial_factor; 
// 		y *= radial_factor; 
// 	} 
// 	glEnd(); 
// 	return ;
// }

void		OpenGlLib::drawSquare(float x, float y, float scale, int color) const
{
	y *= -1;
	x = x - (RATIO/2);
	y = y + (RATIO/2) - 1*scale;
	
	setColor(color);
	glBegin( GL_POLYGON );
		glVertex2f( (x ) / RATIO*2 , (y ) / RATIO*2 );
		glVertex2f( (x ) / RATIO*2 , (y + scale) / RATIO*2 );
		glVertex2f( (x + scale) / RATIO*2 , (y + scale) / RATIO*2 );
		glVertex2f( (x + scale) / RATIO*2 , (y ) / RATIO*2 );
	glEnd();
}

void		OpenGlLib::drawCircle(float x, float y, float scale, int color) const
{

	y *= -1;
	x = x - (RATIO/2) + scale/2;
	y = y + (RATIO/2) - 1*scale + scale/2;

	double angle;
	double a;
	double b;

	setColor(color);
	glBegin( GL_POLYGON );
		for( int i = 0; i <= (360 * scale) + 20; i++ )
		{
			angle = 2 * M_PI * i / ((360 * scale) + 20);
			a = cos( angle );
			b = sin( angle );
			glVertex2d( (x + a * scale/2)/ RATIO*2  , (y + b * scale/2)/ RATIO*2  );
		}
	glEnd();
}

void		OpenGlLib::drawLine(float xa, float ya, float xb, float yb, int color) const
{
	ya *= -1;
	yb *= -1;
	xa = xa - (RATIO/2);
	ya = ya + (RATIO/2);
	xb = xb - (RATIO/2);
	yb = yb + (RATIO/2);
	setColor(color);
	glBegin(GL_LINE_LOOP);
		glVertex2d(xa / RATIO*2, ya / RATIO*2);
		glVertex2d(xb / RATIO*2, yb / RATIO*2);
	glEnd();
}












