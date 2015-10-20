#ifndef GAME_OBJECT_HPP
# define GAME_OBJECT_HPP
# include <vector>
# include "../engine/OpenGlLib.hpp"
# include "../utils/vec.hpp"

class CoreEngine;

class GameObject
{
public:
	GameObject( void );
	~GameObject( void );
	GameObject( GameObject const & src );

	GameObject &				operator=( GameObject const & rhs );

	virtual int					update( OpenGlLib *	_renderLib, double delta ) = 0;
	virtual int					render( OpenGlLib *	_renderLib ) const = 0;

	void						setCoreEngine(CoreEngine * coreEngine);
	CoreEngine*					getCoreEngine( void ) const;
	virtual void				init( void );

	void						setPos(Vec2i pos);
	Vec2i						getPos(void);

protected:
	Vec2i 						_pos;
	CoreEngine *				_coreEngine;

};

#endif