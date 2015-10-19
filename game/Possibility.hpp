#ifndef POSSIBILITY_HPP
# define POSSIBILITY_HPP

# include <iostream>
# include <vector>

class Possibility
{
public:
	Possibility( void );
	Possibility( int x, int y, int player );
 	~Possibility( void );
	Possibility( Possibility const & src );

	Possibility &	operator=( Possibility const & rhs );

private:
	int							_player;
	int							_weight;
	int							_x;
	int							_y;
	std::vector<Possibility> 	_sons;

};

#endif