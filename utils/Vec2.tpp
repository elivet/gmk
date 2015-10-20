/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/06 11:06:03 by rbenjami          #+#    #+#             */
/*   Updated: 2015/03/06 11:08:59 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_HPP
# define VEC2_HPP

template <typename T>
class Vec2
{
public:
	inline Vec2( void ) :
		_x( 0 ),
		_y( 0 )
	{
		return ;
	};

	inline Vec2( T const x, T const y ) :
		_x( x ),
		_y( y )
	{
		return ;
	};

	inline Vec2( Vec2 const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline ~Vec2( void )
	{
		return ;
	};

	inline T		length( void ) const
	{
		return ( sqrt( this->_x * this->_x + this->_y * this->_y ) );
	}

	inline Vec2 &	operator=( Vec2 const & rhs )
	{
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		return ( *this );
	};

	inline bool		operator==( Vec2 const & rhs )
	{
		return ( this->_x == rhs.getX() && this->_y == rhs.getY() );
	};

	inline bool		operator!=( Vec2 const & rhs )
	{
		return ( this->_x != rhs.getX() && this->_y != rhs.getY() );
	};

	inline Vec2 &	operator+( Vec2 const & rhs )
	{
		this->_x += rhs.getX();
		this->_y += rhs.getY();
		return ( *this );
	};

	inline Vec2 &	operator-( Vec2 const & rhs )
	{
		this->_x -= rhs.getX();
		this->_y -= rhs.getY();
		return ( *this );
	};

	inline Vec2 &	operator*( Vec2 const & rhs )
	{
		this->_x *= rhs.getX();
		this->_y *= rhs.getY();
		return ( *this );
	};

	inline Vec2 &	operator*( T const & value )
	{
		this->_x *= value;
		this->_y *= value;
		return ( *this );
	};

	inline Vec2 &	operator/( Vec2 const & rhs )
	{
		this->_x /= rhs.getX();
		this->_y /= rhs.getY();
		return ( *this );
	};

	// std::ostream &	operator<<(std::ostream & o, Vec2 const & i)
	// {
	// 	o << "x:" << i.getX() << ", y: " << i.getY() << std::endl;
	// 	return o;
	// }


	/*
	**	SETTER
	*/
	void			setX( float x )
	{
		this->_x = x;
		return ;
	};

	void			setY( float y )
	{
		this->_y = y;
		return ;
	};


	/*
	**	GETTER
	*/
	T				getX( void ) const
	{
		return ( this->_x );
	};

	T				getY( void ) const
	{
		return ( this->_y );
	};

private:
	T				_x;
	T				_y;
};

#endif
