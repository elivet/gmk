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
		return ( false );
	}
	if (currentBoard->findPawn(x, y))
	{
		return (false);
	}
	if (isDoubleThree(currentBoard, key))
	{
		return ( false );
	}

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
	Pawn *tmp4;
	int tmp4_x = tmp3_x + v.first;
	int tmp4_y = tmp3_y + v.second;
	Pawn *tmpOposite;
	int tmpO_x = key.first - v.first;
	int tmpO_y = key.second - v.second;
	Pawn *tmpOpositeNext;
	int tmpOpositeNext_x = tmpO_x - v.first;
	int tmpOpositeNext_y = tmpO_y - v.second;

	// _ 0 0 X 0
	// 3 2 1 X O

	if (board->isPairInsideBoard(tmp1_x, tmp1_y) && board->isPairInsideBoard(tmp2_x, tmp2_y) && board->isPairInsideBoard(tmpO_x, tmpO_y))
	{
		//if we are on the situation with three pawns aligned ? ? 0 X _ [X: the pawn we are checking | 0: current player pawn] 
		tmp1 = board->findPawn(tmp1_x, tmp1_y);
		tmp2 = board->findPawn(tmp2_x, tmp2_y);
		tmpOposite = board->findPawn(tmpO_x, tmpO_y);
		if (tmp1 != NULL && tmpOposite != NULL && tmp1->getPlayer()->getName() == this->getName() && tmpOposite->getPlayer()->getName() == this->getName())
		{
			tmpOpositeNext = board->findPawn(tmpOpositeNext_x, tmpOpositeNext_y);
			if (tmp2 == NULL && tmpOpositeNext == NULL)
				return true;
		}
		if (tmp1 != NULL && tmp1->getPlayer()->getName() == this->getName())
		{
			// ? 0 0 X _
			tmp3 = board->findPawn(tmp3_x, tmp3_y);
			if (tmp2 != NULL && tmp2->getPlayer()->getName() == this->getName())
			{
				//? 0 0 X _  TRUE ? 0 0 X . FALSE 
				return (tmpOposite == NULL && tmp3 == NULL);
			}
		}
		else if (board->isPairInsideBoard(tmp3_x, tmp3_y)) // ? ? _ X _
		{
			tmp3 = board->findPawn(tmp3_x, tmp3_y);
			tmp4 = board->findPawn(tmp4_x, tmp4_y);
			if (tmp2 != NULL && tmp2->getPlayer()->getName() == this->getName() &&
				tmp3 != NULL && tmp3->getPlayer()->getName() == this->getName())
			{
				return (tmpOposite == NULL && tmp4 == NULL);
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

	doubleThreeTab[0] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, 0))) ? 1 : 0; //left
	if (doubleThreeTab[0] == 0)
		doubleThreeTab[1] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, 0))) ? 1 : 0; //right
	
	doubleThreeTab[2] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, -1))) ? 1 : 0; //bottom left
	if (doubleThreeTab[2] == 0)
		doubleThreeTab[3] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, 1))) ? 1 : 0; //top right
	
	doubleThreeTab[4] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(-1, 1))) ? 1 : 0; //top left
	if (doubleThreeTab[4] == 0)
		doubleThreeTab[5] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(1, -1))) ? 1 : 0; //bottom right
	
	doubleThreeTab[6] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(0, 1))) ? 1 : 0; //top
	if (doubleThreeTab[6] == 0)
		doubleThreeTab[7] = (isDoubleThreeForVector(currentBoard, key, std::make_pair(0, -1))) ? 1 : 0; //bottom

	for (int s = 0; s < 8; s++)
	{
		if (doubleThreeTab[s] > 0)
			res++;
	}
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


