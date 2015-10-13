#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player
{
public:
	Player( void );
	Player( int name );
 	virtual ~Player( void );
	Player( Player const & src );

	Player &	operator=( Player const & rhs );

protected:
	int		_name;
	int		_capturedPawns;

};

#endif