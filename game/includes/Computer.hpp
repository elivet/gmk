#ifndef COMPUTER_HPP
# define COMPUTER_HPP

class Computer
{
public:
	Computer( void );
 	~Computer( void );
	Computer( Computer const & src );

	Computer &	operator=( Computer const & rhs );

private:

};

#endif