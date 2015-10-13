#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player
{
public:
	Player( void );
 	~Player( void );
	Player( Player const & src );

	Player &	operator=( Player const & rhs );

private:

};

#endif