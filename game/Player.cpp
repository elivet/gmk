#include "Player.hpp"

Player::Player( void ) : _name(1), _color(0x000000), _capturedPawns(0)
{
	return ;
}

Player::Player( int name, int color ) : _name(name), _color(color), _capturedPawns(0)
{
	return ;
}

Player::~Player( void )
{
	return ;
}

Player::Player( Player const & src )
{
	*this = src;
}

Player &	Player::operator=( Player const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

std::pair<int, int>		Player::play(Board* currentBoard, std::pair<int, int> xy)
{
	// std::cout << this->_name << " playing" << std::endl;
	(void)currentBoard;
	return xy;
}

bool					Player::referee(Board* currentBoard, std::pair<int, int> key)
{
	int		x = key.first;
	int		y = key.second;

	if (x > 18 || x < 0 || y > 18 || y < 0)
	{
		// std::cout << "DEHORS DE LA GRILLE PUTE" << std::endl;
		return ( false );
	}
	if (currentBoard->findPawn(x, y))
	{
		// std::cout << "DEJA UN PION BIAAAATCH" << std::endl;
		return (false);
	}
	if (isDoubleThree(currentBoard, key))
	{
		std::cout << " CANT PLAY DOUBLE THREE "<< std::endl;
		return ( false );
	}

	std::cout << "CEST OK MA CATIN DES ILES" << std::endl;
	return ( true );
}

bool					Player::isDoubleThreeForVector(Board* board, std::pair<int, int> key, std::pair<int, int> v)
{
	Pawn *tmp1;
	int tmp1_x = key.first + v.first;
	int tmp1_y = key.second + v.second;
	Pawn *tmp2;
	int tmp2_x = tmp1_x + v.first;
	int tmp2_y = tmp1_y + v.second;
	Pawn *tmp3;
	int tmp3_x = tmp2_x + v.first;
	int tmp3_y = tmp2_y + v.second;
	Pawn *tmpOposite;
	int tmpO_x = key.first - v.first;
	int tmpO_y = key.second - v.second;

	// _ 0 0 X 0
	// 3 2 1 X O

	std::cout << "1" << std::endl;
	if (board->isPairInsideBoard(tmp1_x, tmp1_y) && board->isPairInsideBoard(tmp2_x, tmp2_y) && board->isPairInsideBoard(tmpO_x, tmpO_y))
	{
		std::cout << "2" << std::endl;
		//if we are on the situation with three pawns aligned ? ? 0 X _ [X: the pawn we are checking | 0: current player pawn] 
		tmp1 = board->findPawn(tmp1_x, tmp1_y);
		if (tmp1 != NULL && tmp1->getPlayer()->getName() == this->getName())
		{
			std::cout << "3" << std::endl;
			// ? 0 0 X _
			tmp2 = board->findPawn(tmp2_x, tmp2_y);
			if (tmp2 != NULL && tmp2->getPlayer()->getName() == this->getName())
			{
				std::cout << "4" << std::endl;
				tmpOposite = board->findPawn(tmpO_x, tmpO_y);
				//? 0 0 X _  TRUE ? 0 0 X . FALSE 
				if (tmpOposite == NULL)
					std::cout << "trouver "<< std::endl;
				return (tmpOposite == NULL);
			}
		}
		else if (board->isPairInsideBoard(tmp3_x, tmp3_y)) // ? ? _ X _
		{
			std::cout << "5" << std::endl;
			tmp2 = board->findPawn(tmp2_x, tmp2_y);
			tmp3 = board->findPawn(tmp3_x, tmp3_y);
			if (tmp2 != NULL && tmp2->getPlayer()->getName() == this->getName() &&
				tmp3 != NULL && tmp3->getPlayer()->getName() == this->getName())
			{
				std::cout << "6" << std::endl;
				tmpOposite = board->findPawn(tmpO_x, tmpO_y);
				if (tmpOposite == NULL)
					std::cout << "trouver "<< std::endl;
				return (tmpOposite == NULL);
			}
		}
	}
	return false;
}

bool					Player::isDoubleThree(Board* currentBoard, std::pair<int, int> key)
{
	int doubleThreeTab[8] = {0}; 
	int res = 0;
	
	//checkin if there is a double three situation in each direction vector

	//left	
	doubleThreeTab[0] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, 0))) ? 1 : 0;
	//right
	doubleThreeTab[1] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, 0))) ? 1 : 0;
	//bottom left
	doubleThreeTab[2] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, -1))) ? 1 : 0;
	//top right
	doubleThreeTab[3] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, 1))) ? 1 : 0;
	//top left
	doubleThreeTab[4] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, 1))) ? 1 : 0;
	//bottom right
	doubleThreeTab[5] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, -1))) ? 1 : 0;
	//top
	doubleThreeTab[6] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(0, 1))) ? 1 : 0;
	//bottom
	doubleThreeTab[7] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(0, -1))) ? 1 : 0;

	//checking number of double threes that will be generated by the current key
	for (int s = 0; s < 8; s++)
	{
		if (doubleThreeTab[s] > 0)
			res++;
	}
	std::cout << "Player: "<< this->getName() <<" -number of double threes: " << res << "["
	<< doubleThreeTab[0] <<  ","
	<< doubleThreeTab[1] <<  ","
	<< doubleThreeTab[2] <<  ","
	<< doubleThreeTab[3] <<  ","
	<< doubleThreeTab[4] <<  ","
	<< doubleThreeTab[5] <<  ","
	<< doubleThreeTab[6] <<  ","
	<< doubleThreeTab[7]
	<< "]" << std::endl;
	return (res >= 2);
}

int						Player::getName() const
{
	return this->_name;
}

int						Player::getColor() const
{
	return this->_color;
}

void				Player::setOpponent(Player* opponent)
{
	_opponent = opponent;
	return ;
}


