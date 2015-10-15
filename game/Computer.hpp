#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include "Player.hpp"

class Computer : public Player
{
public:
	Computer( void );
 	virtual ~Computer( void );
	Computer( Computer const & src );

	Computer &	operator=( Computer const & rhs );

	virtual std::pair<int, int>			play();

private:

};

#endif