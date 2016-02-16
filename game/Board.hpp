#ifndef BOARD_HPP
# define BOARD_HPP

// # include "Player.hpp"
# include <map>
# include <vector>
# include "../engine/OpenGlLib.hpp"

class Player;
class Pawn;
class Alignement;

#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF

class Board
{
public:
	Board( void );
 	~Board( void );
	Board( Board const & src );

	Board &	operator=( Board const & rhs );

	void								insert(std::pair<int, int> xy, Player* player);
	void								erase(std::pair<int, int> xy);
	void								displayPawns( void );
	Pawn*								findPawn( int x, int y);
	bool 								checkwin(Player* player1, Player* player2);
	// void								checkAround(std::map<std::pair<int,int>, Pawn*>::iterator it);
	// int 								checkFriend(int x, int y, std::pair<int, int> key);
	std::vector<std::pair<int, int> > 	checkOpponent(int x, int y, std::pair<int, int> key);
	std::vector<std::pair<int, int> >	checkTrap(std::pair<int, int> key, std::pair<int, int> key2);
	// int 								checkAlignement(std::pair<int, int> key, std::pair<int, int> key2);
	std::vector<std::pair<int, int> >	checkCapture(int x, int y);
	void								stockAlignement(std::pair<int,int> xy);
	void								findAlignement(Pawn* neighbour, std::pair<int,int> key);
	void								checkNeighbour(std::pair<int,int> key1, std::pair<int,int> key2);
	void								createAlignement(Pawn* neighbour, std::pair<int,int> key);
	void								determinePawnBegin(Alignement* alignement);
	void								determinePawnEnd(Alignement* alignement);
	void 								eraseAlignementFromPawnsBegin(Alignement* al1, Alignement* al2);
	void								erasePawnInsideAlignement(Alignement *align, Pawn* pawn);
	void								deleteAlignement(Alignement* align);
	void								deleteAlignementFromBoard(Alignement* align);



	std::map<std::pair<int,int>, Pawn*>		getPawns();
	int 									getWin();

	int					render( OpenGlLib *	_renderLib );

private:
	std::map<std::pair<int,int>, Pawn*>		_pawns;
	int										_win;

public:
	std::vector<Alignement*> 				_alignements;

};

#endif