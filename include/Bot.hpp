#include "Board.hpp"

class Bot
{
public:
	void make_move(board &b);
	Bot(bot_colour bc, int max_depth = 1);

private:
	int max_depth_;
	const player_colour bot_colour_;
};