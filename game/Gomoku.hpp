#ifndef GOMOKU_HPP
# define GOMOKU_HPP

# include <iostream>
# include "Player.hpp"
# include "Board.hpp"
# include "Computer.hpp"
# include "../engine/OpenGlLib.hpp"
# include "../core/GameObject.hpp"

class CoreEngine;

class Gomoku: public GameObject
{
public:
	Gomoku( void );
 	~Gomoku( void );
	Gomoku( Gomoku const & src );

	Gomoku &	operator=( Gomoku const & rhs );


	// void						stockAlignement(Player* p1, Player* p2, std::pair<int, int> xy);

	void						init( void );
	void						play( void );
	void						playerTurn(Player *player);
	// void						turns(Player* p1, Player* p2);
	void						endGame( void );
	bool						isClicked( void );
	void						endTurn( void );
	std::pair<int, int>			getPair( void );
	void						capturePawns(std::vector<std::pair<int, int> >  capturedPawns, Player* player);

	void						setCoreEngine( CoreEngine * coreEngine );
	CoreEngine*					getCoreEngine( void ) const;
	void						setVerbose(bool isDebugMode);
	bool						getVerbose( void ) const;
	void						setAssist(bool isAssist);
	bool						getAssist( void ) const;
	void						setGameMode(int gameMode);
	int							getGameMode( void ) const;
	void						Swap1Player(Player *player, int step);
	void						Swap1Computer(Player *player, int step);
	virtual int					update( OpenGlLib *	_renderLib, double delta );
	virtual int					render( OpenGlLib *	_renderLib ) const;

private:
	CoreEngine *				_coreEngine;
	Board*						_currentBoard;
	Player*						_player1;
	Player*						_player2;
	bool						_firstPlayerTurn;
	double *					_lastClick;

	bool						_verbose;
	bool						_assist;
	int							_gameMode;

};

#endif