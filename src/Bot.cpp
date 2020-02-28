
#include <random>
#include "Bot.hpp"	

std::mt19937 rnd(1337);

Bot::Bot(player_colour bc, int max_depth = 1)
{
	max_depth_ = max_depth;
	bot_colour_ = bc;
}


void Bot::make_move(board &b)
{
	auto brd = b.getBoard();
	std::vector<std::pair<figure*, cell> all_moves;
	for(auto &row : brd)
		for(auto &fgr : row)
		{
			if(fgr != nullptr && fgr.colour() == bot_colour_)
			{
				auto moves = fgr.allMoves();
				for(auto &move : moves)
					all_moves.push_back({fgr, move});
			}
		}
	assert(all_moves.size());
	size_t necessary_move = rnd() % all_moves.size(); 
	// for(auto &move: all_moves)
	// {

	// }
	// all_moves[necessary_move].first.move(all_moves[necessary_move].second);
			
};